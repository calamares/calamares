/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/ColorUtils.h"

#include "core/KPMHelpers.h"

#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/luks.h>

// Qt
#include <QColor>
#include <QMap>

using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::isPartitionNew;
using CalamaresUtils::Partition::PartitionIterator;

static const int NUM_PARTITION_COLORS = 5;
static const int NUM_NEW_PARTITION_COLORS = 4;
//Let's try to use the Breeze palette
static const QColor PARTITION_COLORS[ NUM_PARTITION_COLORS ] = {
    "#2980b9",  //Dark Plasma Blue
    "#27ae60",  //Dark Icon Green
    "#c9ce3b",  //Dirty Yellow
    "#3daee9",  //Plasma Blue
    "#9b59b6",  //Purple
};
static const QColor NEW_PARTITION_COLORS[ NUM_NEW_PARTITION_COLORS ] = {
    "#c0392b",  //Dark Icon Red
    "#f39c1f",  //Dark Icon Yellow
    "#f1b7bc",  //Light Salmon
    "#fed999",  //Light Orange
};
static QColor FREE_SPACE_COLOR = "#777777";
static QColor EXTENDED_COLOR = "#aaaaaa";
static QColor UNKNOWN_DISKLABEL_COLOR = "#4d4151";

static QMap< QString, QColor > s_partitionColorsCache;


namespace ColorUtils
{

QColor
freeSpaceColor()
{
    return FREE_SPACE_COLOR;
}

QColor
unknownDisklabelColor()
{
    return UNKNOWN_DISKLABEL_COLOR;
}

PartitionNode*
_findRootForPartition( PartitionNode* partition )
{
    if ( partition->isRoot() || !partition->parent() )
    {
        return partition;
    }

    return _findRootForPartition( partition->parent() );
}

QColor
colorForPartition( Partition* partition )
{
    if ( !partition )
    {
        cWarning() << "NULL partition";
        return FREE_SPACE_COLOR;
    }

    if ( isPartitionFreeSpace( partition ) )
    {
        return FREE_SPACE_COLOR;
    }
    if ( partition->roles().has( PartitionRole::Extended ) )
    {
        return EXTENDED_COLOR;
    }

    if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
         && !partition->fileSystem().uuid().isEmpty() )
    {
        if ( partition->fileSystem().type() == FileSystem::Luks )
        {
            FS::luks& luksFs = dynamic_cast< FS::luks& >( partition->fileSystem() );
            if ( !luksFs.outerUuid().isEmpty() && s_partitionColorsCache.contains( luksFs.outerUuid() ) )
            {
                return s_partitionColorsCache[ luksFs.outerUuid() ];
            }
        }

        if ( s_partitionColorsCache.contains( partition->fileSystem().uuid() ) )
        {
            return s_partitionColorsCache[ partition->fileSystem().uuid() ];
        }
    }

    // No partition-specific color needed, pick one from our list, but skip
    // free space: we don't want a partition to change colors if space before
    // it is inserted or removed
    PartitionNode* parent = _findRootForPartition( partition );
    PartitionTable* table = dynamic_cast< PartitionTable* >( parent );
    Q_ASSERT( table );
    int colorIdx = 0;
    int newColorIdx = 0;
    for ( PartitionIterator it = PartitionIterator::begin( table ); it != PartitionIterator::end( table ); ++it )
    {
        Partition* child = *it;
        if ( child == partition )
        {
            break;
        }
        if ( !isPartitionFreeSpace( child ) && !child->hasChildren() )
        {
            if ( isPartitionNew( child ) )
            {
                ++newColorIdx;
            }
            ++colorIdx;
        }
    }

    if ( isPartitionNew( partition ) )
    {
        return NEW_PARTITION_COLORS[ newColorIdx % NUM_NEW_PARTITION_COLORS ];
    }

    if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
         && !partition->fileSystem().uuid().isEmpty() )
    {
        if ( partition->fileSystem().type() == FileSystem::Luks )
        {
            FS::luks& luksFs = dynamic_cast< FS::luks& >( partition->fileSystem() );
            if ( !luksFs.outerUuid().isEmpty() )
            {
                s_partitionColorsCache.insert( luksFs.outerUuid(),
                                               PARTITION_COLORS[ colorIdx % NUM_PARTITION_COLORS ] );
            }
        }
        else
            s_partitionColorsCache.insert( partition->fileSystem().uuid(),
                                           PARTITION_COLORS[ colorIdx % NUM_PARTITION_COLORS ] );
    }
    return PARTITION_COLORS[ colorIdx % NUM_PARTITION_COLORS ];
}


QColor
colorForPartitionInFreeSpace( Partition* partition )
{
    PartitionNode* parent = _findRootForPartition( partition );
    PartitionTable* table = dynamic_cast< PartitionTable* >( parent );
    Q_ASSERT( table );
    int newColorIdx = 0;
    for ( PartitionIterator it = PartitionIterator::begin( table ); it != PartitionIterator::end( table ); ++it )
    {
        Partition* child = *it;
        if ( child == partition )
        {
            break;
        }
        if ( !isPartitionFreeSpace( child ) && !child->hasChildren() && isPartitionNew( child ) )
        {
            ++newColorIdx;
        }
    }
    return NEW_PARTITION_COLORS[ newColorIdx % NUM_NEW_PARTITION_COLORS ];
}


void
invalidateCache()
{
    s_partitionColorsCache.clear();
}

}  // namespace ColorUtils
