/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <jobs/FillGlobalStorageJob.h>

#include <GlobalStorage.h>
#include <JobQueue.h>
#include <core/PartitionInfo.h>
#include <core/PartitionIterator.h>
#include <core/PMUtils.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>

// Qt
#include <QDebug>
#include <QDir>
#include <QFileInfo>

typedef QHash<QString, QString> UuidForPartitionHash;

static const char* UUID_DIR = "/dev/disk/by-uuid";

static UuidForPartitionHash
findPartitionUuids()
{
    QDir dir( UUID_DIR );
    UuidForPartitionHash hash;
    for ( auto info : dir.entryInfoList( QDir::Files ) )
    {
        QString uuid = info.fileName();
        QString path = info.canonicalFilePath();
        hash.insert( path, uuid );
    }
    return hash;
}

static QVariant
mapForPartition( Partition* partition, const QString& uuid )
{
    QVariantMap map;
    map[ "device" ] = partition->partitionPath();
    map[ "mountPoint" ] = PartitionInfo::mountPoint( partition );
    map[ "fs" ] = partition->fileSystem().name();
    map[ "uuid" ] = uuid;
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

Calamares::JobResult
FillGlobalStorageJob::exec()
{
    Calamares::GlobalStorage* storage = Calamares::JobQueue::instance()->globalStorage();
    storage->insert( "partitions", createPartitionList() );
    QVariant var = createBootLoaderMap();
    if ( !var.isValid() )
        return Calamares::JobResult::error( tr( "Failed to find path for boot loader" ) );
    storage->insert( "bootLoader", var );
    return Calamares::JobResult::ok();
}

QVariant
FillGlobalStorageJob::createPartitionList()
{
    UuidForPartitionHash hash = findPartitionUuids();
    QVariantList lst;
    for ( auto device : m_devices )
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            lst << mapForPartition( *it, hash.value( ( *it )->partitionPath() ) );
    return lst;
}

QVariant
FillGlobalStorageJob::createBootLoaderMap()
{
    QVariantMap map;
    QString path = m_bootLoaderPath;
    if ( !path.startsWith( "/dev/" ) )
    {
        Partition* partition = PMUtils::findPartitionByMountPoint( m_devices, path );
        if ( !partition )
            return QVariant();
        path = partition->partitionPath();
    }
    map[ "installPath" ] = path;
    return map;
}
