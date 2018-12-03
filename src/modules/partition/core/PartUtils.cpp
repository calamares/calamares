/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <utils/CalamaresUtilsSystem.h>
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
    {
        cDebug() << "Partition* is NULL";
        return false;
    }

    cDebug() << "Checking if" << candidate->partitionPath() << "can be resized.";
    if ( !candidate->fileSystem().supportGrow() ||
         !candidate->fileSystem().supportShrink() )
    {
        cDebug() << "  .. filesystem" << candidate->fileSystem().name()
            << "does not support resize.";
        return false;
    }

    if ( KPMHelpers::isPartitionFreeSpace( candidate ) )
    {
        cDebug() << "  .. partition is free space";
        return false;
    }

    if ( candidate->isMounted() )
    {
        cDebug() << "  .. partition is mounted";
        return false;
    }

    if ( candidate->roles().has( PartitionRole::Primary ) )
    {
        PartitionTable* table = dynamic_cast< PartitionTable* >( candidate->parent() );
        if ( !table )
        {
            cDebug() << "  .. no partition table found";
            return false;
        }

        if ( table->numPrimaries() >= table->maxPrimaries() )
        {
            cDebug() << "  .. partition table already has" 
                << table->maxPrimaries() << "primary partitions.";
            return false;
        }
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
    cDebug() << "Checking if" << partitionPath << "can be resized.";
    QString partitionWithOs = partitionPath;
    if ( partitionWithOs.startsWith( "/dev/" ) )
    {
        DeviceModel* dm = core->deviceModel();
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            Partition* candidate = KPMHelpers::findPartitionByPath( { dev }, partitionWithOs );
            if ( candidate )
            {
                cDebug() << "  .. found Partition* for" << partitionWithOs;
                return canBeResized( candidate );
            }
        }
        cDebug() << "  .. no Partition* found for" << partitionWithOs;
    }

    cDebug() << "Partition" << partitionWithOs << "CANNOT BE RESIZED FOR AUTOINSTALL.";
    return false;
}


static FstabEntryList
lookForFstabEntries( const QString& partitionPath )
{
    QStringList mountOptions{ "ro" };

    auto r = CalamaresUtils::System::runCommand(
        CalamaresUtils::System::RunLocation::RunInHost,
        { "blkid", "-s", "TYPE", "-o", "value", partitionPath }
    );
    if ( r.getExitCode() )
        cWarning() << "blkid on" << partitionPath << "failed.";
    else
    {
        QString fstype = r.getOutput().trimmed();
        if ( ( fstype == "ext3" ) || ( fstype == "ext4" ) )
            mountOptions.append( "noload" );
    }

    cDebug() << "Checking device" << partitionPath 
        << "for fstab (fs=" << r.getOutput() << ')';

    FstabEntryList fstabEntries;
    QTemporaryDir mountsDir;
    mountsDir.setAutoRemove( false );

    int exit = QProcess::execute( "mount", { "-o", mountOptions.join(','), partitionPath, mountsDir.path() } );
    if ( !exit ) // if all is well
    {
        QFile fstabFile( mountsDir.path() + "/etc/fstab" );
        
        cDebug() << "  .. reading" << fstabFile.fileName();
        
        if ( fstabFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            const QStringList fstabLines = QString::fromLocal8Bit( fstabFile.readAll() )
                                     .split( '\n' );

            for ( const QString& rawLine : fstabLines )
                fstabEntries.append( FstabEntry::fromEtcFstab( rawLine ) );
            fstabFile.close();
            cDebug() << "  .. got" << fstabEntries.count() << "lines.";
            std::remove_if( fstabEntries.begin(), fstabEntries.end(), [](const FstabEntry& x) { return !x.isValid(); } );
            cDebug() << "  .. got" << fstabEntries.count() << "fstab entries.";
        }
        else
            cWarning() << "Could not read fstab from mounted fs";

        if ( QProcess::execute( "umount", { "-R", mountsDir.path() } ) )
            cWarning() << "Could not unmount" << mountsDir.path();
    }
    else
        cWarning() << "Could not mount existing fs";

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
        cError() << "os-prober cannot start.";
    }
    else if ( !osprober.waitForFinished( 60000 ) )
    {
        cError() << "os-prober timed out.";
    }
    else
    {
        osproberOutput.append(
            QString::fromLocal8Bit(
                osprober.readAllStandardOutput() ).trimmed() );
    }

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

    if ( osproberCleanLines.count() > 0 )
        cDebug() << "os-prober lines after cleanup:" << Logger::DebugList( osproberCleanLines );
    else
        cDebug() << "os-prober gave no output.";

    Calamares::JobQueue::instance()->globalStorage()->insert( "osproberLines", osproberCleanLines );

    return osproberEntries;
}

bool
isEfiSystem()
{
    return QDir( "/sys/firmware/efi/efivars" ).exists();
}

bool
isEfiBootable( const Partition* candidate )
{
    cDebug() << "Check EFI bootable" << candidate->partitionPath() << candidate->devicePath();
    cDebug() << " .. flags" << candidate->activeFlags();

    auto flags = PartitionInfo::flags( candidate );

    /* If bit 17 is set, old-style Esp flag, it's OK */
    if ( flags.testFlag( PartitionTable::FlagEsp ) )
        return true;

    /* Otherwise, if it's a GPT table, Boot (bit 0) is the same as Esp */
    const PartitionNode* root = candidate;
    while ( root && !root->isRoot() )
    {
        root = root->parent();
        cDebug() << " .. moved towards root" << (void *)root;
    }

    // Strange case: no root found, no partition table node?
    if ( !root )
        return false;

    const PartitionTable* table = dynamic_cast<const PartitionTable*>( root );
    cDebug() << "  .. partition table" << (void *)table << "type" << ( table ? table->type() : PartitionTable::TableType::unknownTableType );
    return table && ( table->type() == PartitionTable::TableType::gpt ) &&
        flags.testFlag( PartitionTable::FlagBoot );
}

}  // nmamespace PartUtils

/* Implementation of methods for FstabEntry, from OsproberEntry.h */

bool
FstabEntry::isValid() const
{
    return !partitionNode.isEmpty() && !mountPoint.isEmpty() && !fsType.isEmpty();
}

FstabEntry
FstabEntry::fromEtcFstab( const QString& rawLine )
{
    QString line = rawLine.simplified();
    if ( line.startsWith( '#' ) )
        return FstabEntry{ QString(), QString(), QString(), QString(), 0, 0 };

    QStringList splitLine = line.split( ' ' );
    if ( splitLine.length() != 6 )
        return FstabEntry{ QString(), QString(), QString(), QString(), 0, 0 };

    return FstabEntry{ splitLine.at( 0 ), // path, or UUID, or LABEL, etc.
                       splitLine.at( 1 ), // mount point
                       splitLine.at( 2 ), // fs type
                       splitLine.at( 3 ), // options
                       splitLine.at( 4 ).toInt(), //dump
                       splitLine.at( 5 ).toInt()  //pass
                       };
 }
