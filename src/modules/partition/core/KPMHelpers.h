/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014,      Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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
#ifndef KPMHELPERS_H
#define KPMHELPERS_H

// KPMcore
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>

// Qt
#include <QList>

#include <functional>

class Device;
class Partition;
class PartitionNode;
class PartitionRole;

/**
 * Helper functions to manipulate partitions
 */
namespace KPMHelpers
{

/**
 * Thin wrapper on top of CoreBackendManager. Hides things like initializing the
 * Config instance or instantiating the backend.
 *
 * Initialize PartitionManager Config object and load a PartitionManager
 * backend. It loads the "libparted" plugin by default, but this can be
 * overloaded by settings the environment variable KPMCORE_BACKEND. Setting it to
 * "dummy" will load the dummy plugin instead.
 *
 * @return true if initialization was successful.
 */
bool initKPMcore();

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
 * Iterates on all devices and partitions and returns a pointer to the Partition object
 * for the given path, or nullptr if a Partition for the given path cannot be found.
 */
Partition* findPartitionByPath( const QList< Device* >& devices, const QString& path );

/**
 * Iterates on all devices and partitions and returns a list of pointers to the Partition
 * objects that satisfy the conditions defined in the criterion function.
 */
QList< Partition* > findPartitions( const QList< Device* >& devices,
                                    std::function< bool ( Partition* ) > criterionFunction );

/**
 * Helper function to create a new Partition object (does not create anything
 * on the disk) associated with a FileSystem.
 */
Partition* createNewPartition( PartitionNode* parent,
                               const Device& device,
                               const PartitionRole& role,
                               FileSystem::Type fsType,
                               qint64 firstSector,
                               qint64 lastSector,
                               PartitionTable::Flags flags = PartitionTable::FlagNone );

Partition* createNewEncryptedPartition( PartitionNode* parent,
                                        const Device& device,
                                        const PartitionRole& role,
                                        FileSystem::Type fsType,
                                        qint64 firstSector,
                                        qint64 lastSector,
                                        const QString& passphrase,
                                        PartitionTable::Flags flags = PartitionTable::FlagNone );

Partition* clonePartition( Device* device, Partition* partition );

QString prettyNameForFileSystemType( FileSystem::Type t );
}

#endif /* KPMHELPERS_H */
