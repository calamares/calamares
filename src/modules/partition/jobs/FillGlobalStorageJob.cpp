/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "FillGlobalStorageJob.h"

#include "core/KPMHelpers.h"
#include "core/PartitionInfo.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/FileSystem.h"
#include "partition/PartitionIterator.h"
#include "utils/Logger.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/fs/luks.h>

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QProcess>

using CalamaresUtils::Partition::PartitionIterator;
using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

typedef QHash< QString, QString > UuidForPartitionHash;

static UuidForPartitionHash
findPartitionUuids( QList< Device* > devices )
{
    UuidForPartitionHash hash;
    foreach ( Device* device, devices )
    {
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        {
            Partition* p = *it;
            QString path = p->partitionPath();
            QString uuid = p->fileSystem().readUUID( p->partitionPath() );
            hash.insert( path, uuid );
        }
    }

    if ( hash.isEmpty() )
    {
        cDebug() << "No UUIDs found for existing partitions.";
    }
    return hash;
}


static QString
getLuksUuid( const QString& path )
{
    QProcess process;
    process.setProgram( "cryptsetup" );
    process.setArguments( { "luksUUID", path } );
    process.start();
    process.waitForFinished();
    if ( process.exitStatus() != QProcess::NormalExit || process.exitCode() )
    {
        return QString();
    }
    QString uuid = QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed();
    return uuid;
}


static QVariant
mapForPartition( Partition* partition, const QString& uuid )
{
    QVariantMap map;
    map[ "device" ] = partition->partitionPath();
    map[ "mountPoint" ] = PartitionInfo::mountPoint( partition );
    map[ "fsName" ] = userVisibleFS( partition->fileSystem() );
    map[ "fs" ] = untranslatedFS( partition->fileSystem() );
    if ( partition->fileSystem().type() == FileSystem::Luks
         && dynamic_cast< FS::luks& >( partition->fileSystem() ).innerFS() )
    {
        map[ "fs" ] = untranslatedFS( dynamic_cast< FS::luks& >( partition->fileSystem() ).innerFS() );
    }
    map[ "uuid" ] = uuid;
    map[ "claimed" ] = PartitionInfo::format( partition );  // If we formatted it, it's ours

    // Debugging for inside the loop in createPartitionList(),
    // so indent a bit
    Logger::CDebug deb;
    using TR = Logger::DebugRow< const char* const, const QString& >;
    deb << Logger::SubEntry << "mapping for" << partition->partitionPath() << partition->deviceNode()
        << TR( "mtpoint:", PartitionInfo::mountPoint( partition ) ) << TR( "fs:", map[ "fs" ].toString() )
        << TR( "fsName", map[ "fsName" ].toString() ) << TR( "uuid", uuid )
        << TR( "claimed", map[ "claimed" ].toString() );

    if ( partition->roles().has( PartitionRole::Luks ) )
    {
        const FileSystem& fsRef = partition->fileSystem();
        const FS::luks* luksFs = dynamic_cast< const FS::luks* >( &fsRef );
        if ( luksFs )
        {
            map[ "luksMapperName" ] = luksFs->mapperName().split( "/" ).last();
            map[ "luksUuid" ] = getLuksUuid( partition->partitionPath() );
            map[ "luksPassphrase" ] = luksFs->passphrase();
            deb << TR( "luksMapperName:", map[ "luksMapperName" ].toString() );
        }
    }

    return map;
}

FillGlobalStorageJob::FillGlobalStorageJob( QList< Device* > devices, const QString& bootLoaderPath )
    : m_devices( devices )
    , m_bootLoaderPath( bootLoaderPath )
{
}

QString
FillGlobalStorageJob::prettyName() const
{
    return tr( "Set partition information" );
}


