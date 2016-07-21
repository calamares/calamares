/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014      Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

#if defined( WITH_KPMCORE4API )
#define KPM_PARTITION_FLAG( x ) PartitionTable::Flag::x
#define KPM_PARTITION_STATE( x ) Partition::State::x
#define KPM_PARTITION_FLAG_ESP PartitionTable::Flag::Boot
#else
#define KPM_PARTITION_FLAG( x ) PartitionTable::Flag##x
#define KPM_PARTITION_STATE( x ) Partition::State##x
#define KPM_PARTITION_FLAG_ESP PartitionTable::FlagEsp
#endif

/**
 * Helper functions to manipulate partitions
 */
namespace KPMHelpers
{

/**
 * Iterates on all devices and return the first partition which is associated
 * with mountPoint. This uses PartitionInfo::mountPoint(), not Partition::mountPoint()
 */
Partition* findPartitionByMountPoint( const QList< Device* >& devices, const QString& mountPoint );

/**
 * Helper function to create a new Partition object (does not create anything
 * on the disk) associated with a FileSystem.
 */
Partition* createNewPartition( PartitionNode* parent,
                               const Device& device,
                               const PartitionRole& role,
                               FileSystem::Type fsType,
                               const QString& fsLabel,
                               qint64 firstSector,
                               qint64 lastSector,
                               PartitionTable::Flags flags );

Partition* createNewEncryptedPartition( PartitionNode* parent,
                                        const Device& device,
                                        const PartitionRole& role,
                                        FileSystem::Type fsType,
                                        const QString& fsLabel,
                                        qint64 firstSector,
                                        qint64 lastSector,
                                        const QString& passphrase,
                                        PartitionTable::Flags flags );

Partition* clonePartition( Device* device, Partition* partition );

}  // namespace KPMHelpers

#endif /* KPMHELPERS_H */
