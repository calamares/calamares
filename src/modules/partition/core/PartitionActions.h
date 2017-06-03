/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#ifndef PARTITIONACTIONS_H
#define PARTITIONACTIONS_H

#include <QString>

class PartitionCoreModule;
class Device;
class Partition;

namespace PartitionActions
{

/**
 * @brief doAutopartition sets up an autopartitioning operation on the given Device.
 * @param core a pointer to the PartitionCoreModule instance.
 * @param dev the device to wipe.
 * @param luksPassphrase the passphrase for LUKS encryption (optional, default is empty).
 */
void doAutopartition( PartitionCoreModule* core,
                      Device* dev,
                      const QString& luksPassphrase = QString() );

/**
 * @brief doReplacePartition sets up replace-partitioning with the given partition.
 * @param core a pointer to the PartitionCoreModule instance.
 * @param dev a pointer to the Device on which to replace a partition.
 * @param partition a pointer to the Partition to be replaced.
 * @param luksPassphrase the passphrase for LUKS encryption (optional, default is empty).
 * @note this function also takes care of requesting PCM to delete the partition.
 */
void doReplacePartition( PartitionCoreModule* core,
                         Device* dev,
                         Partition* partition,
                         const QString& luksPassphrase = QString() );
}

#endif // PARTITIONACTIONS_H
