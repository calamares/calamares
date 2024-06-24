/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONACTIONS_H
#define PARTITIONACTIONS_H

#include "Config.h"

#include <QSet>
#include <QString>

class PartitionCoreModule;
class Device;
class Partition;

namespace PartitionActions
{
/** @brief Namespace for enums
 *
 * This namespace houses non-class enums.....
 */
namespace Choices
{
struct ReplacePartitionOptions
{
    QString defaultPartitionTableType;  // e.g. "gpt" or "msdos"
    QString defaultFsType;  // e.g. "ext4" or "btrfs"
    Config::LuksGeneration luksFsType = Config::LuksGeneration::Luks1;  // optional ("luks", "luks2")
    QString luksPassphrase;  // optional

    ReplacePartitionOptions( const QString& pt,
                             const QString& fs,
                             Config::LuksGeneration luksFs,
                             const QString& passphrase )
        : defaultPartitionTableType( pt )
        , defaultFsType( fs )
        , luksFsType( luksFs )
        , luksPassphrase( passphrase )
    {
    }
};

struct AutoPartitionOptions : ReplacePartitionOptions
{
    QString efiPartitionMountPoint;  // optional, e.g. "/boot"
    quint64 requiredSpaceB;  // estimated required space for root partition
    Config::SwapChoice swap;

    AutoPartitionOptions( const QString& pt,
                          const QString& fs,
                          Config::LuksGeneration luksFs,
                          const QString& passphrase,
                          const QString& efi,
                          qint64 requiredBytes,
                          Config::SwapChoice s )
        : ReplacePartitionOptions( pt, fs, luksFs, passphrase )
        , efiPartitionMountPoint( efi )
        , requiredSpaceB( requiredBytes > 0 ? quint64( requiredBytes ) : 0U )
        , swap( s )
    {
    }
};

}  // namespace Choices

/**
 * @brief doAutopartition sets up an autopartitioning operation on the given Device.
 * @param core a pointer to the PartitionCoreModule instance.
 * @param dev the device to wipe.
 * @param options settings for autopartitioning.
 */
void doAutopartition( PartitionCoreModule* core, Device* dev, Choices::AutoPartitionOptions options );

/**
 * @brief doReplacePartition sets up replace-partitioning with the given partition.
 * @param core a pointer to the PartitionCoreModule instance.
 * @param dev a pointer to the Device on which to replace a partition.
 * @param partition a pointer to the Partition to be replaced.
 * @param options settings for partitioning (not all fields apply)
 *
 * @note this function also takes care of requesting PCM to delete the partition.
 */
void doReplacePartition( PartitionCoreModule* core,
                         Device* dev,
                         Partition* partition,
                         Choices::ReplacePartitionOptions options );
}  // namespace PartitionActions

#endif  // PARTITIONACTIONS_H
