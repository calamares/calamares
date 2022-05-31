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
    {
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        {
            if ( PartitionInfo::mountPoint( *it ) == mountPoint )
            {
                return *it;
            }
        }
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

// Adapted from src/fs/luks.cpp cryptOpen which always opens a dialog to ask for a passphrase
SavePassphraseValue
savePassphrase( Partition* partition, const QString& passphrase )
{

    if ( passphrase.isEmpty() )
    {
        return SavePassphraseValue::EmptyPassphrase;
    }

    if ( partition->fileSystem().type() != FileSystem::Luks )
    {
        return SavePassphraseValue::NotLuksPartition;
    }

    FS::luks* luksFs = dynamic_cast< FS::luks* >( &partition->fileSystem() );
    const QString deviceNode = partition->partitionPath();

    // Test the given passphrase
    if ( !luksFs->testPassphrase( deviceNode, passphrase ) )
    {
        return SavePassphraseValue::IncorrectPassphrase;
    }

    if ( luksFs->isCryptOpen() )
    {
        if ( !luksFs->mapperName().isEmpty() )
        {
            return SavePassphraseValue::NoError;
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
        return SavePassphraseValue::CryptsetupError;
    }

    // Save the existing passphrase
    luksFs->setPassphrase( passphrase );
    luksFs->scan( deviceNode );
    if ( luksFs->mapperName().isEmpty() )
    {
        return SavePassphraseValue::NoMapperNode;
    }

    luksFs->loadInnerFileSystem( luksFs->mapperName() );
    luksFs->setCryptOpen( luksFs->innerFS() != nullptr );
    if ( !luksFs->isCryptOpen() )
    {
        return SavePassphraseValue::DeviceNotDecrypted;
    }

    return SavePassphraseValue::NoError;
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
    std::for_each( l.begin(), l.end(), []( QString& s ) { Calamares::String::removeLeading( s, '=' ); } );

    return Calamares::JobResult::error( failureMessage, l.join( '\n' ) );
}


}  // namespace KPMHelpers
