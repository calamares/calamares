/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014,      Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

/*
 * NOTE: this functionality is only available when Calamares is compiled
 *       with KPMcore support.
 */

#ifndef PARTITION_PARTITIONQUERY_H
#define PARTITION_PARTITIONQUERY_H

#include <QList>

#include <functional>

class Device;
class Partition;

namespace CalamaresUtils
{
namespace Partition
{

using ::Device;
using ::Partition;

/** @brief Is this a free-space area? */
bool isPartitionFreeSpace( Partition* );

/** @brief Is this partition newly-to-be-created?
 *
 * Returns true if the partition is planned to be created by the installer as
 * opposed to already existing on the disk.
 */
bool isPartitionNew( Partition* );

/**
 * Iterates on all devices and return the first partition which is (already)
 * mounted on @p mountPoint.
 */
Partition* findPartitionByCurrentMountPoint( const QList< Device* >& devices, const QString& mountPoint );

// TODO: add this distinction
// Partition* findPartitionByIntendedMountPoint( const QList< Device* >& devices, const QString& mountPoint );

/**
 * Iterates on all devices and partitions and returns a pointer to the Partition object
 * for the given path, or nullptr if a Partition for the given path cannot be found.
 */
Partition* findPartitionByPath( const QList< Device* >& devices, const QString& path );

/**
 * Iterates on all devices and partitions and returns a list of pointers to the Partition
 * objects that satisfy the conditions defined in the criterion function.
 */
QList< Partition* > findPartitions( const QList< Device* >& devices,
                                    std::function< bool( Partition* ) > criterionFunction );
}  // namespace Partition
}  // namespace CalamaresUtils

#endif  // PARTITION_PARTITIONQUERY_H
