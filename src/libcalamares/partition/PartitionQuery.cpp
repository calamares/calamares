/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "PartitionQuery.h"

#include "PartitionIterator.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>

namespace CalamaresUtils
{
namespace Partition
{

// Types from KPMCore
using ::Device;
using ::Partition;

const PartitionTable*
getPartitionTable( const Partition* partition )
{
    const PartitionNode* root = partition;
    while ( root && !root->isRoot() )
    {
        root = root->parent();
    }

    return dynamic_cast< const PartitionTable* >( root );
}


bool
isPartitionFreeSpace( const Partition* partition )
{
    return partition->roles().has( PartitionRole::Unallocated );
}


bool
isPartitionNew( const Partition* partition )
{
    return partition->state() == Partition::State::New;
}


Partition*
findPartitionByCurrentMountPoint( const QList< Device* >& devices, const QString& mountPoint )
{
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( ( *it )->mountPoint() == mountPoint )
            {
                return *it;
            }
    return nullptr;
}


Partition*
findPartitionByPath( const QList< Device* >& devices, const QString& path )
{
    if ( path.simplified().isEmpty() )
    {
        return nullptr;
    }

    for ( auto device : devices )
    {
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        {
            if ( ( *it )->partitionPath() == path.simplified() )
            {
                return *it;
            }
        }
    }
    return nullptr;
}


QList< Partition* >
findPartitions( const QList< Device* >& devices, std::function< bool( Partition* ) > criterionFunction )
{
    QList< Partition* > results;
    for ( auto device : devices )
    {
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        {
            if ( criterionFunction( *it ) )
            {
                results.append( *it );
            }
        }
    }
    return results;
}


}  // namespace Partition
}  // namespace CalamaresUtils
