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

#include <core/PartitionIterator.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>

PartitionIterator::PartitionIterator( Device* device )
    : m_device( device )
{}

Partition*
PartitionIterator::operator*() const
{
    return m_current;
}

void
PartitionIterator::operator++()
{
    if ( !m_current )
        return;
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
    return m_device == other.m_device && m_current == other.m_current;
}

bool
PartitionIterator::operator!=( const PartitionIterator& other ) const
{
    return ! ( *this == other );
}

PartitionIterator
PartitionIterator::begin( Device* device )
{
    auto it = PartitionIterator( device );
    PartitionTable* table = device->partitionTable();
    if ( !table )
        return it;
    QList< Partition* > children = table->children();
    // Does not usually happen, but it did happen on a 10MB disk with an MBR
    // partition table.
    if ( children.isEmpty() )
        return it;
    it.m_current = children.first();
    return it;
}

PartitionIterator
PartitionIterator::end( Device* device )
{
    return PartitionIterator( device );
}
