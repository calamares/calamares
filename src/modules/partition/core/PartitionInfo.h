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
#ifndef PARTITIONINFO_H
#define PARTITIONINFO_H

#include <QHash>
#include <QString>

class Partition;

/**
 * Functions to store Calamares-specific information in the Qt properties of a
 * Partition object.
 *
 * See README.md for the rational behind this design.
 *
 * Properties:
 * - mountPoint: which directory will a partition be mounted on the installed
 *   system. This is different from Partition::mountPoint, which is the
 *   directory on which a partition is *currently* mounted while the installer
 *   is running.
 * - format: whether this partition should be formatted at install time.
 */
namespace PartitionInfo
{

QString mountPoint( Partition* partition );
void setMountPoint( Partition* partition, const QString& value );

bool format( Partition* partition );
void setFormat( Partition* partition, bool value );

void reset( Partition* partition );

/**
 * Returns true if one of the property has been set. This information is used
 * by the UI to decide whether the "Revert" button should be enabled or
 * disabled.
 */
bool isDirty( Partition* partition );

};

#endif /* PARTITIONINFO_H */
