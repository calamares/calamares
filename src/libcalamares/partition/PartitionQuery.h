/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
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
class PartitionTable;

namespace CalamaresUtils
{
namespace Partition
{

using ::Device;
using ::Partition;
using ::PartitionTable;

/** @brief Get partition table */
const PartitionTable* getPartitionTable( const Partition* partition );

/** @brief Is this a free-space area? */
bool isPartitionFreeSpace( const Partition* );

/** @brief Is this partition newly-to-be-created?
 *
 * Returns true if the partition is planned to be created by the installer as
 * opposed to already existing on the disk.
 */
bool isPartitionNew( const Partition* );

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
