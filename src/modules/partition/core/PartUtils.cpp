/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PartUtils.h"

#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/PartitionInfo.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/Mount.h"
#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QProcess>
#include <QTemporaryDir>

using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::isPartitionNew;

namespace PartUtils
{

QString
convenienceName( const Partition* const candidate )
{
    if ( !candidate->mountPoint().isEmpty() )
    {
        return candidate->mountPoint();
    }
    if ( !candidate->partitionPath().isEmpty() )
    {
        return candidate->partitionPath();
    }
    if ( !candidate->devicePath().isEmpty() )
    {
        return candidate->devicePath();
    }
    if ( !candidate->deviceNode().isEmpty() )
    {
        return candidate->devicePath();
    }

    QString p;
    QTextStream s( &p );
    s << static_cast< const void* >( candidate );  // No good name available, use pointer address

    return p;
}

/** @brief Get the globalStorage setting for required space. */
static double
getRequiredStorageGiB( bool& ok )
{
    return Calamares::JobQueue::instance()->globalStorage()->value( "requiredStorageGiB" ).toDouble( &ok );
}

bool
canBeReplaced( Partition* candidate )
{
    if ( !candidate )
    {
        cDebug() << "Partition* is NULL";
        return false;
    }

    cDebug() << "Checking if" << convenienceName( candidate ) << "can be replaced.";
    if ( candidate->isMounted() )
    {
        cDebug() << Logger::SubEntry << "NO, it is mounted.";
        return false;
    }

    bool ok = false;
    double requiredStorageGiB = getRequiredStorageGiB( ok );
    if ( !ok )
    {
        cDebug() << Logger::SubEntry << "NO, requiredStorageGiB is not set correctly.";
        return false;
    }

    qint64 availableStorageB = candidate->capacity();
    qint64 requiredStorageB = CalamaresUtils::GiBtoBytes( requiredStorageGiB + 0.5 );

    if ( availableStorageB > requiredStorageB )
    {
        cDebug() << "Partition" << convenienceName( candidate ) << "authorized for replace install.";
        return true;
    }
    else
    {
        Logger::CDebug deb;
        deb << Logger::SubEntry << "NO, insufficient storage";
        deb << Logger::Continuation << "Required  storage B:" << requiredStorageB
            << QString( "(%1GiB)" ).arg( requiredStorageGiB );
        deb << Logger::Continuation << "Available storage B:" << availableStorageB
            << QString( "(%1GiB)" ).arg( CalamaresUtils::BytesToGiB( availableStorageB ) );
        return false;
    }
}


bool
canBeResized( Partition* candidate )
{
    if ( !candidate )
    {
        cDebug() << "Partition* is NULL";
        return false;
    }

    cDebug() << "Checking if" << convenienceName( candidate ) << "can be resized.";
    if ( !candidate->fileSystem().supportGrow() || !candidate->fileSystem().supportShrink() )
    {
        cDebug() << Logger::SubEntry << "NO, filesystem" << candidate->fileSystem().name()
                 << "does not support resize.";
        return false;
    }

    if ( isPartitionFreeSpace( candidate ) )
    {
        cDebug() << Logger::SubEntry << "NO, partition is free space";
        return false;
    }

    if ( candidate->isMounted() )
    {
        cDebug() << Logger::SubEntry << "NO, partition is mounted";
        return false;
    }

    if ( candidate->roles().has( PartitionRole::Primary ) )
    {
        PartitionTable* table = dynamic_cast< PartitionTable* >( candidate->parent() );
        if ( !table )
        {
            cDebug() << Logger::SubEntry << "NO, no partition table found";
            return false;
        }

        if ( table->numPrimaries() >= table->maxPrimaries() )
        {
            cDebug() << Logger::SubEntry << "NO, partition table already has" << table->maxPrimaries()
                     << "primary partitions.";
            return false;
        }
    }

    bool ok = false;
    double requiredStorageGiB = getRequiredStorageGiB( ok );
    if ( !ok )
    {
        cDebug() << Logger::SubEntry << "NO, requiredStorageGiB is not set correctly.";
        return false;
    }

    // We require a little more for partitioning overhead and swap file
    double advisedStorageGiB = requiredStorageGiB + 0.5 + 2.0;
    qint64 availableStorageB = candidate->available();
    qint64 advisedStorageB = CalamaresUtils::GiBtoBytes( advisedStorageGiB );

    if ( availableStorageB > advisedStorageB )
    {
        cDebug() << "Partition" << convenienceName( candidate ) << "authorized for resize + autopartition install.";
        return true;
    }
    else
    {
        Logger::CDebug deb;
        deb << Logger::SubEntry << "NO, insufficient storage";
        deb << Logger::Continuation << "Required  storage B:" << advisedStorageB
            << QString( "(%1GiB)" ).arg( advisedStorageGiB );
        deb << Logger::Continuation << "Available storage B:" << availableStorageB
            << QString( "(%1GiB)" ).arg( CalamaresUtils::BytesToGiB( availableStorageB ) ) << "for"
            << convenienceName( candidate ) << "length:" << candidate->length()
            << "sectorsUsed:" << candidate->sectorsUsed() << "fsType:" << candidate->fileSystem().name();
        return false;
    }
}


bool
canBeResized( DeviceModel* dm, const QString& partitionPath )
{
    cDebug() << "Checking if" << partitionPath << "can be resized.";
    QString partitionWithOs = partitionPath;
    if ( partitionWithOs.startsWith( "/dev/" ) )
    {
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            Partition* candidate = CalamaresUtils::Partition::findPartitionByPath( { dev }, partitionWithOs );
            if ( candidate )
            {
                return canBeResized( candidate );
            }
        }
        cDebug() << Logger::SubEntry << "no Partition* found for" << partitionWithOs;
    }

