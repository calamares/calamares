/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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

static const NamedEnumTable<SizeUnit>&
unitSuffixes()
{
    static const NamedEnumTable<SizeUnit> names{
        { QStringLiteral( "%" ), SizeUnit::Percent },
        { QStringLiteral( "B" ), SizeUnit::Byte },
        { QStringLiteral( "K" ), SizeUnit::KiB },
        { QStringLiteral( "M" ), SizeUnit::MiB },
        { QStringLiteral( "G" ), SizeUnit::GiB }
    };

    return names;
}

PartSize::PartSize( const QString& s )
    : NamedSuffix( unitSuffixes(), s )
{
    if ( ( unit() == SizeUnit::Percent ) && ( value() > 100 || value() < 0 ) )
    {
        cDebug() << "Percent value" << value() << "is not valid.";
        m_value = 0;
    }

    if ( m_unit == SizeUnit::None )
    {
        m_value = s.toInt();
        if ( m_value > 0 )
            m_unit = SizeUnit::Byte;
    }

    if ( m_value <= 0 )
    {
        m_value = 0;
        m_unit = SizeUnit::None;
    }
}

qint64
PartSize::toSectors( qint64 totalSectors, qint64 sectorSize ) const
{
    if ( !isValid() )
        return -1;
    if ( totalSectors < 1 || sectorSize < 1 )
        return -1;

    switch ( m_unit )
    {
    case unit_t::None:
        return -1;
    case unit_t::Percent:
        if ( value() == 100 )
            return totalSectors;  // Common-case, avoid futzing around
        else
            return totalSectors * value() / 100;
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return bytesToSectors ( toBytes(), sectorSize );
    }

    return -1;
}

qint64
PartSize::toBytes( qint64 totalSectors, qint64 sectorSize ) const
{
    if ( !isValid() )
        return -1;

    switch ( m_unit )
    {
    case unit_t::None:
        return -1;
    case unit_t::Percent:
        if ( totalSectors < 1 || sectorSize < 1 )
            return -1;
        if ( value() == 100 )
            return totalSectors * sectorSize;  // Common-case, avoid futzing around
        else
            return totalSectors * value() / 100;
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return toBytes();
    }

    // notreached
    return -1;
}

qint64
PartSize::toBytes( qint64 totalBytes ) const
{
    if ( !isValid() )
        return -1;

    switch ( m_unit )
    {
    case unit_t::None:
        return -1;
    case unit_t::Percent:
        if ( totalBytes < 1 )
            return -1;
        if ( value() == 100 )
            return totalBytes;  // Common-case, avoid futzing around
        else
            return totalBytes * value() / 100;
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return toBytes();
    }

    // notreached
    return -1;
}

qint64
PartSize::toBytes() const
{
    if ( !isValid() )
        return -1;

    switch ( m_unit )
    {
    case unit_t::Byte:
        return value();
    case unit_t::KiB:
        return CalamaresUtils::KiBtoBytes( static_cast<unsigned long long>( value() ) );
    case unit_t::MiB:
        return CalamaresUtils::MiBtoBytes( static_cast<unsigned long long>( value() ) );
    case unit_t::GiB:
        return CalamaresUtils::GiBtoBytes( static_cast<unsigned long long>( value() ) );
    default:
        break;
    }

    // Reached only when unit is Percent or None
    return -1;
}

bool
PartSize::operator< ( const PartSize& other ) const
{
    if ( ( m_unit == SizeUnit::None || other.m_unit == SizeUnit::None ) ||
         ( m_unit == SizeUnit::Percent && other.m_unit != SizeUnit::Percent ) ||
         ( m_unit != SizeUnit::Percent && other.m_unit == SizeUnit::Percent ) )
        return false;

    switch ( m_unit )
    {
    case SizeUnit::Percent:
        return ( m_value < other.m_value );
    case SizeUnit::Byte:
    case SizeUnit::KiB:
    case SizeUnit::MiB:
    case SizeUnit::GiB:
        return ( toBytes() < other.toBytes () );
    }

    return false;
}

bool
PartSize::operator> ( const PartSize& other ) const
{
    if ( ( m_unit == SizeUnit::None || other.m_unit == SizeUnit::None ) ||
         ( m_unit == SizeUnit::Percent && other.m_unit != SizeUnit::Percent ) ||
         ( m_unit != SizeUnit::Percent && other.m_unit == SizeUnit::Percent ) )
        return false;

    switch ( m_unit )
    {
    case SizeUnit::Percent:
        return ( m_value > other.m_value );
    case SizeUnit::Byte:
    case SizeUnit::KiB:
    case SizeUnit::MiB:
    case SizeUnit::GiB:
        return ( toBytes() > other.toBytes () );
    }

    return false;
}

bool
PartSize::operator== ( const PartSize& other ) const
{
    if ( ( m_unit == SizeUnit::None || other.m_unit == SizeUnit::None ) ||
         ( m_unit == SizeUnit::Percent && other.m_unit != SizeUnit::Percent ) ||
         ( m_unit != SizeUnit::Percent && other.m_unit == SizeUnit::Percent ) )
        return false;

    switch ( m_unit )
    {
    case SizeUnit::Percent:
        return ( m_value == other.m_value );
    case SizeUnit::Byte:
    case SizeUnit::KiB:
    case SizeUnit::MiB:
    case SizeUnit::GiB:
        return ( toBytes() == other.toBytes () );
    }

    return false;
}

