/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "PartitionIterator.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>

namespace CalamaresUtils
{
namespace Partition
{

using Partition = ::Partition;

PartitionIterator::PartitionIterator( PartitionTable* table )
    : m_table( table )
{
}

Partition*
PartitionIterator::operator*() const
{
    return m_current;
}

void
PartitionIterator::operator++()
{
    if ( !m_current )
    {
        return;
    }
    if ( m_current->hasChildren() )
    {
        // Go to the first child
        m_current = static_cast< Partition* >( m_current->children().first() );
        return;
    }
    PartitionNode* parent = m_current->parent();
    Partition* successor = parent->successor( *m_current );
    if ( successor )
    {
        // Go to the next sibling
        m_current = successor;
        return;
    }
    if ( parent->isRoot() )
    {
        // We reached the end
        m_current = nullptr;
        return;
    }
    // Try to go to the next sibling of our parent

    PartitionNode* grandParent = parent->parent();
    Q_ASSERT( grandParent );
    // If parent is not root, then it's not a PartitionTable but a
    // Partition, we can static_cast it.
    m_current = grandParent->successor( *static_cast< Partition* >( parent ) );
}

bool
PartitionIterator::operator==( const PartitionIterator& other ) const
{
    return m_table == other.m_table && m_current == other.m_current;
}

bool
PartitionIterator::operator!=( const PartitionIterator& other ) const
{
    return !( *this == other );
}

PartitionIterator
PartitionIterator::begin( Device* device )
{
    if ( !device )
    {
        return PartitionIterator( nullptr );
    }
    PartitionTable* table = device->partitionTable();
    if ( !table )
    {
        return PartitionIterator( nullptr );
    }
    return PartitionIterator::begin( table );
}

PartitionIterator
PartitionIterator::begin( PartitionTable* table )
{
    auto it = PartitionIterator( table );
    QList< Partition* > children = table->children();
    // Does not usually happen, but it did happen on a tiny (10MiB) disk with an MBR
    // partition table.
    if ( children.isEmpty() )
    {
        return it;
    }
    it.m_current = children.first();
    return it;
}

PartitionIterator
PartitionIterator::end( Device* device )
{
    if ( !device )
    {
        return PartitionIterator( nullptr );
    }
    PartitionTable* table = device->partitionTable();
    if ( !table )
    {
        return PartitionIterator( nullptr );
    }

    return PartitionIterator::end( table );
}

PartitionIterator
PartitionIterator::end( PartitionTable* table )
{
    return PartitionIterator( table );
}

}  // namespace Partition
}  // namespace CalamaresUtils
