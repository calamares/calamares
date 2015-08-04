/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#include "core/PMUtils.h"

#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"

// KPMcore
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystemfactory.h>

namespace PMUtils
{


bool
isPartitionFreeSpace( Partition* partition )
{
    return partition->roles().has( PartitionRole::Unallocated );
}


bool
isPartitionNew( Partition* partition )
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
findPartitionByPath( const QList< Device* >& devices, const QString& path )
{
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( ( *it )->partitionPath() == path.simplified() )
                return *it;
    return nullptr;
}


QList< Partition* >
findPartitions( const QList< Device* >& devices,
                std::function< bool ( Partition* ) > criterionFunction )
{
    QList< Partition* > results;
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( criterionFunction( *it ) )
                results.append( *it );
    return results;
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