    cDebug() << Logger::SubEntry << "Partition" << partitionWithOs << "CANNOT BE RESIZED FOR AUTOINSTALL.";
    return false;
}


static FstabEntryList
lookForFstabEntries( const QString& partitionPath )
{
    QStringList mountOptions { "ro" };

    auto r = CalamaresUtils::System::runCommand( CalamaresUtils::System::RunLocation::RunInHost,
                                                 { "blkid", "-s", "TYPE", "-o", "value", partitionPath } );
    if ( r.getExitCode() )
    {
        cWarning() << "blkid on" << partitionPath << "failed.";
    }
    else
    {
        QString fstype = r.getOutput().trimmed();
        if ( ( fstype == "ext3" ) || ( fstype == "ext4" ) )
        {
            mountOptions.append( "noload" );
        }
    }

    cDebug() << "Checking device" << partitionPath << "for fstab (fs=" << r.getOutput() << ')';

    FstabEntryList fstabEntries;

    CalamaresUtils::Partition::TemporaryMount mount( partitionPath, QString(), mountOptions.join( ',' ) );
    if ( mount.isValid() )
    {
        QFile fstabFile( mount.path() + "/etc/fstab" );

        cDebug() << Logger::SubEntry << "reading" << fstabFile.fileName();

        if ( fstabFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            const QStringList fstabLines = QString::fromLocal8Bit( fstabFile.readAll() ).split( '\n' );

            for ( const QString& rawLine : fstabLines )
            {
                fstabEntries.append( FstabEntry::fromEtcFstab( rawLine ) );
            }
            fstabFile.close();
            cDebug() << Logger::SubEntry << "got" << fstabEntries.count() << "lines.";
            std::remove_if(
                fstabEntries.begin(), fstabEntries.end(), []( const FstabEntry& x ) { return !x.isValid(); } );
            cDebug() << Logger::SubEntry << "got" << fstabEntries.count() << "fstab entries.";
        }
        else
        {
            cWarning() << "Could not read fstab from mounted fs";
        }
    }
    else
    {
        cWarning() << "Could not mount existing fs";
    }

    return fstabEntries;
}


static QString
findPartitionPathForMountPoint( const FstabEntryList& fstab, const QString& mountPoint )
{
    if ( fstab.isEmpty() )
    {
        return QString();
    }

    for ( const FstabEntry& entry : fstab )
    {
        if ( entry.mountPoint == mountPoint )
        {
            QProcess readlink;
            QString partPath;

            if ( entry.partitionNode.startsWith( "/dev" ) )  // plain dev node
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

            if ( partPath.startsWith( "/dev/disk/by-" ) )  // we got a fancy node
            {
                readlink.start( "readlink", { "-en", partPath } );
                if ( !readlink.waitForStarted( 1000 ) )
                {
                    return QString();
                }
                if ( !readlink.waitForFinished( 1000 ) )
                {
                    return QString();
                }
                if ( readlink.exitCode() != 0 || readlink.exitStatus() != QProcess::NormalExit )
                {
                    return QString();
                }
                partPath = QString::fromLocal8Bit( readlink.readAllStandardOutput() ).trimmed();
            }

            return partPath;
        }
    }

    return QString();
}


