/* === This file is part of Calamares - <https://github.com/calamares> ===
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
/** @brief Namespace for enums
 *
 * This namespace houses non-class enums.....
 */
namespace Choices
{
    /** @brief Ccchoice of swap (size and type) */
    enum SwapChoice
    {
        NoSwap,     // don't create any swap, don't use any
        ReuseSwap,  // don't create, but do use existing
        SmallSwap,  // up to 8GiB of swap
        FullSwap,   // ensureSuspendToDisk -- at least RAM size
        SwapFile    // use a file (if supported)
    };

    struct ReplacePartitionOptions
    {
        QString defaultFsType;  // e.g. "ext4" or "btrfs"
        QString luksPassphrase;  // optional

        ReplacePartitionOptions( const QString& fs, const QString& luks )
            : defaultFsType( fs )
            , luksPassphrase( luks )
        {
        }
    };

    struct AutoPartitionOptions : ReplacePartitionOptions
    {
        QString efiPartitionMountPoint;  // optional, e.g. "/boot"
        quint64 requiredSpaceB;  // estimated required space for root partition
        SwapChoice swap;

        AutoPartitionOptions( const QString& fs, const QString& luks, const QString& efi, qint64 r, SwapChoice s )
            : ReplacePartitionOptions( fs, luks )
            , efiPartitionMountPoint( efi )
            , requiredSpaceB( r > 0 ? r : 0 )
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
void doAutopartition( PartitionCoreModule* core,
                      Device* dev,
                      Choices::AutoPartitionOptions options );

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

#endif // PARTITIONACTIONS_H
