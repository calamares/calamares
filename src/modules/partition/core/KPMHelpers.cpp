/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014,      Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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
#include "core/PartitionIterator.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/fs/luks.h>

#include <QDebug>


namespace KPMHelpers
{

static bool s_KPMcoreInited = false;

bool
initKPMcore()
{
    if ( s_KPMcoreInited )
        return true;

    QByteArray backendName = qgetenv( "KPMCORE_BACKEND" );
    if ( !CoreBackendManager::self()->load( backendName.isEmpty() ? CoreBackendManager::defaultBackendName() : backendName ) )
    {
        qWarning() << "Failed to load backend plugin" << backendName;
        return false;
    }
    s_KPMcoreInited = true;
    return true;
}


bool
isPartitionFreeSpace( Partition* partition )
{
    return partition->roles().has( PartitionRole::Unallocated );
}


bool
isPartitionNew( Partition* partition )
{
    return partition->state() == Partition::StateNew;
}


Partition*
findPartitionByMountPoint( const QList< Device* >& devices, const QString& mountPoint )
{
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( PartitionInfo::mountPoint( *it ) == mountPoint )
                return *it;
    return nullptr;
}


Partition*
findPartitionByPath( const QList< Device* >& devices, const QString& path )
{
    if ( path.simplified().isEmpty() )
        return nullptr;

    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( ( *it )->partitionPath() == path.simplified() )
                return *it;
    return nullptr;
}


QList< Partition* >
findPartitions( const QList< Device* >& devices,
                std::function< bool ( Partition* ) > criterionFunction )
{
    QList< Partition* > results;
    for ( auto device : devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( criterionFunction( *it ) )
                results.append( *it );
    return results;
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
    FileSystem* fs = FileSystemFactory::create( fsType, firstSector, lastSector
#ifdef WITH_KPMCORE22
                                                ,device.logicalSize()
#endif
    );
    return new Partition(
               parent,
               device,
               role,
               fs, fs->firstSector(), fs->lastSector(),
               QString() /* path */,
               PartitionTable::FlagNone /* availableFlags */,
               QString() /* mountPoint */,
               false /* mounted */,
               flags /* activeFlags */,
               Partition::StateNew
           );
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
        newRoles |= PartitionRole::Luks;

    FS::luks* fs = dynamic_cast< FS::luks* >(
                           FileSystemFactory::create( FileSystem::Luks,
                                                      firstSector,
                                                      lastSector
#ifdef WITH_KPMCORE22
                                                     ,device.logicalSize()
#endif
                                                      ) );
    if ( !fs )
    {
        qDebug() << "ERROR: cannot create LUKS filesystem. Giving up.";
        return nullptr;
    }

    fs->createInnerFileSystem( fsType );
    fs->setPassphrase( passphrase );
    Partition* p = new Partition( parent,
                                  device,
                                  PartitionRole( newRoles ),
                                  fs, fs->firstSector(), fs->lastSector(),
                                  QString() /* path */,
                                  PartitionTable::FlagNone /* availableFlags */,
                                  QString() /* mountPoint */,
                                  false /* mounted */,
                                  flags /* activeFlags */,
                                  Partition::StateNew );
    return p;
}


Partition*
clonePartition( Device* device, Partition* partition )
{
    FileSystem* fs = FileSystemFactory::create(
                         partition->fileSystem().type(),
                         partition->firstSector(),
                         partition->lastSector()
#ifdef WITH_KPMCORE22
                        ,device->logicalSize()
#endif
                     );
    return new Partition( partition->parent(),
                          *device,
                          partition->roles(),
                          fs,
                          fs->firstSector(),
                          fs->lastSector(),
                          partition->partitionPath(),
                          partition->activeFlags() );
}


QString
prettyNameForFileSystemType( FileSystem::Type t )
{
    switch ( t )
    {
    case FileSystem::Unknown:
        return QObject::tr( "unknown" );
    case FileSystem::Extended:
        return QObject::tr( "extended" );
    case FileSystem::Unformatted:
        return QObject::tr( "unformatted" );
    case FileSystem::LinuxSwap:
        return QObject::tr( "swap" );
    case FileSystem::Fat16:
    case FileSystem::Fat32:
    case FileSystem::Ntfs:
    case FileSystem::Xfs:
    case FileSystem::Jfs:
    case FileSystem::Hfs:
    case FileSystem::Ufs:
    case FileSystem::Hpfs:
    case FileSystem::Luks:
    case FileSystem::Ocfs2:
    case FileSystem::Zfs:
    case FileSystem::Nilfs2:
        return FileSystem::nameForType( t ).toUpper();
    case FileSystem::ReiserFS:
        return "ReiserFS";
    case FileSystem::Reiser4:
        return "Reiser4";
    case FileSystem::HfsPlus:
        return "HFS+";
    case FileSystem::Btrfs:
        return "Btrfs";
    case FileSystem::Exfat:
        return "exFAT";
    case FileSystem::Lvm2_PV:
        return "LVM PV";
    default:
        return FileSystem::nameForType( t );
    }
}

} // namespace
