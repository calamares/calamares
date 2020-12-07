/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#ifndef COLORUTILS_H
#define COLORUTILS_H

class QColor;

class Partition;

/**
 * Helper functions to define colors for partitions. It ensures no consecutive
 * partitions have the same color.
 */
namespace ColorUtils
{

QColor freeSpaceColor();

QColor unknownDisklabelColor();

/**
 * @brief colorForPartition iterates over partitions, caches their colors and returns
 * a color for the given partition.
 * @param partition the partition for which to return a color.
 * @return a color for the partition.
 */
QColor colorForPartition( Partition* partition );

/**
 * This is similar to colorForPartition() but returns the color of a partition
 * which would be created in freeSpacePartition
 */
QColor colorForPartitionInFreeSpace( Partition* freeSpacePartition );

/**
 * @brief invalidateCache clears the partition colors cache.
 */
void invalidateCache();

}  // namespace ColorUtils

#endif /* COLORUTILS_H */