QString
convenienceName( const Partition* const candidate )
{
    if ( !candidate->mountPoint().isEmpty() )
        return candidate->mountPoint();
    if ( !candidate->partitionPath().isEmpty() )
        return candidate->partitionPath();
    if ( !candidate->devicePath().isEmpty() )
        return candidate->devicePath();
    if ( !candidate->deviceNode().isEmpty() )
        return candidate->devicePath();

    QString p;
    QTextStream s( &p );
    s << (void *)candidate;

    return p;
}

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
             << "for" << convenienceName( candidate ) << "   length:" << candidate->length();

    if ( ok &&
         availableStorageB > requiredStorageB )
    {
        cDebug() << "Partition" << convenienceName( candidate ) << "authorized for replace install.";

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

    cDebug() << "Checking if" << convenienceName( candidate ) << "can be resized.";
    if ( !candidate->fileSystem().supportGrow() ||
         !candidate->fileSystem().supportShrink() )
    {
        cDebug() << Logger::SubEntry << "NO, filesystem" << candidate->fileSystem().name()
            << "does not support resize.";
        return false;
    }

    if ( KPMHelpers::isPartitionFreeSpace( candidate ) )
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
            cDebug() << Logger::SubEntry << "NO, partition table already has"
                << table->maxPrimaries() << "primary partitions.";
            return false;
        }
    }

    bool ok = false;
    double requiredStorageGB = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "requiredStorageGB" )
                                    .toDouble( &ok );
    // We require a little more for partitioning overhead and swap file
    double advisedStorageGB = requiredStorageGB + 0.5 + 2.0;
    qint64 availableStorageB = candidate->available();

    qint64 advisedStorageB = CalamaresUtils::GiBtoBytes( advisedStorageGB );

    if ( ok &&
         availableStorageB > advisedStorageB )
    {
        cDebug() << "Partition" << convenienceName( candidate ) << "authorized for resize + autopartition install.";

        return true;
    }
    else if ( ok )
    {
        Logger::CDebug deb;
        deb << Logger::SubEntry << "NO, insufficient storage";
        deb << Logger::Continuation << "Required  storage B:" << advisedStorageB
                << QString( "(%1GB)" ).arg( advisedStorageGB );
        deb << Logger::Continuation << "Available storage B:" << availableStorageB
                << QString( "(%1GB)" ).arg( availableStorageB / 1024 / 1024 / 1024 )
                << "for" << convenienceName( candidate ) << "length:" << candidate->length()
                << "sectorsUsed:" << candidate->sectorsUsed() << "fsType:" << candidate->fileSystem().name();
        return false;
    }
    else
    {
        cDebug() << Logger::SubEntry << "NO, requiredStorageGB is not set correctly.";
        return false;
    }
}


bool
canBeResized( PartitionCoreModule* core, const QString& partitionPath )
{
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

        cDebug() << Logger::SubEntry << "reading" << fstabFile.fileName();

        if ( fstabFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            const QStringList fstabLines = QString::fromLocal8Bit( fstabFile.readAll() )
                                     .split( '\n' );

            for ( const QString& rawLine : fstabLines )
                fstabEntries.append( FstabEntry::fromEtcFstab( rawLine ) );
            fstabFile.close();
            cDebug() << Logger::SubEntry << "got" << fstabEntries.count() << "lines.";
            std::remove_if( fstabEntries.begin(), fstabEntries.end(), [](const FstabEntry& x) { return !x.isValid(); } );
            cDebug() << Logger::SubEntry << "got" << fstabEntries.count() << "fstab entries.";
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
    cDebug() << "Check EFI bootable" << convenienceName( candidate ) << candidate->devicePath();
    cDebug() << Logger::SubEntry << "flags" << candidate->activeFlags();

    auto flags = PartitionInfo::flags( candidate );

    /* If bit 17 is set, old-style Esp flag, it's OK */
    if ( flags.testFlag( KPM_PARTITION_FLAG_ESP ) )
        return true;

    /* Otherwise, if it's a GPT table, Boot (bit 0) is the same as Esp */
    const PartitionNode* root = candidate;
    while ( root && !root->isRoot() )
    {
        root = root->parent();
        cDebug() << Logger::SubEntry << "moved towards root" << (void *)root;
    }

    // Strange case: no root found, no partition table node?
    if ( !root )
        return false;

    const PartitionTable* table = dynamic_cast<const PartitionTable*>( root );
    cDebug() << Logger::SubEntry << "partition table" << (void *)table << "type" << ( table ? table->type() : PartitionTable::TableType::unknownTableType );
    return table && ( table->type() == PartitionTable::TableType::gpt ) &&
        flags.testFlag( KPM_PARTITION_FLAG(Boot) );
}

QString
findFS( QString fsName, FileSystem::Type* fsType )
{
    QStringList fsLanguage { QLatin1Literal( "C" ) };  // Required language list to turn off localization
    if ( fsName.isEmpty() )
        fsName = QStringLiteral( "ext4" );

    FileSystem::Type tmpType = FileSystem::typeForName( fsName, fsLanguage );
    if ( tmpType != FileSystem::Unknown )
    {
        cDebug() << "Found filesystem" << fsName;
        if ( fsType )
            *fsType = tmpType;
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
                *fsType = t;
            return fsRealName;
        }
    }

    cDebug() << "Filesystem" << fsName << "not found, using ext4";
    fsName = QStringLiteral( "ext4" );
    // fsType can be used to check whether fsName was a valid filesystem.
    if (fsType)
        *fsType = FileSystem::Unknown;
#ifdef DEBUG_FILESYSTEMS
    // This bit is for distro's debugging their settings, and shows
    // all the strings that KPMCore is matching against for FS type.
    {
        Logger::CDebug d;
        using TR = Logger::DebugRow< int, QString >;
        const auto fstypes = FileSystem::types();
        d << "Available types (" << fstypes.count() << ')';
        for ( FileSystem::Type t : fstypes )
            d << TR( static_cast<int>( t ), FileSystem::nameForType( t, fsLanguage ) );
    }
#endif
    return fsName;
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
