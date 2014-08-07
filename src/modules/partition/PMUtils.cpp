/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <PMUtils.h>

#include <PartitionInfo.h>
#include <PartitionIterator.h>

// CalaPM
#include <core/partition.h>
#include <fs/filesystemfactory.h>

namespace PMUtils
{

bool isPartitionFreeSpace( Partition* partition )
{
    return partition->roles().has( PartitionRole::Unallocated );
}

bool isPartitionNew( Partition* partition )
{
    return partition->state() == Partition::StateNew;
}

Partition*
findPartitionByMountPoint( const QList< Device* >& devices, const QString& mountPoint )
{
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( PartitionInfo::mountPoint( *it ) == mountPoint )
                return *it;
    return nullptr;
}

Partition*
createNewPartition( PartitionNode* parent, const Device& device, const PartitionRole& role, FileSystem::Type fsType, qint64 firstSector, qint64 lastSector )
{
    FileSystem* fs = FileSystemFactory::create( fsType, firstSector, lastSector );
    return new Partition(
               parent,
               device,
               role,
               fs, fs->firstSector(), fs->lastSector(),
               QString() /* path */,
               PartitionTable::FlagNone /* availableFlags */,
               QString() /* mountPoint */,
               false /* mounted */,
               PartitionTable::FlagNone /* activeFlags */,
               Partition::StateNew
           );
}

Partition*
clonePartition( Device* device, Partition* partition )
{
    FileSystem* fs = FileSystemFactory::create(
                         partition->fileSystem().type(),
                         partition->firstSector(),
                         partition->lastSector()
                     );
    return new Partition(
        partition->parent(),
        *device,
        partition->roles(),
        fs, fs->firstSector(), fs->lastSector(),
        partition->partitionPath()
    );
}

} // namespace
