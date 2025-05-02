/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PartitionActions.h"

#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionInfo.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/System.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QDir>

using namespace Calamares::Units;

static quint64
swapSuggestion( const quint64 availableSpaceB, Config::SwapChoice swap )
{
    if ( ( swap != Config::SwapChoice::SmallSwap ) && ( swap != Config::SwapChoice::FullSwap ) )
    {
        return 0;
    }

    // See partition.conf for explanation
    quint64 suggestedSwapSizeB = 0;
    auto [ availableRamB, overestimationFactor ] = Calamares::System::instance()->getTotalMemoryB();

    bool ensureSuspendToDisk = swap == Config::SwapChoice::FullSwap;

    // Ramp up quickly to 8GiB, then follow memory size
    if ( availableRamB <= 4_GiB )
    {
        suggestedSwapSizeB = availableRamB * 2;
    }
    else if ( availableRamB <= 8_GiB )
    {
        suggestedSwapSizeB = 8_GiB;
    }
    else
    {
        suggestedSwapSizeB = availableRamB;
    }

    // .. top out at 8GiB if we don't care about suspend
    if ( !ensureSuspendToDisk )
    {
        // TODO: make the _GiB operator return unsigned
        suggestedSwapSizeB = qMin( quint64( 8_GiB ), suggestedSwapSizeB );
    }

    // Allow for a fudge factor
    suggestedSwapSizeB = quint64( qRound64( qreal( suggestedSwapSizeB ) * overestimationFactor ) );

    // don't use more than 10% of available space
    if ( !ensureSuspendToDisk )
    {
        suggestedSwapSizeB = qMin( suggestedSwapSizeB, availableSpaceB / 10 /* 10% is 0.1 */ );
    }

    // TODO: make Units functions work on unsigned
    cDebug() << "Suggested swap size:" << Calamares::BytesToGiB( suggestedSwapSizeB ) << "GiB";

    return suggestedSwapSizeB;
}

namespace PartitionActions
{

void
doAutopartition( PartitionCoreModule* core, Device* dev, Choices::AutoPartitionOptions o )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    const bool isEfi = PartUtils::isEfiSystem();
    
    bool createHybridBootloaderLayout = false;
    if ( gs->contains( "createHybridBootloaderLayout" ) ) {
        createHybridBootloaderLayout = gs->value( "createHybridBootloaderLayout" ).toBool();
    }

    // Partition sizes are expressed in MiB, should be multiples of
    // the logical sector size (usually 512B). EFI starts with 2MiB
    // empty and a EFI boot partition, while BIOS starts at
    // the 1MiB boundary (usually sector 2048).
    // ARM empty sectors are 16 MiB in size.
    const int empty_space_sizeB = PartUtils::isArmSystem() ? 16_MiB : ( isEfi ? 2_MiB : 1_MiB );

    // Since sectors count from 0, if the space is 2048 sectors in size,
    // the first free sector has number 2048 (and there are 2048 sectors
    // before that one, numbered 0..2047).
    qint64 firstFreeSector = Calamares::bytesToSectors( empty_space_sizeB, dev->logicalSize() );

    PartitionTable::TableType partType = PartitionTable::nameToTableType( o.defaultPartitionTableType );
    if ( partType == PartitionTable::unknownTableType )
    {
        partType = ( isEfi || createHybridBootloaderLayout ) ? PartitionTable::gpt : PartitionTable::msdos;
    }
    // last usable sector possibly allowing for secondary GPT using 66 sectors (256 entries)
    const qint64 lastUsableSector = dev->totalLogical() - ( partType == PartitionTable::gpt ? 67 : 1 );

    // Looking up the defaultFsType (which should name a filesystem type)
    // will log an error and set the type to Unknown if there's something wrong.
    FileSystem::Type type = FileSystem::Unknown;
    PartUtils::canonicalFilesystemName( o.defaultFsType, &type );
    core->partitionLayout().setDefaultFsType( type == FileSystem::Unknown ? FileSystem::Ext4 : type );

    core->createPartitionTable( dev, partType );

    if ( createHybridBootloaderLayout || isEfi )
    {
        qint64 uefisys_part_sizeB = PartUtils::efiFilesystemRecommendedSize();
        qint64 efiSectorCount = Calamares::bytesToSectors( uefisys_part_sizeB, dev->logicalSize() );
        Q_ASSERT( efiSectorCount > 0 );

        // Since sectors count from 0, and this partition is created starting
        // at firstFreeSector, we need efiSectorCount sectors, numbered
        // firstFreeSector..firstFreeSector+efiSectorCount-1.
        qint64 lastSector = firstFreeSector + efiSectorCount - 1;
        Partition* efiPartition = KPMHelpers::createNewPartition( dev->partitionTable(),
                                                                  *dev,
                                                                  PartitionRole( PartitionRole::Primary ),
                                                                  FileSystem::Fat32,
                                                                  QString(),
                                                                  firstFreeSector,
                                                                  lastSector,
                                                                  KPM_PARTITION_FLAG( None ) );
        PartitionInfo::setFormat( efiPartition, true );
        PartitionInfo::setMountPoint( efiPartition, o.efiPartitionMountPoint );
        if ( gs->contains( "efiSystemPartitionName" ) )
        {
            efiPartition->setLabel( gs->value( "efiSystemPartitionName" ).toString() );
        }
        core->createPartition( dev, efiPartition, KPM_PARTITION_FLAG_ESP );
        firstFreeSector = lastSector + 1;

        if ( createHybridBootloaderLayout )
        {
            qint64 bios_part_sizeB = 8_MiB;
            qint64 biosSectorCount = Calamares::bytesToSectors( bios_part_sizeB, dev->logicalSize() );
            Q_ASSERT( biosSectorCount > 0 );

            qint64 lastSector = firstFreeSector + biosSectorCount - 1;
            Partition* biosPartition = KPMHelpers::createNewPartition( dev->partitionTable(),
                                                                       *dev,
                                                                       PartitionRole( PartitionRole::Primary ),
                                                                       FileSystem::Unformatted,
                                                                       QString(),
                                                                       firstFreeSector,
                                                                       lastSector,
                                                                       KPM_PARTITION_FLAG( None ) );
            core->createPartition( dev, biosPartition, KPM_PARTITION_FLAG( BiosGrub ) );
            firstFreeSector = lastSector + 1;
        }
    }

