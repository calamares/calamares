/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "PartitionActions.h"

#include "core/KPMHelpers.h"
#include "core/PartitionInfo.h"
#include "core/PartitionCoreModule.h"
#include "core/PartUtils.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Units.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "GlobalStorage.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QDir>

namespace PartitionActions
{
using CalamaresUtils::GiBtoBytes;
using CalamaresUtils::MiBtoBytes;
using CalamaresUtils::operator""_GiB;
using CalamaresUtils::operator""_MiB;

qint64
swapSuggestion( const qint64 availableSpaceB )
{
    /* If suspend-to-disk is demanded, then we always need enough
     * swap to write the whole memory to disk -- between 2GB and 8GB
     * RAM give proportionally more swap, and from 8GB RAM keep
     * swap = RAM.
     *
     * If suspend-to-disk is not demanded, then ramp up more slowly,
     * to 8GB swap at 16GB memory, and then drop to 4GB for "large
     * memory" machines, on the assumption that those don't need swap
     * because they have tons of memory (or whatever they are doing,
     * had better not run into swap).
     */
    qint64 suggestedSwapSizeB = 0;
    auto memory = CalamaresUtils::System::instance()->getTotalMemoryB();
    qint64 availableRamB = memory.first;
    qreal overestimationFactor = memory.second;

    bool ensureSuspendToDisk =
        Calamares::JobQueue::instance()->globalStorage()->
            value( "ensureSuspendToDisk" ).toBool();

    if ( ensureSuspendToDisk )
    {
        if ( availableRamB < 4_GiB )
            suggestedSwapSizeB = qMax( 2_GiB, availableRamB * 2 );
        else if ( availableRamB >= 4_GiB && availableRamB < 8_GiB )
            suggestedSwapSizeB = 8_GiB;
        else
            suggestedSwapSizeB = availableRamB;

        suggestedSwapSizeB *= overestimationFactor;
    }
    else //if we don't care about suspend to disk
    {
        if ( availableRamB < 2_GiB )
            suggestedSwapSizeB = qMax( 2_GiB, availableRamB * 2 );
        else if ( availableRamB >= 2_GiB && availableRamB < 8_GiB )
            suggestedSwapSizeB = availableRamB;
        else if ( availableRamB >= 8_GiB && availableRamB < 16_GiB )
            suggestedSwapSizeB = 8_GiB;
        else
            suggestedSwapSizeB = 4_GiB;

        suggestedSwapSizeB *= overestimationFactor;

        // don't use more than 10% of available space
        qreal maxSwapDiskRatio = 0.10;
        qint64 maxSwapSizeB = availableSpaceB * maxSwapDiskRatio;
        if ( suggestedSwapSizeB > maxSwapSizeB )
            suggestedSwapSizeB = maxSwapSizeB;
    }

    cDebug() << "Suggested swap size:" << suggestedSwapSizeB / 1024. / 1024. / 1024. << "GiB";

    return suggestedSwapSizeB;
}

constexpr qint64
alignBytesToBlockSize( qint64 bytes, qint64 blocksize )
{
    qint64 blocks = bytes / blocksize;

    if ( blocks * blocksize != bytes )
        ++blocks;
    return blocks * blocksize;
}

constexpr qint64
bytesToSectors( qint64 bytes, qint64 blocksize )
{
    return alignBytesToBlockSize( alignBytesToBlockSize( bytes, blocksize), MiBtoBytes(1) ) / blocksize;
}

void
doAutopartition( PartitionCoreModule* core, Device* dev, const QString& luksPassphrase )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    bool isEfi = PartUtils::isEfiSystem();

    QString defaultFsType = gs->value( "defaultFileSystemType" ).toString();
    if ( FileSystem::typeForName( defaultFsType ) == FileSystem::Unknown )
        defaultFsType = "ext4";

    // Partition sizes are expressed in MiB, should be multiples of
    // the logical sector size (usually 512B). EFI starts with 2MiB
    // empty and a 300MiB EFI boot partition, while BIOS starts at
    // the 1MiB boundary (usually sector 2048).
    int uefisys_part_sizeB = isEfi ? 300_MiB : 0_MiB;
    int empty_space_sizeB = isEfi ? 2_MiB : 1_MiB;

    // Since sectors count from 0, if the space is 2048 sectors in size,
    // the first free sector has number 2048 (and there are 2048 sectors
    // before that one, numbered 0..2047).
    qint64 firstFreeSector = bytesToSectors( empty_space_sizeB, dev->logicalSize() );

    if ( isEfi )
    {
        qint64 efiSectorCount = bytesToSectors( uefisys_part_sizeB, dev->logicalSize() );
        Q_ASSERT( efiSectorCount > 0 );

        // Since sectors count from 0, and this partition is created starting
        // at firstFreeSector, we need efiSectorCount sectors, numbered
        // firstFreeSector..firstFreeSector+efiSectorCount-1.
        qint64 lastSector = firstFreeSector + efiSectorCount - 1;
        core->createPartitionTable( dev, PartitionTable::gpt );
        Partition* efiPartition = KPMHelpers::createNewPartition(
            dev->partitionTable(),
            *dev,
            PartitionRole( PartitionRole::Primary ),
            FileSystem::Fat32,
            firstFreeSector,
            lastSector
        );
        PartitionInfo::setFormat( efiPartition, true );
        PartitionInfo::setMountPoint( efiPartition, gs->value( "efiSystemPartition" )
                                                        .toString() );
        core->createPartition( dev, efiPartition, PartitionTable::FlagEsp );
        firstFreeSector = lastSector + 1;
    }
    else
    {
        core->createPartitionTable( dev, PartitionTable::msdos );
    }

