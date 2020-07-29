/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018-2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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
    qint64 minSize, maxSize, end;
    qint64 totalSize = lastSector - firstSector + 1;
    qint64 availableSize = totalSize;

    // TODO: Refine partition sizes to make sure there is room for every partition
    // Use a default (200-500M ?) minimum size for partition without minSize

    foreach ( const PartitionLayout::PartitionEntry& part, m_partLayout )
    {
        Partition* currentPartition = nullptr;

        qint64 size = -1;
        // Calculate partition size
        if ( part.partSize.isValid() )
        {
            size = part.partSize.toSectors( totalSize, dev->logicalSize() );
        }
        else
        {
            cWarning() << "Partition" << part.partMountPoint << "size (" << size << "sectors) is invalid, skipping...";
            continue;
        }

        if ( part.partMinSize.isValid() )
        {
            minSize = part.partMinSize.toSectors( totalSize, dev->logicalSize() );
        }
        else
        {
            minSize = 0;
        }

        if ( part.partMaxSize.isValid() )
        {
            maxSize = part.partMaxSize.toSectors( totalSize, dev->logicalSize() );
        }
        else
        {
            maxSize = availableSize;
        }

        // Make sure we never go under minSize once converted to sectors
        if ( maxSize < minSize )
        {
            cWarning() << "Partition" << part.partMountPoint << "max size (" << maxSize << "sectors) is < min size ("
                       << minSize << "sectors), using min size";
            maxSize = minSize;
        }

        // Adjust partition size based on user-defined boundaries and available space
        if ( size < minSize )
        {
            size = minSize;
        }
        if ( size > maxSize )
        {
            size = maxSize;
        }
        if ( size > availableSize )
        {
            size = availableSize;
        }
        end = firstSector + size - 1;

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
