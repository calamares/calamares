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

#include <core/ColorUtils.h>

#include <core/PMUtils.h>

// CalaPM
#include <core/partition.h>

// Qt
#include <QColor>

static QColor COLORS[ 4 ] =
{
    "#448eca",
    "#a5cc42",
    "#d87e30",
    "#ffbdbd",
};
static QColor FREE_SPACE_COLOR = "#777777";
static QColor EXTENDED_COLOR = "#aaaaaa";


namespace ColorUtils
{

QColor freeSpaceColor()
{
    return FREE_SPACE_COLOR;
}

QColor colorForPartition( Partition* partition )
{
    if ( PMUtils::isPartitionFreeSpace( partition ) )
        return FREE_SPACE_COLOR;
    if ( partition->roles().has( PartitionRole::Extended ) )
        return EXTENDED_COLOR;
    // No partition-specific color needed, pick one from our list, but skip
    // free space: we don't want a partition to change colors if space before
    // it is inserted or removed
    PartitionNode* parent = partition->parent();
    Q_ASSERT( parent );
    int colorIdx = 0;
    for ( auto child : parent->children() )
    {
        if ( child == partition )
            break;
        if ( !PMUtils::isPartitionFreeSpace( child ) )
            ++colorIdx;
    }
    return COLORS[ colorIdx % 4 ];
}

QColor colorForPartitionInFreeSpace( Partition* partition )
{
    PartitionNode* parent = partition->parent();
    Q_ASSERT( parent );
    int colorIdx = 0;
    for ( auto child : parent->children() )
    {
        if ( child == partition )
            break;
        if ( !PMUtils::isPartitionFreeSpace( child ) )
            ++colorIdx;
    }
    return COLORS[ colorIdx % 4 ];
}

} // namespace
