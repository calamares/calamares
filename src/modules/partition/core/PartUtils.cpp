/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "PartUtils.h"

#include "PartitionCoreModule.h"

#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/PartitionIterator.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <utils/Logger.h>
#include <JobQueue.h>
#include <GlobalStorage.h>

#include <QProcess>
#include <QTemporaryDir>

namespace PartUtils
{

bool
canBeReplaced( Partition* candidate )
{
    if ( !candidate )
        return false;

    if ( candidate->isMounted() )
        return false;

    bool ok = false;
    double requiredStorageGB = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "requiredStorageGB" )
                                    .toDouble( &ok );

    qint64 availableStorageB = candidate->capacity();
    qint64 requiredStorageB = ( requiredStorageGB + 0.5 ) * 1024 * 1024 * 1024;
    cDebug() << "Required  storage B:" << requiredStorageB
             << QString( "(%1GB)" ).arg( requiredStorageB / 1024 / 1024 / 1024 );
    cDebug() << "Storage capacity  B:" << availableStorageB
             << QString( "(%1GB)" ).arg( availableStorageB / 1024 / 1024 / 1024 )
             << "for" << candidate->partitionPath() << "   length:" << candidate->length();

    if ( ok &&
         availableStorageB > requiredStorageB )
    {
        cDebug() << "Partition" << candidate->partitionPath() << "authorized for replace install.";

        return true;
    }
    return false;
}


bool
canBeResized( Partition* candidate )
{
    if ( !candidate )
        return false;

    if ( !candidate->fileSystem().supportGrow() ||
         !candidate->fileSystem().supportShrink() )
        return false;

    if ( KPMHelpers::isPartitionFreeSpace( candidate ) )
        return false;

    if ( candidate->isMounted() )
        return false;

    if ( candidate->roles().has( PartitionRole::Primary ) )
    {
        PartitionTable* table = dynamic_cast< PartitionTable* >( candidate->parent() );
        if ( !table )
            return false;

        if ( table->numPrimaries() >= table->maxPrimaries() )
            return false;
    }

    bool ok = false;
    double requiredStorageGB = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "requiredStorageGB" )
                                    .toDouble( &ok );
    double advisedStorageGB = requiredStorageGB + 0.5 + 2.0;

    qint64 availableStorageB = candidate->available();

    // We require a little more for partitioning overhead and swap file
    // TODO: maybe make this configurable?
    qint64 advisedStorageB = advisedStorageGB * 1024 * 1024 * 1024;
    cDebug() << "Required  storage B:" << advisedStorageB
             << QString( "(%1GB)" ).arg( advisedStorageGB );
    cDebug() << "Available storage B:" << availableStorageB
             << QString( "(%1GB)" ).arg( availableStorageB / 1024 / 1024 / 1024 )
             << "for" << candidate->partitionPath() << "   length:" << candidate->length()
             << "   sectorsUsed:" << candidate->sectorsUsed() << "   fsType:" << candidate->fileSystem().name();

    if ( ok &&
         availableStorageB > advisedStorageB )
    {
        cDebug() << "Partition" << candidate->partitionPath() << "authorized for resize + autopartition install.";

        return true;
    }
    return false;
}


bool
canBeResized( PartitionCoreModule* core, const QString& partitionPath )
{
    //FIXME: check for max partitions count on DOS MBR
    cDebug() << "checking if" << partitionPath << "can be resized.";
    QString partitionWithOs = partitionPath;
    if ( partitionWithOs.startsWith( "/dev/" ) )
    {
        cDebug() << partitionWithOs << "seems like a good path";
        bool canResize = false;
        DeviceModel* dm = core->deviceModel();
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            Partition* candidate = KPMHelpers::findPartitionByPath( { dev }, partitionWithOs );
            if ( candidate )
            {
                cDebug() << "found Partition* for" << partitionWithOs;
                return canBeResized( candidate );
            }
        }
    }

    cDebug() << "Partition" << partitionWithOs << "CANNOT BE RESIZED FOR AUTOINSTALL.";
    return false;
}


static FstabEntryList
lookForFstabEntries( const QString& partitionPath )
{
    FstabEntryList fstabEntries;
    QTemporaryDir mountsDir;

    int exit = QProcess::execute( "mount", { partitionPath, mountsDir.path() } );
    if ( !exit ) // if all is well
    {
        QFile fstabFile( mountsDir.path() + "/etc/fstab" );
        if ( fstabFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            const QStringList fstabLines = QString::fromLocal8Bit( fstabFile.readAll() )
                                     .split( '\n' );

            for ( const QString& rawLine : fstabLines )
            {
                QString line = rawLine.simplified();
                if ( line.startsWith( '#' ) )
                    continue;

                QStringList splitLine = line.split( ' ' );
                if ( splitLine.length() != 6 )
                    continue;

                fstabEntries.append( { splitLine.at( 0 ), // path, or UUID, or LABEL, etc.
                                       splitLine.at( 1 ), // mount point
                                       splitLine.at( 2 ), // fs type
                                       splitLine.at( 3 ), // options
                                       splitLine.at( 4 ).toInt(), //dump
                                       splitLine.at( 5 ).toInt()  //pass
                                     } );
            }

            fstabFile.close();
        }

        QProcess::execute( "umount", { "-R", mountsDir.path() } );
    }

    return fstabEntries;
}


