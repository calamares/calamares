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
#ifndef PMUTILS_H
#define PMUTILS_H

// CalaPM
#include <fs/filesystem.h>

// Qt
#include <QList>

class Device;
class Partition;
class PartitionNode;
class PartitionRole;

/**
 * Helper functions to manipulate partitions
 */
namespace PMUtils
{

bool isPartitionFreeSpace( Partition* );

/**
 * Returns true if the partition is planned to be created by the installer as
 * opposed to already existing on the disk.
 */
bool isPartitionNew( Partition* );

/**
 * Iterates on all devices and return the first partition which is associated
 * with mountPoint. This uses PartitionInfo::mountPoint(), not Partition::mountPoint()
 */
Partition* findPartitionByMountPoint( const QList< Device* >& devices, const QString& mountPoint );

/**
 * Helper function to create a new Partition object (does not create anything
 * on the disk) associated with a FileSystem.
 */
Partition* createNewPartition( PartitionNode* parent, const Device& device, const PartitionRole& role, FileSystem::Type fsType, qint64 firstSector, qint64 lastSector );

Partition* clonePartition( Device* device, Partition* partition );
}

#endif /* PMUTILS_H */