    const bool mayCreateSwap = !gs->value( "neverCreateSwap" ).toBool();
    bool shouldCreateSwap = false;
    qint64 suggestedSwapSizeB = 0;

    if ( mayCreateSwap )
    {
        qint64 availableSpaceB = ( dev->totalLogical() - firstFreeSector ) * dev->logicalSize();
        suggestedSwapSizeB = swapSuggestion( availableSpaceB );
        // Space required by this installation is what the distro claims is needed
        // (via global configuration) plus the swap size plus a fudge factor of
        // 0.6GiB (this was 2.1GiB up to Calamares 3.2.2).
        qint64 requiredSpaceB =
                GiBtoBytes( gs->value( "requiredStorageGB" ).toDouble() + 0.6 ) +
                suggestedSwapSizeB;

        // If there is enough room for ESP + root + swap, create swap, otherwise don't.
        shouldCreateSwap = availableSpaceB > requiredSpaceB;
    }

    qint64 lastSectorForRoot = dev->totalLogical() - 1; //last sector of the device
    if ( shouldCreateSwap )
    {
        lastSectorForRoot -= suggestedSwapSizeB / dev->logicalSize() + 1;
    }

    Partition* rootPartition = nullptr;
    if ( luksPassphrase.isEmpty() )
    {
        rootPartition = KPMHelpers::createNewPartition(
            dev->partitionTable(),
            *dev,
            PartitionRole( PartitionRole::Primary ),
            FileSystem::typeForName( defaultFsType ),
            firstFreeSector,
            lastSectorForRoot
        );
    }
    else
    {
        rootPartition = KPMHelpers::createNewEncryptedPartition(
            dev->partitionTable(),
            *dev,
            PartitionRole( PartitionRole::Primary ),
            FileSystem::typeForName( defaultFsType ),
            firstFreeSector,
            lastSectorForRoot,
            luksPassphrase
       );
    }
    PartitionInfo::setFormat( rootPartition, true );
    PartitionInfo::setMountPoint( rootPartition, "/" );
    if( isEfi )
    {
        core->createPartition( dev, rootPartition );
    }
    else
    {
        // Some buggy BIOSes test if the bootflag of at least one partition is set. Otherwise they ignore the device in boot-order. 
        core->createPartition( dev, rootPartition, PartitionTable::FlagBoot )
    }

    if ( shouldCreateSwap )
    {
        Partition* swapPartition = nullptr;
        if ( luksPassphrase.isEmpty() )
        {
            swapPartition = KPMHelpers::createNewPartition(
                dev->partitionTable(),
                *dev,
                PartitionRole( PartitionRole::Primary ),
                FileSystem::LinuxSwap,
                lastSectorForRoot + 1,
                dev->totalLogical() - 1
            );
        }
        else
        {
            swapPartition = KPMHelpers::createNewEncryptedPartition(
                dev->partitionTable(),
                *dev,
                PartitionRole( PartitionRole::Primary ),
                FileSystem::LinuxSwap,
                lastSectorForRoot + 1,
                dev->totalLogical() - 1,
                luksPassphrase
            );
        }
        PartitionInfo::setFormat( swapPartition, true );
        core->createPartition( dev, swapPartition );
    }

    core->dumpQueue();
}


void
doReplacePartition( PartitionCoreModule* core,
                    Device* dev,
                    Partition* partition,
                    const QString& luksPassphrase )
{
    cDebug() << "doReplacePartition for device" << partition->partitionPath();

    QString defaultFsType = Calamares::JobQueue::instance()->
                                globalStorage()->
                                value( "defaultFileSystemType" ).toString();
    if ( FileSystem::typeForName( defaultFsType ) == FileSystem::Unknown )
        defaultFsType = "ext4";

    PartitionRole newRoles( partition->roles() );
    if ( partition->roles().has( PartitionRole::Extended ) )
        newRoles = PartitionRole( PartitionRole::Primary );

    if ( partition->roles().has( PartitionRole::Unallocated ) )
    {
        newRoles = PartitionRole( PartitionRole::Primary );
        cWarning() << "selected partition is free space";
        if ( partition->parent() )
        {
            Partition* parent = dynamic_cast< Partition* >( partition->parent() );
            if ( parent && parent->roles().has( PartitionRole::Extended ) )
                newRoles = PartitionRole( PartitionRole::Logical );
        }
    }

    Partition* newPartition = nullptr;
    if ( luksPassphrase.isEmpty() )
    {
        newPartition = KPMHelpers::createNewPartition(
            partition->parent(),
            *dev,
            newRoles,
            FileSystem::typeForName( defaultFsType ),
            partition->firstSector(),
            partition->lastSector()
        );
    }
    else
    {
        newPartition = KPMHelpers::createNewEncryptedPartition(
            partition->parent(),
            *dev,
            newRoles,
            FileSystem::typeForName( defaultFsType ),
            partition->firstSector(),
            partition->lastSector(),
            luksPassphrase
        );
    }
    PartitionInfo::setMountPoint( newPartition, "/" );
    PartitionInfo::setFormat( newPartition, true );

    if ( !partition->roles().has( PartitionRole::Unallocated ) )
        core->deletePartition( dev, partition );
    core->createPartition( dev, newPartition );

    core->dumpQueue();
}

}
