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
#include "utils/String.h"

#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/fs/luks.h>
#include <kpmcore/util/externalcommand.h>

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

#ifndef WITH_KPMCORE4API
// This function was added in KPMCore 4, implementation copied from src/fs/luks.cpp
/*
    SPDX-FileCopyrightText: 2010 Volker Lanz <vl@fidra.de>
    SPDX-FileCopyrightText: 2012-2019 Andrius Štikonas <andrius@stikonas.eu>
    SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
    SPDX-FileCopyrightText: 2016 Chantara Tith <tith.chantara@gmail.com>
    SPDX-FileCopyrightText: 2017 Christian Morlok <christianmorlok@gmail.com>
    SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
    SPDX-FileCopyrightText: 2020 Arnaud Ferraris <arnaud.ferraris@collabora.com>
    SPDX-FileCopyrightText: 2020 Gaël PORTAY <gael.portay@collabora.com>

    SPDX-License-Identifier: GPL-3.0-or-later
*/
static bool
testPassphrase( FS::luks* fs, const QString& deviceNode, const QString& passphrase )
{
    ExternalCommand cmd( QStringLiteral( "cryptsetup" ),
                         { QStringLiteral( "open" ),
                           QStringLiteral( "--tries" ),
                           QStringLiteral( "1" ),
                           QStringLiteral( "--test-passphrase" ),
                           deviceNode } );
    if ( cmd.write( passphrase.toLocal8Bit() + '\n' ) && cmd.start( -1 ) && cmd.exitCode() == 0 )
    {
        return true;
    }

    return false;
}
#else
static bool
testPassphrase( FS::luks* fs, const QString& deviceNode, const QString& passphrase )
{
    return fs->testPassphrase( deviceNode, passphrase );
}
#endif

// Adapted from luks cryptOpen which always opens a dialog to ask for a passphrase
int
updateLuksDevice( Partition* partition, const QString& passphrase )
{
    const QString deviceNode = partition->partitionPath();

    cDebug() << "Update Luks device: " << deviceNode;

    if ( passphrase.isEmpty() )
    {
        cWarning() << Logger::SubEntry << "#1: Passphrase is empty";
        return 1;
    }

    if ( partition->fileSystem().type() != FileSystem::Luks )
    {
        cWarning() << Logger::SubEntry << "#2: Not a luks encrypted device";
        return 2;
    }

    // Cast partition fs to luks fs
    FS::luks* luksFs = dynamic_cast< FS::luks* >( &partition->fileSystem() );

    // Test the given passphrase
    if ( !testPassphrase( luksFs, deviceNode, passphrase ) )
    {
        cWarning() << Logger::SubEntry << "#3: Passphrase incorrect";
        return 3;
    }

    if ( luksFs->isCryptOpen() )
    {
        if ( !luksFs->mapperName().isEmpty() )
        {
            cWarning() << Logger::SubEntry << "#4: Device already decrypted";
            return 4;
        }
        else
        {
            cDebug() << Logger::SubEntry << "No mapper node found";
            luksFs->setCryptOpen( false );
        }
    }

    ExternalCommand openCmd( QStringLiteral( "cryptsetup" ),
                             { QStringLiteral( "open" ), deviceNode, luksFs->suggestedMapperName( deviceNode ) } );

    if ( !( openCmd.write( passphrase.toLocal8Bit() + '\n' ) && openCmd.start( -1 ) && openCmd.exitCode() == 0 ) )
    {
        cWarning() << Logger::SubEntry << openCmd.exitCode() << ": cryptsetup command failed";
        return openCmd.exitCode();
    }

    // Save the existing passphrase
    luksFs->setPassphrase( passphrase );

    luksFs->scan( deviceNode );

    if ( luksFs->mapperName().isEmpty() )
    {
        cWarning() << Logger::SubEntry << "#5: No mapper node found";
        return 5;
    }

    luksFs->loadInnerFileSystem( luksFs->mapperName() );
    luksFs->setCryptOpen( luksFs->innerFS() != nullptr );

    if ( !luksFs->isCryptOpen() )
    {
        cWarning() << Logger::SubEntry << "#6: Device could not be decrypted";
        return 6;
    }

    return 0;
}

Calamares::JobResult
execute( Operation& operation, const QString& failureMessage )
{
    operation.setStatus( Operation::StatusRunning );

    Report report( nullptr );
    if ( operation.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    // Remove the === lines from the report by trimming them to empty
    QStringList l = report.toText().split( '\n' );
    std::for_each( l.begin(), l.end(), []( QString& s ) { CalamaresUtils::removeLeading( s, '=' ); } );

    return Calamares::JobResult::error( failureMessage, l.join( '\n' ) );
}


}  // namespace KPMHelpers
