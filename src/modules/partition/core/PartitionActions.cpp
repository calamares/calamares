/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

qint64
swapSuggestion( const qint64 availableSpaceB )
{

#define MiB * static_cast< qint64 >( 1024 ) * 1024
#define GiB * static_cast< qint64 >( 1024 ) * 1024 * 1024

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
        if ( availableRamB < 4 GiB )
            suggestedSwapSizeB = qMax( 2 GiB, availableRamB * 2 );
        else if ( availableRamB >= 4 GiB && availableRamB < 8 GiB )
            suggestedSwapSizeB = 8 GiB;
        else
            suggestedSwapSizeB = availableRamB;

        suggestedSwapSizeB *= overestimationFactor;
    }
    else //if we don't care about suspend to disk
    {
        if ( availableRamB < 2 GiB )
            suggestedSwapSizeB = qMax( 2 GiB, availableRamB * 2 );
        else if ( availableRamB >= 2 GiB && availableRamB < 8 GiB )
            suggestedSwapSizeB = availableRamB;
        else if ( availableRamB >= 8 GiB && availableRamB < 64 GiB )
            suggestedSwapSizeB = availableRamB / 2;
        else
            suggestedSwapSizeB = 4 GiB;

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
doAutopartition( PartitionCoreModule* core, Device* dev )
{
    bool isEfi = false;
    if ( QDir( "/sys/firmware/efi/efivars" ).exists() )
        isEfi = true;

#define MiB * static_cast< qint64 >( 1024 ) * 1024
#define GiB * static_cast< qint64 >( 1024 ) * 1024 * 1024

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

    qint64 firstFreeSector = empty_space_size MiB / dev->logicalSectorSize() + 1;

    if ( isEfi )
    {
        qint64 lastSector = firstFreeSector + ( uefisys_part_size MiB / dev->logicalSectorSize() );
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
        PartitionInfo::setMountPoint( efiPartition, Calamares::JobQueue::instance()
                                                        ->globalStorage()
                                                        ->value( "efiSystemPartition" )
                                                        .toString() );
        core->createPartition( dev, efiPartition );
        firstFreeSector = lastSector + 1;
    }
    else
    {
        core->createPartitionTable( dev, PartitionTable::msdos );
    }

    bool shouldCreateSwap = false;
    qint64 availableSpaceB = ( dev->totalSectors() - firstFreeSector ) * dev->logicalSectorSize();
    qint64 suggestedSwapSizeB = swapSuggestion( availableSpaceB );
    qint64 requiredSpaceB =
            ( Calamares::JobQueue::instance()->
              globalStorage()->
              value( "requiredStorageGB" ).toDouble() + 0.1 + 2.0 ) GiB +
            suggestedSwapSizeB;

    // If there is enough room for ESP + root + swap, create swap, otherwise don't.
    shouldCreateSwap = availableSpaceB > requiredSpaceB;

    qint64 lastSectorForRoot = dev->totalSectors() - 1; //last sector of the device
    if ( shouldCreateSwap )
    {
        lastSectorForRoot -= suggestedSwapSizeB / dev->logicalSectorSize() + 1;
    }

    Partition* rootPartition = KPMHelpers::createNewPartition(
        dev->partitionTable(),
        *dev,
        PartitionRole( PartitionRole::Primary ),
        FileSystem::Ext4,
        firstFreeSector,
        lastSectorForRoot
    );
    PartitionInfo::setFormat( rootPartition, true );
    PartitionInfo::setMountPoint( rootPartition, "/" );
    core->createPartition( dev, rootPartition );

    if ( shouldCreateSwap )
    {
        Partition* swapPartition = KPMHelpers::createNewPartition(
            dev->partitionTable(),
            *dev,
            PartitionRole( PartitionRole::Primary ),
            FileSystem::LinuxSwap,
            lastSectorForRoot + 1,
            dev->totalSectors() - 1
        );
        PartitionInfo::setFormat( swapPartition, true );
        core->createPartition( dev, swapPartition );
    }

    core->dumpQueue();
}


void
doReplacePartition( PartitionCoreModule* core, Device* dev, Partition* partition )
{
    cDebug() << "doReplacePartition for device" << partition->partitionPath();

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

    Partition* newPartition = KPMHelpers::createNewPartition(
                                  partition->parent(),
                                  *dev,
                                  newRoles,
                                  FileSystem::Ext4,
                                  partition->firstSector(),
                                  partition->lastSector() );
    PartitionInfo::setMountPoint( newPartition, "/" );
    PartitionInfo::setFormat( newPartition, true );

    if ( !partition->roles().has( PartitionRole::Unallocated ) )
        core->deletePartition( dev, partition );
    core->createPartition( dev, newPartition );

    core->dumpQueue();
}

}
