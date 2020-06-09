/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */


/*
 * NOTE: this functionality is only available when Calamares is compiled
 *       with KPMcore support.
 */

#ifndef PARTITION_PARTITIONITERATOR_H
#define PARTITION_PARTITIONITERATOR_H

class Device;
class Partition;
class PartitionTable;

namespace CalamaresUtils
{
namespace Partition
{

/** @brief Iterator over KPMCore partitions
 *
 * A forward-only iterator to go through the partitions of a device,
 * independently of whether they are primary, logical or extended.
 *
 * An iterator can be created from a device (then it refers to the
 * partition table of that device) or a partition table. The
 * partition table must remain valid throughout iteration.
 *
 * A nullptr is valid, for an empty iterator.
 */
class PartitionIterator
{
public:
    ::Partition* operator*() const;

    void operator++();

    bool operator==( const PartitionIterator& other ) const;
    bool operator!=( const PartitionIterator& other ) const;

    static PartitionIterator begin( ::Device* device );
    static PartitionIterator begin( ::PartitionTable* table );
    static PartitionIterator end( ::Device* device );
    static PartitionIterator end( ::PartitionTable* table );

private:
    PartitionIterator( ::PartitionTable* table );

    ::PartitionTable* m_table;
    ::Partition* m_current = nullptr;
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif  // PARTITION_PARTITIONITERATOR_H
