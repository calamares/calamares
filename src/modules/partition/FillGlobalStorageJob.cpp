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

#include <FillGlobalStorageJob.h>

#include <GlobalStorage.h>
#include <JobQueue.h>
#include <PartitionInfo.h>
#include <PartitionIterator.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>

FillGlobalStorageJob::FillGlobalStorageJob( QList< Device* > devices )
    : m_devices( devices )
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
    QVariantList lst;
    for( auto device : m_devices )
        for( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it)
        {
            QVariant var = mapForPartition( *it );
            if ( var.isValid() )
                lst << var;
        }
    Calamares::JobQueue::instance()->globalStorage()->insert( "partitions", lst );
    return Calamares::JobResult::ok();
}

QVariant
FillGlobalStorageJob::mapForPartition( Partition* partition )
{
    QVariantMap map;
    map[ "device" ] = partition->partitionPath();
    map[ "mountPoint" ] = PartitionInfo::mountPoint( partition );
    map[ "fs" ] = partition->fileSystem().name();
    return map;
}
