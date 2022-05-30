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

#include <qregularexpression.h>

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

SavePassphraseValue
savePassphrase( Partition* partition, const QString& passphrase )
{

    if ( passphrase.isEmpty() )
    {
        return SavePassphraseValue::EmptyPassphrase;
    }

    FS::luks* luksFs = dynamic_cast< FS::luks* >( &partition->fileSystem() );
    if ( luksFs == nullptr )
    {
        // No luks device
        return SavePassphraseValue::NotLuksPartition;
    }

    // Test the given passphrase
    if ( testPassphrase( luksFs, partition->partitionPath(), passphrase ) )
    {
        // Save the existing passphrase
        luksFs->setPassphrase( passphrase );
    }
    else
    {
        return SavePassphraseValue::IncorrectPassphrase;
    }
    return SavePassphraseValue::NoError;
}

QString
openLuksDevice( Partition* partition )
{
    FS::luks* luksFs = dynamic_cast< FS::luks* >( &partition->fileSystem() );
    if ( luksFs == nullptr )
    {
        // No luks device
        return QString();
    }

    if ( luksFs->isCryptOpen() )
    {
        if ( !luksFs->mapperName().isEmpty() )
        {
            // Already decrypted
            return luksFs->mapperName();
        }
        else
        {
            cDebug() << Logger::SubEntry << "No mapper node found - reset cryptOpen";
            luksFs->setCryptOpen( false );
        }
    }

    if ( luksFs->passphrase().isEmpty() )
    {
        // No passphrase for decryption
        return QString();
    }

    // Decrypt the partition
    const QString deviceNode = partition->partitionPath();
    ExternalCommand openCmd( QStringLiteral( "cryptsetup" ),
                             { QStringLiteral( "open" ), deviceNode, luksFs->suggestedMapperName( deviceNode ) } );
    if ( ( openCmd.write( luksFs->passphrase().toLocal8Bit() + '\n' ) && openCmd.start( -1 ) && openCmd.exitCode() == 0 ) )
    {
        luksFs->scan( deviceNode );
        if ( luksFs->mapperName().isEmpty() )
        {
            return QString();
        }
        luksFs->loadInnerFileSystem( luksFs->mapperName() );
        luksFs->setCryptOpen( luksFs->innerFS() != nullptr );
        if ( !luksFs->isCryptOpen() )
        {
            return QString();
        }
        return luksFs->mapperName();
    }
    return QString();
}

void
closeLuksDevice( Partition* partition )
{
    FS::luks* luksFs = dynamic_cast< FS::luks* >( &partition->fileSystem() );
    if ( luksFs == nullptr )
    {
        // No luks device
        return;
    }

    if ( luksFs->mapperName().isEmpty() )
    {
        // Not opened
        return;
    }

    // Close the partition
    ExternalCommand openCmd( QStringLiteral( "cryptsetup" ),
                             { QStringLiteral( "close" ), partition->partitionPath() } );
    openCmd.start( -1 );
}

bool
setLuksLabel( Partition* partition, const QString& label )
{
    int version = luksVersion( partition );
    if ( version == 0 || label.isEmpty() )
    {
        return false;
    }

    if ( version == 1 )
    {
        QString mappedDevice = openLuksDevice( partition );
        if ( !mappedDevice.isEmpty() )
        {
            // Label mapped device
            ExternalCommand openCmd( QStringLiteral( "e2label" ),
                                     { mappedDevice,
                                     label } );
            openCmd.start( -1 );
            closeLuksDevice( partition );
            return true;
        }
    }
    else
    {
        ExternalCommand openCmd( QStringLiteral( "cryptsetup" ),
                                 { QStringLiteral( "config" ),
                                 partition->partitionPath(),
                                 QStringLiteral( "--label" ),
                                 label } );
        if ( openCmd.start( -1 ) && openCmd.exitCode() == 0 )
        {
            return true;
        }
    }
    return false;
}

int
luksVersion( Partition* partition )
{
    if ( partition->fileSystem().type() != FileSystem::Luks )
    {
        return 0;
    }

    // Get luks version from header information
    int luksVersion = 1;
    ExternalCommand openCmd( QStringLiteral( "cryptsetup" ),
                             { QStringLiteral( "luksDump" ),
                             partition->partitionPath() } );
    if ( openCmd.start( -1 ) && openCmd.exitCode() == 0 )
    {
        QRegularExpression re( QStringLiteral( R"(version:\s+(\d))" ),
                               QRegularExpression::CaseInsensitiveOption );
        QRegularExpressionMatch rem = re.match( openCmd.output() );
        if ( rem.hasMatch() )
        {
            luksVersion = rem.captured( 1 ).toInt();
        }
    }
    return luksVersion;
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
