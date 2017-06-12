/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "utils/CalamaresUtilsSystem.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "GlobalStorage.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QDir>

namespace PartitionActions
{
constexpr qint64 operator ""_MiB( unsigned long long m )
{
    return m * static_cast< qint64 >( 1024 ) * 1024;
}

constexpr qint64 operator ""_GiB( unsigned long long m )
{
    return operator ""_MiB(m) * static_cast< qint64 >( 1024 );
}

constexpr qint64 toMiB( unsigned long long m )
{
    return operator ""_MiB( m );
}

constexpr qint64 toGiB( unsigned long long m )
{
    return operator ""_GiB( m );
}

qint64
swapSuggestion( const qint64 availableSpaceB )
{
    // swap(mem) = max(2, 2 * mem), if mem < 2 GiB
    //           = mem,             if 2 GiB <= mem < 8 GiB
    //           = mem / 2,         if 8 GIB <= mem < 64 GiB
    //           = 4 GiB,           if mem >= 64 GiB

    qint64 suggestedSwapSizeB = 0;
    qint64 availableRamB = CalamaresUtils::System::instance()->getPhysicalMemoryB();
    qreal overestimationFactor = 1.01;
    if ( !availableRamB )
    {
        availableRamB = CalamaresUtils::System::instance()->getTotalMemoryB();
        overestimationFactor = 1.10;
    }

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
        else if ( availableRamB >= 8_GiB && availableRamB < 64_GiB )
            suggestedSwapSizeB = availableRamB / 2;
        else
            suggestedSwapSizeB = 4_GiB;

        suggestedSwapSizeB *= overestimationFactor;

        // don't use more than 10% of available space
        qreal maxSwapDiskRatio = 1.10;
        qint64 maxSwapSizeB = availableSpaceB * maxSwapDiskRatio;
        if ( suggestedSwapSizeB > maxSwapSizeB )
            suggestedSwapSizeB = maxSwapSizeB;
    }

    cDebug() << "Suggested swap size:" << suggestedSwapSizeB / 1024. / 1024. /1024. << "GiB";

    return suggestedSwapSizeB;
}


void
doAutopartition( PartitionCoreModule* core, Device* dev, const QString& luksPassphrase )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    bool isEfi = false;
    if ( QDir( "/sys/firmware/efi/efivars" ).exists() )
        isEfi = true;

    QString defaultFsType = gs->value( "defaultFileSystemType" ).toString();
    if ( FileSystem::typeForName( defaultFsType ) == FileSystem::Unknown )
        defaultFsType = "ext4";

    // Partition sizes are expressed in MiB, should be multiples of
    // the logical sector size (usually 512B).
    int uefisys_part_size = 0;
    int empty_space_size = 0;
    if ( isEfi )
    {
        uefisys_part_size = 300;
        empty_space_size = 2;
    }
    else
    {
        // we start with a 1MiB offset before the first partition
        empty_space_size = 1;
    }

    qint64 firstFreeSector = toMiB(empty_space_size) / dev->logicalSize() + 1;

    if ( isEfi )
    {
        qint64 lastSector = firstFreeSector + ( toMiB(uefisys_part_size) / dev->logicalSize() );
        core->createPartitionTable( dev, PartitionTable::gpt );
        Partition* efiPartition = KPMHelpers::createNewPartition(
            dev->partitionTable(),
            *dev,
            PartitionRole( PartitionRole::Primary ),
            FileSystem::Fat32,
            firstFreeSector,
            lastSector,
            PartitionTable::FlagEsp
        );
        PartitionInfo::setFormat( efiPartition, true );
        PartitionInfo::setMountPoint( efiPartition, gs->value( "efiSystemPartition" )
                                                        .toString() );
        core->createPartition( dev, efiPartition, PartitionTable::FlagEsp | PartitionTable::FlagBoot );
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
        qint64 requiredSpaceB =
                toGiB( gs->value( "requiredStorageGB" ).toDouble() + 0.1 + 2.0 ) +
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
    core->createPartition( dev, rootPartition );

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
        cDebug() << "WARNING: selected partition is free space";
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