static QString
findPartitionPathForMountPoint( const FstabEntryList& fstab,
                                const QString& mountPoint )
{
    if ( fstab.isEmpty() )
        return QString();

    for ( const FstabEntry& entry : fstab )
    {
        if ( entry.mountPoint == mountPoint )
        {
            QProcess readlink;
            QString partPath;

            if ( entry.partitionNode.startsWith( "/dev" ) ) // plain dev node
            {
                partPath = entry.partitionNode;
            }
            else if ( entry.partitionNode.startsWith( "LABEL=" ) )
            {
                partPath = entry.partitionNode.mid( 6 );
                partPath.remove( "\"" );
                partPath.replace( "\\040", "\\ " );
                partPath.prepend( "/dev/disk/by-label/" );
            }
            else if ( entry.partitionNode.startsWith( "UUID=" ) )
            {
                partPath = entry.partitionNode.mid( 5 );
                partPath.remove( "\"" );
                partPath = partPath.toLower();
                partPath.prepend( "/dev/disk/by-uuid/" );
            }
            else if ( entry.partitionNode.startsWith( "PARTLABEL=" ) )
            {
                partPath = entry.partitionNode.mid( 10 );
                partPath.remove( "\"" );
                partPath.replace( "\\040", "\\ " );
                partPath.prepend( "/dev/disk/by-partlabel/" );
            }
            else if ( entry.partitionNode.startsWith( "PARTUUID=" ) )
            {
                partPath = entry.partitionNode.mid( 9 );
                partPath.remove( "\"" );
                partPath = partPath.toLower();
                partPath.prepend( "/dev/disk/by-partuuid/" );
            }

            // At this point we either have /dev/sda1, or /dev/disk/by-something/...

            if ( partPath.startsWith( "/dev/disk/by-" ) ) // we got a fancy node
            {
                readlink.start( "readlink", { "-en", partPath });
                if ( !readlink.waitForStarted( 1000 ) )
                    return QString();
                if ( !readlink.waitForFinished( 1000 ) )
                    return QString();
                if ( readlink.exitCode() != 0 || readlink.exitStatus() != QProcess::NormalExit )
                    return QString();
                partPath = QString::fromLocal8Bit(
                               readlink.readAllStandardOutput() ).trimmed();
            }

            return partPath;
        }
    }

    return QString();
}


OsproberEntryList
runOsprober( PartitionCoreModule* core )
{
    QString osproberOutput;
    QProcess osprober;
    osprober.setProgram( "os-prober" );
    osprober.setProcessChannelMode( QProcess::SeparateChannels );
    osprober.start();
    if ( !osprober.waitForStarted() )
    {
        cDebug() << "ERROR: os-prober cannot start.";
    }
    else if ( !osprober.waitForFinished( 60000 ) )
    {
        cDebug() << "ERROR: os-prober timed out.";
    }
    else
    {
        osproberOutput.append(
            QString::fromLocal8Bit(
                osprober.readAllStandardOutput() ).trimmed() );
    }

    QString osProberReport( "Osprober lines, clean:\n" );
    QStringList osproberCleanLines;
    OsproberEntryList osproberEntries;
    const auto lines = osproberOutput.split( '\n' );
    for ( const QString& line : lines )
    {
        if ( !line.simplified().isEmpty() )
        {
            QStringList lineColumns = line.split( ':' );
            QString prettyName;
            if ( !lineColumns.value( 1 ).simplified().isEmpty() )
                prettyName = lineColumns.value( 1 ).simplified();
            else if ( !lineColumns.value( 2 ).simplified().isEmpty() )
                prettyName = lineColumns.value( 2 ).simplified();

            QString path = lineColumns.value( 0 ).simplified();
            if ( !path.startsWith( "/dev/" ) ) //basic sanity check
                continue;

            FstabEntryList fstabEntries = lookForFstabEntries( path );
            QString homePath = findPartitionPathForMountPoint( fstabEntries, "/home" );

            osproberEntries.append( { prettyName,
                                      path,
                                      QString(),
                                      canBeResized( core, path ),
                                      lineColumns,
                                      fstabEntries,
                                      homePath } );
            osproberCleanLines.append( line );
        }
    }
    osProberReport.append( osproberCleanLines.join( '\n' ) );
    cDebug() << osProberReport;

    Calamares::JobQueue::instance()->globalStorage()->insert( "osproberLines", osproberCleanLines );

    return osproberEntries;
}

bool
isEfiSystem()
{
    return QDir( "/sys/firmware/efi/efivars" ).exists();
}

}  // nmamespace PartUtils
