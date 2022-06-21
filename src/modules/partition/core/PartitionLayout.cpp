/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/Logger.h"

#include "core/PartitionLayout.h"

#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "core/PartitionActions.h"
#include "core/PartitionInfo.h"

#include "utils/Variant.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

PartitionLayout::PartitionLayout() {}

PartitionLayout::PartitionLayout( const PartitionLayout& layout )
    : m_partLayout( layout.m_partLayout )
{
}

PartitionLayout::~PartitionLayout() {}

PartitionLayout::PartitionEntry::PartitionEntry()
    : partAttributes( 0 )
{
}

PartitionLayout::PartitionEntry::PartitionEntry( FileSystem::Type fs,
                                                 const QString& mountPoint,
                                                 const QString& size,
                                                 const QString& minSize,
                                                 const QString& maxSize )
    : partAttributes( 0 )
    , partMountPoint( mountPoint )
    , partFileSystem( fs )
    , partSize( size )
    , partMinSize( minSize )
    , partMaxSize( maxSize )
{
}

PartitionLayout::PartitionEntry::PartitionEntry( const QString& label,
                                                 const QString& uuid,
                                                 const QString& type,
                                                 quint64 attributes,
                                                 const QString& mountPoint,
                                                 const QString& fs,
                                                 const QVariantMap& features,
                                                 const QString& size,
                                                 const QString& minSize,
                                                 const QString& maxSize )
    : partLabel( label )
    , partUUID( uuid )
    , partType( type )
    , partAttributes( attributes )
    , partMountPoint( mountPoint )
    , partFeatures( features )
    , partSize( size )
    , partMinSize( minSize )
    , partMaxSize( maxSize )
{
    PartUtils::canonicalFilesystemName( fs, &partFileSystem );
}


bool
PartitionLayout::addEntry( const PartitionEntry& entry )
{
    if ( !entry.isValid() )
    {
        return false;
    }

    m_partLayout.append( entry );

    return true;
}

void
PartitionLayout::init( FileSystem::Type defaultFsType, const QVariantList& config )
{
    bool ok = true;  // bogus argument to getSubMap()

    m_partLayout.clear();

    for ( const auto& r : config )
    {
        QVariantMap pentry = r.toMap();

        if ( !pentry.contains( "name" ) || !pentry.contains( "size" ) )
        {
            cError() << "Partition layout entry #" << config.indexOf( r )
                     << "lacks mandatory attributes, switching to default layout.";
            m_partLayout.clear();
            break;
        }

        if ( !addEntry( { CalamaresUtils::getString( pentry, "name" ),
                          CalamaresUtils::getString( pentry, "uuid" ),
                          CalamaresUtils::getString( pentry, "type" ),
                          CalamaresUtils::getUnsignedInteger( pentry, "attributes", 0 ),
                          CalamaresUtils::getString( pentry, "mountPoint" ),
                          CalamaresUtils::getString( pentry, "filesystem", "unformatted" ),
                          CalamaresUtils::getSubMap( pentry, "features", ok ),
                          CalamaresUtils::getString( pentry, "size", QStringLiteral( "0" ) ),
                          CalamaresUtils::getString( pentry, "minSize", QStringLiteral( "0" ) ),
                          CalamaresUtils::getString( pentry, "maxSize", QStringLiteral( "0" ) ) } ) )
        {
            cError() << "Partition layout entry #" << config.indexOf( r ) << "is invalid, switching to default layout.";
            m_partLayout.clear();
            break;
        }
    }

    if ( !m_partLayout.count() )
    {
        // Unknown will be translated to defaultFsType at apply-time
        addEntry( { FileSystem::Type::Unknown, QString( "/" ), QString( "100%" ) } );
    }

    setDefaultFsType( defaultFsType );
}