QString
FillGlobalStorageJob::prettyDescription() const
{
    QStringList lines;

    const auto partitionList = createPartitionList();
    for ( const QVariant& partitionItem : partitionList )
    {
        if ( partitionItem.type() == QVariant::Map )
        {
            QVariantMap partitionMap = partitionItem.toMap();
            QString path = partitionMap.value( "device" ).toString();
            QString mountPoint = partitionMap.value( "mountPoint" ).toString();
            QString fsType = partitionMap.value( "fs" ).toString();
            if ( mountPoint.isEmpty() || fsType.isEmpty() )
            {
                continue;
            }
            if ( path.isEmpty() )
            {
                if ( mountPoint == "/" )
                {
                    lines.append( tr( "Install %1 on <strong>new</strong> %2 system partition." )
                                      .arg( *Calamares::Branding::ShortProductName )
                                      .arg( fsType ) );
                }
                else
                {
                    lines.append( tr( "Set up <strong>new</strong> %2 partition with mount point "
                                      "<strong>%1</strong>." )
                                      .arg( mountPoint )
                                      .arg( fsType ) );
                }
            }
            else
            {
                if ( mountPoint == "/" )
                {
                    lines.append( tr( "Install %2 on %3 system partition <strong>%1</strong>." )
                                      .arg( path )
                                      .arg( *Calamares::Branding::ShortProductName )
                                      .arg( fsType ) );
                }
                else
                {
                    lines.append( tr( "Set up %3 partition <strong>%1</strong> with mount point "
                                      "<strong>%2</strong>." )
                                      .arg( path )
                                      .arg( mountPoint )
                                      .arg( fsType ) );
                }
            }
        }
    }

    QVariant bootloaderMap = createBootLoaderMap();
    if ( !m_bootLoaderPath.isEmpty() )
    {
        lines.append( tr( "Install boot loader on <strong>%1</strong>." ).arg( m_bootLoaderPath ) );
    }
    return lines.join( "<br/>" );
}


QString
FillGlobalStorageJob::prettyStatusMessage() const
{
    return tr( "Setting up mount points." );
}


/** @brief note which FS'ses are in use in GS
 *
 * .. mark as "1" if it's on the system, somewhere
 * .. mark as "2" if it's one of the claimed / in-use FSses
 *
 * Stores a GS key called "filesystems_use" with this mapping.
 */
static void
storeFSUse( Calamares::GlobalStorage* storage, const QVariantList& partitions )
{
    QMap< QString, int > fsUses;
    for ( const auto& p : partitions )
    {
        const auto pmap = p.toMap();

        QString fs = pmap.value( "fs" ).toString();
        int thisUse = pmap.value( "claimed" ).toBool() ? 2 : 1;

        if ( fs.isEmpty() )
        {
            continue;
        }

        int newUse = qMax( fsUses.value( fs ), thisUse );  // value() is 0 if not present
        fsUses.insert( fs, newUse );
    }

    QVariantMap fsUsesVariant;
    for ( auto it = fsUses.cbegin(); it != fsUses.cend(); ++it )
    {
        fsUsesVariant.insert( it.key(), it.value() );
    }

    storage->insert( "filesystems_use", fsUsesVariant );
}

Calamares::JobResult
FillGlobalStorageJob::exec()
{
    Calamares::GlobalStorage* storage = Calamares::JobQueue::instance()->globalStorage();
    const auto partitions = createPartitionList();
    cDebug() << "Saving partition information map to GlobalStorage[\"partitions\"]";
    storage->insert( "partitions", partitions );
    storeFSUse( storage, partitions );

    if ( !m_bootLoaderPath.isEmpty() )
    {
        QVariant var = createBootLoaderMap();
        if ( !var.isValid() )
        {
            cDebug() << "Failed to find path for boot loader";
        }
        cDebug() << "FillGlobalStorageJob writing bootLoader path:" << var;
        storage->insert( "bootLoader", var );
    }
    else
    {
        cDebug() << "FillGlobalStorageJob writing empty bootLoader value";
        storage->insert( "bootLoader", QVariant() );
    }
    return Calamares::JobResult::ok();
}

QVariantList
FillGlobalStorageJob::createPartitionList() const
{
    UuidForPartitionHash hash = findPartitionUuids( m_devices );
    QVariantList lst;
    cDebug() << "Building partition information map";
    for ( auto device : m_devices )
    {
        cDebug() << Logger::SubEntry << "partitions on" << device->deviceNode();
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        {
            // Debug-logging is done when creating the map
            lst << mapForPartition( *it, hash.value( ( *it )->partitionPath() ) );
        }
    }
    return lst;
}

QVariant
FillGlobalStorageJob::createBootLoaderMap() const
{
    QVariantMap map;
    QString path = m_bootLoaderPath;
    if ( !path.startsWith( "/dev/" ) )
    {
        Partition* partition = KPMHelpers::findPartitionByMountPoint( m_devices, path );
        if ( !partition )
        {
            return QVariant();
        }
        path = partition->partitionPath();
    }
    map[ "installPath" ] = path;
    return map;
}