OsproberEntryList
runOsprober( DeviceModel* dm )
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
        osproberOutput.append( QString::fromLocal8Bit( osprober.readAllStandardOutput() ).trimmed() );
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
            {
                prettyName = lineColumns.value( 1 ).simplified();
            }
            else if ( !lineColumns.value( 2 ).simplified().isEmpty() )
            {
                prettyName = lineColumns.value( 2 ).simplified();
            }

            QString file, path = lineColumns.value( 0 ).simplified();
            if ( !path.startsWith( "/dev/" ) )  //basic sanity check
            {
                continue;
            }

            // strip extra file after device: /dev/name@/path/to/file
            int index = path.indexOf( '@' );
            if ( index != -1 )
            {
                file = path.right( path.length() - index - 1 );
                path = path.left( index );
            }

            FstabEntryList fstabEntries = lookForFstabEntries( path );
            QString homePath = findPartitionPathForMountPoint( fstabEntries, "/home" );

            osproberEntries.append(
                { prettyName, path, file, QString(), canBeResized( dm, path ), lineColumns, fstabEntries, homePath } );
            osproberCleanLines.append( line );
        }
    }

    if ( osproberCleanLines.count() > 0 )
    {
        cDebug() << "os-prober lines after cleanup:" << Logger::DebugList( osproberCleanLines );
    }
    else
    {
        cDebug() << "os-prober gave no output.";
    }

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
    const auto flags = PartitionInfo::flags( candidate );

    // TODO: with KPMCore 4, this comment is wrong: the flags
    //       are remapped, and the ESP flag is the same as Boot.
#if defined( WITH_KPMCORE4API )
    static_assert( KPM_PARTITION_FLAG_ESP == KPM_PARTITION_FLAG( Boot ), "KPMCore API enum changed" );
    return flags.testFlag( KPM_PARTITION_FLAG_ESP );
#else
    /* If bit 17 is set, old-style Esp flag, it's OK */
    if ( flags.testFlag( KPM_PARTITION_FLAG_ESP ) )
    {
        return true;
    }

    /* Otherwise, if it's a GPT table, Boot (bit 0) is the same as Esp */
    const PartitionTable* table = CalamaresUtils::Partition::getPartitionTable( candidate );
    if ( !table )
    {
        cWarning() << "Root of partition table is not a PartitionTable object";
        return false;
    }
    if ( table->type() == PartitionTable::TableType::gpt )
    {
        const auto bootFlag = KPM_PARTITION_FLAG( Boot );
        return flags.testFlag( bootFlag );
    }
    return false;
#endif
}

QString
findFS( QString fsName, FileSystem::Type* fsType )
{
    QStringList fsLanguage { QLatin1String( "C" ) };  // Required language list to turn off localization
    if ( fsName.isEmpty() )
    {
        fsName = QStringLiteral( "ext4" );
    }

    FileSystem::Type tmpType = FileSystem::typeForName( fsName, fsLanguage );
    if ( tmpType != FileSystem::Unknown )
    {
        cDebug() << "Found filesystem" << fsName;
        if ( fsType )
        {
            *fsType = tmpType;
        }
        return fsName;
    }

    // Second pass: try case-insensitive
    const auto fstypes = FileSystem::types();
    for ( FileSystem::Type t : fstypes )
    {
        if ( 0 == QString::compare( fsName, FileSystem::nameForType( t, fsLanguage ), Qt::CaseInsensitive ) )
        {
            QString fsRealName = FileSystem::nameForType( t, fsLanguage );
            cDebug() << "Filesystem name" << fsName << "translated to" << fsRealName;
            if ( fsType )
            {
                *fsType = t;
            }
            return fsRealName;
        }
    }

    cDebug() << "Filesystem" << fsName << "not found, using ext4";
    fsName = QStringLiteral( "ext4" );
    // fsType can be used to check whether fsName was a valid filesystem.
    if ( fsType )
    {
        *fsType = FileSystem::Unknown;
    }
#ifdef DEBUG_FILESYSTEMS
    // This bit is for distro's debugging their settings, and shows
    // all the strings that KPMCore is matching against for FS type.
    {
        Logger::CDebug d;
        using TR = Logger::DebugRow< int, QString >;
        const auto fstypes = FileSystem::types();
        d << "Available types (" << fstypes.count() << ')';
        for ( FileSystem::Type t : fstypes )
        {
            d << TR( static_cast< int >( t ), FileSystem::nameForType( t, fsLanguage ) );
        }
    }
#endif
    return fsName;
}

}  // namespace PartUtils

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
        return FstabEntry { QString(), QString(), QString(), QString(), 0, 0 };

    QStringList splitLine = line.split( ' ' );
    if ( splitLine.length() != 6 )
        return FstabEntry { QString(), QString(), QString(), QString(), 0, 0 };

    return FstabEntry {
        splitLine.at( 0 ),  // path, or UUID, or LABEL, etc.
        splitLine.at( 1 ),  // mount point
        splitLine.at( 2 ),  // fs type
        splitLine.at( 3 ),  // options
        splitLine.at( 4 ).toInt(),  //dump
        splitLine.at( 5 ).toInt()  //pass
    };
}