void
PartitionLayout::setDefaultFsType( FileSystem::Type defaultFsType )
{
    using FileSystem = FileSystem::Type;
    QT_WARNING_PUSH
    QT_WARNING_DISABLE_CLANG( "-Wswitch-enum" )
    switch ( defaultFsType )
    {
    case FileSystem::Unknown:
    case FileSystem::Unformatted:
    case FileSystem::Extended:
    case FileSystem::LinuxSwap:
    case FileSystem::Luks:
    case FileSystem::Ocfs2:
    case FileSystem::Lvm2_PV:
    case FileSystem::Udf:
    case FileSystem::Iso9660:
    case FileSystem::Luks2:
    case FileSystem::LinuxRaidMember:
    case FileSystem::BitLocker:
        // bad bad
        cWarning() << "The selected default FS" << defaultFsType << "is not suitable."
                   << "Using ext4 instead.";
        defaultFsType = FileSystem::Ext4;
        break;
    case FileSystem::Ext2:
    case FileSystem::Ext3:
    case FileSystem::Ext4:
    case FileSystem::Fat32:
    case FileSystem::Ntfs:
    case FileSystem::Reiser4:
    case FileSystem::ReiserFS:
    case FileSystem::Xfs:
    case FileSystem::Jfs:
    case FileSystem::Btrfs:
    case FileSystem::Exfat:
    case FileSystem::F2fs:
        // ok
        break;
    case FileSystem::Fat16:
    case FileSystem::Hfs:
    case FileSystem::HfsPlus:
    case FileSystem::Ufs:
    case FileSystem::Hpfs:
    case FileSystem::Zfs:
    case FileSystem::Nilfs2:
    case FileSystem::Fat12:
    case FileSystem::Apfs:
    case FileSystem::Minix:
        // weird
        cWarning() << "The selected default FS" << defaultFsType << "is unusual, but not wrong.";
        break;
    default:
        cWarning() << "The selected default FS" << defaultFsType << "is not known to Calamares."
                   << "Using ext4 instead.";
        defaultFsType = FileSystem::Ext4;
    }
    QT_WARNING_POP

    m_defaultFsType = defaultFsType;
}


