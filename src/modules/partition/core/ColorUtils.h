/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

}

#endif /* COLORUTILS_H */
