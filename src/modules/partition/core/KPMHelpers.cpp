/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014      Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/KPMHelpers.h"

#include "core/PartitionInfo.h"

#include "partition/PartitionIterator.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/fs/luks.h>

using CalamaresUtils::Partition::PartitionIterator;

namespace KPMHelpers
{

Partition*
findPartitionByMountPoint( const QList< Device* >& devices, const QString& mountPoint )
{
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( PartitionInfo::mountPoint( *it ) == mountPoint )
            {
                return *it;
            }
    return nullptr;
}


Partition*
createNewPartition( PartitionNode* parent,
                    const Device& device,
                    const PartitionRole& role,
                    FileSystem::Type fsType,
                    const QString& fsLabel,
                    qint64 firstSector,
                    qint64 lastSector,
                    PartitionTable::Flags flags )
{
    FileSystem* fs = FileSystemFactory::create( fsType, firstSector, lastSector, device.logicalSize() );
    fs->setLabel( fsLabel );
    return new Partition( parent,
                          device,
                          role,
                          fs,
                          fs->firstSector(),
                          fs->lastSector(),
                          QString() /* path */,
                          KPM_PARTITION_FLAG( None ) /* availableFlags */,
                          QString() /* mountPoint */,
                          false /* mounted */,
                          flags /* activeFlags */,
                          KPM_PARTITION_STATE( New ) );
}


Partition*
createNewEncryptedPartition( PartitionNode* parent,
                             const Device& device,
                             const PartitionRole& role,
                             FileSystem::Type fsType,
                             const QString& fsLabel,
                             qint64 firstSector,
                             qint64 lastSector,
                             const QString& passphrase,
                             PartitionTable::Flags flags )
{
    PartitionRole::Roles newRoles = role.roles();
    if ( !role.has( PartitionRole::Luks ) )
    {
        newRoles |= PartitionRole::Luks;
    }

    FS::luks* fs = dynamic_cast< FS::luks* >(
        FileSystemFactory::create( FileSystem::Luks, firstSector, lastSector, device.logicalSize() ) );
    if ( !fs )
    {
        cError() << "cannot create LUKS filesystem. Giving up.";
        return nullptr;
    }

    fs->createInnerFileSystem( fsType );
    fs->setPassphrase( passphrase );
    fs->setLabel( fsLabel );
    Partition* p = new Partition( parent,
                                  device,
                                  PartitionRole( newRoles ),
                                  fs,
                                  fs->firstSector(),
                                  fs->lastSector(),
                                  QString() /* path */,
                                  KPM_PARTITION_FLAG( None ) /* availableFlags */,
                                  QString() /* mountPoint */,
                                  false /* mounted */,
                                  flags /* activeFlags */,
                                  KPM_PARTITION_STATE( New ) );
    return p;
}


Partition*
clonePartition( Device* device, Partition* partition )
{
    FileSystem* fs = FileSystemFactory::create(
        partition->fileSystem().type(), partition->firstSector(), partition->lastSector(), device->logicalSize() );
    return new Partition( partition->parent(),
                          *device,
                          partition->roles(),
                          fs,
                          fs->firstSector(),
                          fs->lastSector(),
                          partition->partitionPath(),
                          partition->activeFlags() );
}

}  // namespace KPMHelpers
