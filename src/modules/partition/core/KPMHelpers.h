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

#include "Job.h"

#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/operation.h>
#include <kpmcore/util/report.h>

#include <QList>

#include <functional>

class Device;
class Partition;
class PartitionNode;
class PartitionRole;

// TODO:3.3: Remove defines, expand in-place
#define KPM_PARTITION_FLAG( x ) PartitionTable::Flag::x
#define KPM_PARTITION_STATE( x ) Partition::State::x
#define KPM_PARTITION_FLAG_ESP PartitionTable::Flag::Boot

/**
 * Helper functions to manipulate partitions
 */
namespace KPMHelpers
{

/** @brief Return (errors) for savePassphrase()
 *
 * There's a handful of things that can go wrong when
 * saving a passphrase for a given partition; this
 * expresses clearly which ones are wrong.
 *
 * @c NoError is "Ok" when saving the passphrase succeeds.
 */
enum class SavePassphraseValue
{
    NoError,
    EmptyPassphrase,
    NotLuksPartition,
    IncorrectPassphrase,
    CryptsetupError,
    NoMapperNode,
    DeviceNotDecrypted
};

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

/** @brief Save an existing passphrase for a previously encrypted partition.
 *
 * Tries to apply the passphrase to the partition; this checks if the
 * @p partition is one that can have a passphrase applied, and
 * runs `cryptsetup` to check that the passphrase actually works
 * for the partition. Returns `NoError` on success, or an explanatory
 * other value if it fails.
 */
SavePassphraseValue savePassphrase( Partition* partition, const QString& passphrase );

/** @brief Decrypt an encrypted partition.
 *
 * Uses @p partition to decrypt the partition.
 * The passphrase saved in @p partition is used.
 * Returns the mapped device path or an empty string if it fails.
 */
QString cryptOpen( Partition* partition );
void cryptClose( Partition* partition );

/** @brief Set label of luks encrypted partition.
 *
 * Returns true on success or false if it fails.
 */
bool cryptLabel( Partition* partition, const QString& label );

/** @brief Returns the luks version used to encrypt the partition.
 *
 * Used by cryptLabel
 */
int cryptVersion( Partition* partition );

/** @brief Return a result for an @p operation
 *
 * Executes the operation, and if successful, returns a success result.
 * Otherwise returns an error using @p failureMessage as the primary part
 * of the error, and details obtained from the operation.
 */
Calamares::JobResult execute( Operation& operation, const QString& failureMessage );
/** @brief Return a result for an @p operation
 *
 * It's acceptable to use an rvalue: the operation-running is the effect
 * you're interested in, rather than keeping the temporary around.
 */
static inline Calamares::JobResult
execute( Operation&& operation, const QString& failureMessage )
{
    return execute( operation, failureMessage );
}

}  // namespace KPMHelpers

#endif /* KPMHELPERS_H */
