/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Collabora Ltd
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

#include "core/PartitionLayout.h"

#include "core/KPMHelpers.h"
#include "core/PartitionActions.h"
#include "core/PartitionInfo.h"
#include "core/PartUtils.h"

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
        PartUtils::findFS( gs->value( "defaultFileSystemType" ).toString(),  &defaultFS);
        if ( defaultFS == FileSystem::Unknown )
            defaultFS = FileSystem::Ext4;
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
    : m_partLayout( layout.m_partLayout )
    , m_defaultFsType( layout.m_defaultFsType )
{
}

PartitionLayout::~PartitionLayout()
{
}

void
PartitionLayout::addEntry( PartitionLayout::PartitionEntry entry )
{
    m_partLayout.append( entry );
}

PartitionLayout::PartitionEntry::PartitionEntry(const QString& size, const QString& min)
{
    partSize = PartUtils::parseSizeString( size , &partSizeUnit );
    if ( !min.isEmpty() )
        partMinSize = PartUtils::parseSizeString( min , &partMinSizeUnit );
}

void
PartitionLayout::addEntry( const QString& mountPoint, const QString& size, const QString& min )
{
    PartitionLayout::PartitionEntry entry( size, min );

    entry.partMountPoint = mountPoint;
    entry.partFileSystem = m_defaultFsType;

    m_partLayout.append( entry );
}

void
PartitionLayout::addEntry( const QString& label, const QString& mountPoint, const QString& fs, const QString& size, const QString& min )
{
    PartitionLayout::PartitionEntry entry( size, min );

    entry.partLabel = label;
    entry.partMountPoint = mountPoint;
    PartUtils::findFS( fs, &entry.partFileSystem );
    if ( entry.partFileSystem == FileSystem::Unknown )
        entry.partFileSystem = m_defaultFsType;

    m_partLayout.append( entry );
}

QList< Partition* >
PartitionLayout::execute( Device *dev, qint64 firstSector,
                          qint64 lastSector, QString luksPassphrase,
                          PartitionNode* parent,
                          const PartitionRole& role )
{
    QList< Partition* > partList;
    qint64 size, minSize, end;
    qint64 totalSize = lastSector - firstSector + 1;
    qint64 availableSize = totalSize;

    // TODO: Refine partition sizes to make sure there is room for every partition
    // Use a default (200-500M ?) minimum size for partition without minSize

    foreach( const PartitionLayout::PartitionEntry& part, m_partLayout )
    {
        Partition *currentPartition = nullptr;

        // Calculate partition size
        size = PartUtils::sizeToSectors( part.partSize, part.partSizeUnit, totalSize, dev->logicalSize() );
        minSize = PartUtils::sizeToSectors( part.partMinSize, part.partMinSizeUnit, totalSize, dev->logicalSize() );
        if ( size < minSize )
            size = minSize;
        if ( size > availableSize )
            size = availableSize;
        end = firstSector + size - 1;

        if ( luksPassphrase.isEmpty() )
        {
            currentPartition = KPMHelpers::createNewPartition(
                parent,
                *dev,
                role,
                part.partFileSystem,
                firstSector,
                end,
                PartitionTable::FlagNone
            );
        }
        else
        {
            currentPartition = KPMHelpers::createNewEncryptedPartition(
                parent,
                *dev,
                role,
                part.partFileSystem,
                firstSector,
                end,
                luksPassphrase,
                PartitionTable::FlagNone
            );
        }
        PartitionInfo::setFormat( currentPartition, true );
        PartitionInfo::setMountPoint( currentPartition, part.partMountPoint );
        if ( !part.partLabel.isEmpty() )
            currentPartition->fileSystem().setLabel( part.partLabel );
        // Some buggy (legacy) BIOSes test if the bootflag of at least one partition is set.
        // Otherwise they ignore the device in boot-order, so add it here.
        partList.append( currentPartition );
        firstSector = end + 1;
        availableSize -= size;
    }

    return partList;
}
