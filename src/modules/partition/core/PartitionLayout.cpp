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

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

static FileSystem::Type
getDefaultFileSystemType()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    FileSystem::Type defaultFS = FileSystem::Ext4;

    if ( gs->contains( "defaultFileSystemType" ) )
    {
        PartUtils::findFS( gs->value( "defaultFileSystemType" ).toString(), &defaultFS );
        if ( defaultFS == FileSystem::Unknown )
        {
            defaultFS = FileSystem::Ext4;
        }
    }

    return defaultFS;
}

PartitionLayout::PartitionLayout()
{
    m_defaultFsType = getDefaultFileSystemType();
}

PartitionLayout::PartitionLayout( PartitionLayout::PartitionEntry entry )
{
    m_defaultFsType = getDefaultFileSystemType();
    m_partLayout.append( entry );
}

PartitionLayout::PartitionLayout( const PartitionLayout& layout )
    : m_defaultFsType( layout.m_defaultFsType )
    , m_partLayout( layout.m_partLayout )
{
}

PartitionLayout::~PartitionLayout() {}

bool
PartitionLayout::addEntry( PartitionLayout::PartitionEntry entry )
{
    if ( !entry.isValid() )
    {
        cError() << "Partition size is invalid or has min size > max size";
        return false;
    }

    m_partLayout.append( entry );

    return true;
}

PartitionLayout::PartitionEntry::PartitionEntry()
    : partAttributes( 0 )
{
}

PartitionLayout::PartitionEntry::PartitionEntry( const QString& size, const QString& min, const QString& max )
    : partSize( size )
    , partMinSize( min )
    , partMaxSize( max )
    , partAttributes( 0 )
{
}

bool
PartitionLayout::addEntry( const QString& mountPoint, const QString& size, const QString& min, const QString& max )
{
    PartitionLayout::PartitionEntry entry( size, min, max );

    if ( !entry.isValid() )
    {
        cError() << "Partition size" << size << "is invalid or" << min << ">" << max;
        return false;
    }
    if ( mountPoint.isEmpty() || !mountPoint.startsWith( QString( "/" ) ) )
    {
        cError() << "Partition mount point" << mountPoint << "is invalid";
        return false;
    }

    entry.partMountPoint = mountPoint;
    entry.partFileSystem = m_defaultFsType;

    m_partLayout.append( entry );

    return true;
}

bool
PartitionLayout::addEntry( const QString& label,
                           const QString& uuid,
                           const QString& type,
                           quint64 attributes,
                           const QString& mountPoint,
                           const QString& fs,
                           const QVariantMap& features,
                           const QString& size,
                           const QString& min,
                           const QString& max )
{
    PartitionLayout::PartitionEntry entry( size, min, max );

    if ( !entry.isValid() )
    {
        cError() << "Partition size" << size << "is invalid or" << min << ">" << max;
        return false;
    }
    if ( mountPoint.isEmpty() || !mountPoint.startsWith( QString( "/" ) ) )
    {
        cError() << "Partition mount point" << mountPoint << "is invalid";
        return false;
    }

    entry.partLabel = label;
    entry.partUUID = uuid;
    entry.partType = type;
    entry.partAttributes = attributes;
    entry.partMountPoint = mountPoint;
    PartUtils::findFS( fs, &entry.partFileSystem );
    if ( entry.partFileSystem == FileSystem::Unknown )
    {
        entry.partFileSystem = m_defaultFsType;
    }
    entry.partFeatures = features;

    m_partLayout.append( entry );

    return true;
}