    const bool mayCreateSwap
        = ( o.swap == Config::SwapChoice::SmallSwap ) || ( o.swap == Config::SwapChoice::FullSwap );
    bool shouldCreateSwap = false;
    quint64 suggestedSwapSizeB = 0;

    const quint64 sectorSize = quint64( dev->logicalSize() );
    if ( mayCreateSwap )
    {
        quint64 availableSpaceB = quint64( lastUsableSector - firstFreeSector + 1 ) * sectorSize;
        suggestedSwapSizeB = swapSuggestion( availableSpaceB, o.swap );
        // Space required by this installation is what the distro claims is needed
        // (via global configuration) plus the swap size plus a fudge factor of
        // 0.6GiB (this was 2.1GiB up to Calamares 3.2.2).
        quint64 requiredSpaceB = o.requiredSpaceB + 600_MiB + suggestedSwapSizeB;

        // If there is enough room for ESP + root + swap, create swap, otherwise don't.
        shouldCreateSwap = availableSpaceB > requiredSpaceB;
    }

    qint64 lastSectorForRoot = lastUsableSector;
    if ( shouldCreateSwap )
    {
        lastSectorForRoot -= suggestedSwapSizeB / sectorSize + 1;
    }

    core->layoutApply( dev, firstFreeSector, lastSectorForRoot, o.luksFsType, o.luksPassphrase );

    if ( shouldCreateSwap )
    {
        Partition* swapPartition = nullptr;
        if ( o.luksPassphrase.isEmpty() )
        {
            swapPartition = KPMHelpers::createNewPartition( dev->partitionTable(),
                                                            *dev,
                                                            PartitionRole( PartitionRole::Primary ),
                                                            FileSystem::LinuxSwap,
                                                            QStringLiteral( "swap" ),
                                                            lastSectorForRoot + 1,
                                                            lastUsableSector,
                                                            KPM_PARTITION_FLAG( None ) );
        }
        else
        {
            swapPartition = KPMHelpers::createNewEncryptedPartition( dev->partitionTable(),
                                                                     *dev,
                                                                     PartitionRole( PartitionRole::Primary ),
                                                                     FileSystem::LinuxSwap,
                                                                     QStringLiteral( "swap" ),
                                                                     lastSectorForRoot + 1,
                                                                     lastUsableSector,
                                                                     o.luksFsType,
                                                                     o.luksPassphrase,
                                                                     KPM_PARTITION_FLAG( None ) );
        }
        PartitionInfo::setFormat( swapPartition, true );
        if ( gs->contains( "swapPartitionName" ) )
        {
            swapPartition->setLabel( gs->value( "swapPartitionName" ).toString() );
        }
        core->createPartition( dev, swapPartition );
    }

    core->dumpQueue();
}

void
doReplacePartition( PartitionCoreModule* core, Device* dev, Partition* partition, Choices::ReplacePartitionOptions o )
{
    qint64 firstSector, lastSector;

    cDebug() << "doReplacePartition for device" << partition->partitionPath();

    // Looking up the defaultFsType (which should name a filesystem type)
    // will log an error and set the type to Unknown if there's something wrong.
    FileSystem::Type type = FileSystem::Unknown;
    PartUtils::canonicalFilesystemName( o.defaultFsType, &type );
    core->partitionLayout().setDefaultFsType( type == FileSystem::Unknown ? FileSystem::Ext4 : type );

    PartitionRole newRoles( partition->roles() );
    if ( partition->roles().has( PartitionRole::Extended ) )
    {
        newRoles = PartitionRole( PartitionRole::Primary );
    }

    if ( partition->roles().has( PartitionRole::Unallocated ) )
    {
        newRoles = PartitionRole( PartitionRole::Primary );
        cWarning() << "selected partition is free space";
        if ( partition->parent() )
        {
            Partition* parent = dynamic_cast< Partition* >( partition->parent() );
            if ( parent && parent->roles().has( PartitionRole::Extended ) )
            {
                newRoles = PartitionRole( PartitionRole::Logical );
            }
        }
    }

    // Save the first and last sector values as the partition will be deleted
    firstSector = partition->firstSector();
    lastSector = partition->lastSector();
    if ( !partition->roles().has( PartitionRole::Unallocated ) )
    {
        core->deletePartition( dev, partition );
    }

    core->layoutApply( dev, firstSector, lastSector, o.luksFsType, o.luksPassphrase );

    core->dumpQueue();
}

}  // namespace PartitionActions
