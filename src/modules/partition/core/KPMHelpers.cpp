/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014,      Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
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
                    qint64 firstSector,
                    qint64 lastSector,
                    PartitionTable::Flags flags )
{
    FileSystem* fs = FileSystemFactory::create( fsType, firstSector, lastSector, device.logicalSize() );
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