QList< Partition* >
PartitionLayout::execute( Device* dev,
                          qint64 firstSector,
                          qint64 lastSector,
                          QString luksPassphrase,
                          PartitionNode* parent,
                          const PartitionRole& role )
{
    QList< Partition* > partList;
    // Map each partition entry to its requested size (0 when calculated later)
    QMap< const PartitionLayout::PartitionEntry*, qint64 > partSizeMap;
    qint64 totalSize = lastSector - firstSector + 1;
    qint64 availableSize = totalSize;

    // Let's check if we have enough space for each partSize
    for ( const auto& part : qAsConst( m_partLayout ) )
    {
        qint64 size;
        // Calculate partition size

        if ( part.partSize.isValid() )
        {
            // We need to ignore the percent-defined
            if ( part.partSize.unit() != CalamaresUtils::Partition::SizeUnit::Percent )
            {
                size = part.partSize.toSectors( totalSize, dev->logicalSize() );
            }
            else
            {
                if ( part.partMinSize.isValid() )
                {
                    size = part.partMinSize.toSectors( totalSize, dev->logicalSize() );
                }
                else
                {
                    size = 0;
                }
            }
        }
        else
        {
            cWarning() << "Partition" << part.partMountPoint << "size (" << size << "sectors) is invalid, skipping...";
            continue;
        }

        partSizeMap.insert( &part, size );
        availableSize -= size;
    }

    // Use partMinSize and see if we can do better afterward.
    if ( availableSize < 0 )
    {
        availableSize = totalSize;
        for ( const auto& part : qAsConst( m_partLayout ) )
        {
            qint64 size;

            if ( part.partMinSize.isValid() )
            {
                size = part.partMinSize.toSectors( totalSize, dev->logicalSize() );
            }
            else if ( part.partSize.isValid() )
            {
                if ( part.partSize.unit() != CalamaresUtils::Partition::SizeUnit::Percent )
                {
                    size = part.partSize.toSectors( totalSize, dev->logicalSize() );
                }
                else
                {
                    size = 0;
                }
            }
            else
            {
                size = 0;
            }

            partSizeMap.insert( &part, size );
            availableSize -= size;
        }
    }

    // Assign size for percentage-defined partitions
    for ( const auto& part : qAsConst( m_partLayout ) )
    {
        if ( part.partSize.unit() == CalamaresUtils::Partition::SizeUnit::Percent )
        {
            qint64 size = partSizeMap.value( &part );
            size = part.partSize.toSectors( availableSize + size, dev->logicalSize() );
            if ( part.partMinSize.isValid() )
            {
                qint64 minSize = part.partMinSize.toSectors( totalSize, dev->logicalSize() );
                if ( minSize > size )
                {
                    size = minSize;
                }
            }
            if ( part.partMaxSize.isValid() )
            {
                qint64 maxSize = part.partMaxSize.toSectors( totalSize, dev->logicalSize() );
                if ( maxSize < size )
                {
                    size = maxSize;
                }
            }

            partSizeMap.insert( &part, size );
        }
    }

    availableSize = totalSize;

    // TODO: Refine partition sizes to make sure there is room for every partition
    // Use a default (200-500M ?) minimum size for partition without minSize

    for ( const auto& part : qAsConst( m_partLayout ) )
    {
        qint64 size, end;
        Partition* currentPartition = nullptr;

        size = partSizeMap.value( &part );

        // Adjust partition size based on available space
        if ( size > availableSize )
        {
            size = availableSize;
        }

        end = firstSector + std::max( size - 1, Q_INT64_C( 0 ) );

        if ( luksPassphrase.isEmpty() )
        {
            currentPartition = KPMHelpers::createNewPartition(
                parent, *dev, role, part.partFileSystem, firstSector, end, KPM_PARTITION_FLAG( None ) );
        }
        else
        {
            currentPartition = KPMHelpers::createNewEncryptedPartition(
                parent, *dev, role, part.partFileSystem, firstSector, end, luksPassphrase, KPM_PARTITION_FLAG( None ) );
        }
        PartitionInfo::setFormat( currentPartition, true );
        PartitionInfo::setMountPoint( currentPartition, part.partMountPoint );
        if ( !part.partLabel.isEmpty() )
        {
            currentPartition->setLabel( part.partLabel );
            currentPartition->fileSystem().setLabel( part.partLabel );
        }
        if ( !part.partUUID.isEmpty() )
        {
            currentPartition->setUUID( part.partUUID );
        }
        if ( !part.partType.isEmpty() )
        {
#if defined( WITH_KPMCORE42API )
            currentPartition->setType( part.partType );
#else
            cWarning() << "Ignoring type; requires KPMcore >= 4.2.0.";
#endif
        }
        if ( part.partAttributes )
        {
#if defined( WITH_KPMCORE42API )
            currentPartition->setAttributes( part.partAttributes );
#else
            cWarning() << "Ignoring attributes; requires KPMcore >= 4.2.0.";
#endif
        }
        if ( !part.partFeatures.isEmpty() )
        {
#if defined( WITH_KPMCORE42API )
            for ( const auto& k : part.partFeatures.keys() )
            {
                currentPartition->fileSystem().addFeature( k, part.partFeatures.value( k ) );
            }
#else
            cWarning() << "Ignoring features; requires KPMcore >= 4.2.0.";
#endif
        }
        // Some buggy (legacy) BIOSes test if the bootflag of at least one partition is set.
        // Otherwise they ignore the device in boot-order, so add it here.
        partList.append( currentPartition );
        firstSector = end + 1;
        availableSize -= size;
    }

    return partList;
}