QList< Partition* >
PartitionLayout::createPartitions( Device* dev,
                                   qint64 firstSector,
                                   qint64 lastSector,
                                   QString luksPassphrase,
                                   PartitionNode* parent,
                                   const PartitionRole& role )
{
    // Make sure the default FS is sensible; warn and use ext4 if not
    setDefaultFsType( m_defaultFsType );

    QList< Partition* > partList;
    // Map each partition entry to its requested size (0 when calculated later)
    QMap< const PartitionLayout::PartitionEntry*, qint64 > partSectorsMap;
    const qint64 totalSectors = lastSector - firstSector + 1;
    qint64 currentSector, availableSectors = totalSectors;

    // Let's check if we have enough space for each partitions, using the size
    // propery or the min-size property if unit is in percentage.
    for ( const auto& entry : qAsConst( m_partLayout ) )
    {
        if ( !entry.partSize.isValid() )
        {
            cWarning() << "Partition" << entry.partMountPoint << "size is invalid, skipping...";
            continue;
        }

        // Calculate partition size: Rely on "possibly uninitialized use"
        // warnings to ensure that all the cases are covered below.
        // We need to ignore the percent-defined until later
        qint64 sectors = 0;
        if ( entry.partSize.unit() != CalamaresUtils::Partition::SizeUnit::Percent )
        {
            sectors = entry.partSize.toSectors( totalSectors, dev->logicalSize() );
        }
        else if ( entry.partMinSize.isValid() )
        {
            sectors = entry.partMinSize.toSectors( totalSectors, dev->logicalSize() );
        }
        partSectorsMap.insert( &entry, sectors );
        availableSectors -= sectors;
    }

    // There is not enough space for all partitions, use the min-size property
    // and see if we can do better afterward.
    if ( availableSectors < 0 )
    {
        availableSectors = totalSectors;
        for ( const auto& entry : qAsConst( m_partLayout ) )
        {
            qint64 sectors = partSectorsMap.value( &entry );
            if ( entry.partMinSize.isValid() )
            {
                sectors = entry.partMinSize.toSectors( totalSectors, dev->logicalSize() );
                partSectorsMap.insert( &entry, sectors );
            }
            availableSectors -= sectors;
        }
    }

    // Assign sectors for percentage-defined partitions.
    for ( const auto& entry : qAsConst( m_partLayout ) )
    {
        if ( entry.partSize.unit() == CalamaresUtils::Partition::SizeUnit::Percent )
        {
            qint64 sectors
                = entry.partSize.toSectors( availableSectors + partSectorsMap.value( &entry ), dev->logicalSize() );
            if ( entry.partMinSize.isValid() )
            {
                sectors = std::max( sectors, entry.partMinSize.toSectors( totalSectors, dev->logicalSize() ) );
            }
            if ( entry.partMaxSize.isValid() )
            {
                sectors = std::min( sectors, entry.partMaxSize.toSectors( totalSectors, dev->logicalSize() ) );
            }
            partSectorsMap.insert( &entry, sectors );
        }
    }

    auto correctFS = [ d = m_defaultFsType ]( FileSystem::Type t ) { return t == FileSystem::Type::Unknown ? d : t; };

    // Create the partitions.
    currentSector = firstSector;
    availableSectors = totalSectors;
    for ( const auto& entry : qAsConst( m_partLayout ) )
    {
        // Adjust partition size based on available space.
        qint64 sectors = partSectorsMap.value( &entry );
        sectors = std::min( sectors, availableSectors );
        if ( sectors == 0 )
        {
            continue;
        }

        Partition* part = nullptr;

        // Encryption for zfs is handled in the zfs module
        if ( luksPassphrase.isEmpty() || correctFS( entry.partFileSystem ) == FileSystem::Zfs )
        {
            part = KPMHelpers::createNewPartition( parent,
                                                   *dev,
                                                   role,
                                                   correctFS( entry.partFileSystem ),
                                                   entry.partLabel,
                                                   currentSector,
                                                   currentSector + sectors - 1,
                                                   KPM_PARTITION_FLAG( None ) );
        }
        else
        {
            part = KPMHelpers::createNewEncryptedPartition( parent,
                                                            *dev,
                                                            role,
                                                            correctFS( entry.partFileSystem ),
                                                            entry.partLabel,
                                                            currentSector,
                                                            currentSector + sectors - 1,
                                                            luksPassphrase,
                                                            KPM_PARTITION_FLAG( None ) );
        }

        // For zfs, we need to make the passphrase available to later modules
        if ( correctFS( entry.partFileSystem ) == FileSystem::Zfs )
        {
            Calamares::GlobalStorage* storage = Calamares::JobQueue::instance()->globalStorage();
            QList< QVariant > zfsInfoList;
            QVariantMap zfsInfo;

            // Save the information subsequent modules will need
            zfsInfo[ "encrypted" ] = !luksPassphrase.isEmpty();
            zfsInfo[ "passphrase" ] = luksPassphrase;
            zfsInfo[ "mountpoint" ] = entry.partMountPoint;

            // Add it to the list and insert it into global storage
            zfsInfoList.append( zfsInfo );
            storage->insert( "zfsInfo", zfsInfoList );
        }

        PartitionInfo::setFormat( part, true );
        PartitionInfo::setMountPoint( part, entry.partMountPoint );
        if ( !entry.partLabel.isEmpty() )
        {
            part->setLabel( entry.partLabel );
            part->fileSystem().setLabel( entry.partLabel );
        }
        if ( !entry.partUUID.isEmpty() )
        {
            part->setUUID( entry.partUUID );
        }
        if ( !entry.partType.isEmpty() )
        {
            part->setType( entry.partType );
        }
        if ( entry.partAttributes )
        {
            part->setAttributes( entry.partAttributes );
        }
        if ( !entry.partFeatures.isEmpty() )
        {
            for ( const auto& k : entry.partFeatures.keys() )
            {
                part->fileSystem().addFeature( k, entry.partFeatures.value( k ) );
            }
        }
        // Some buggy (legacy) BIOSes test if the bootflag of at least one partition is set.
        // Otherwise they ignore the device in boot-order, so add it here.
        partList.append( part );
        currentSector += sectors;
        availableSectors -= sectors;
    }

    return partList;
}
