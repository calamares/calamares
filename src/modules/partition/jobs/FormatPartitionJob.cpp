/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include "jobs/FormatPartitionJob.h"

#include "utils/Logger.h"

// KPMcore
#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/backend/corebackenddevice.h>
#include <kpmcore/backend/corebackendpartition.h>
#include <kpmcore/backend/corebackendpartitiontable.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/util/report.h>

// Qt
#include <QScopedPointer>
#include <QThread>

FormatPartitionJob::FormatPartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
FormatPartitionJob::prettyName() const
{
    return tr( "Format partition %1 (file system: %2, size: %3 MB) on %4." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() )
           .arg( m_partition->capacity() / 1024 / 1024 )
            .arg( m_device->name() );
}


QString
FormatPartitionJob::prettyDescription() const
{
    return tr( "Format <strong>%3MB</strong> partition <strong>%1</strong> with "
               "file system <strong>%2</strong>." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() )
            .arg( m_partition->capacity() / 1024 / 1024 );
}


QString
FormatPartitionJob::prettyStatusMessage() const
{
    return tr( "Formatting partition %1 with "
               "file system %2." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() );
}


Calamares::JobResult
FormatPartitionJob::exec()
{
    Report report( nullptr );  // Root of the report tree, no parent
    QString partitionPath = m_partition->partitionPath();
    QString message = tr( "The installer failed to format partition %1 on disk '%2'." ).arg( partitionPath, m_device->name() );

    CoreBackend* backend = CoreBackendManager::self()->backend();
    QScopedPointer<CoreBackendDevice> backendDevice( backend->openDevice( m_device->deviceNode() ) );
    if ( !backendDevice.data() )
    {
        return Calamares::JobResult::error(
                   message,
                   tr( "Could not open device '%1'." ).arg( m_device->deviceNode() )
               );
    }

    QScopedPointer<CoreBackendPartitionTable> backendPartitionTable( backendDevice->openPartitionTable() );
    if ( !backendPartitionTable.data() )
    {
        return Calamares::JobResult::error(
                   message,
                   tr( "Could not open partition table." )
               );
    }

    FileSystem& fs = m_partition->fileSystem();

    bool ok = fs.create( report, partitionPath );
    int retries = 0;
    const int MAX_RETRIES = 10;
    while ( !ok )
    {
        cDebug() << "Partition" << m_partition->partitionPath()
                 << "might not be ready yet, retrying (" << ++retries
                 << "/" << MAX_RETRIES << ") ...";
        QThread::sleep( 2 /*seconds*/ );
        ok = fs.create( report, partitionPath );

        if ( retries == MAX_RETRIES )
            break;
    }

    if ( !ok )
    {
        return Calamares::JobResult::error(
                   tr( "The installer failed to create file system on partition %1." )
                   .arg( partitionPath ),
                   report.toText()
               );
    }

    if ( !backendPartitionTable->setPartitionSystemType( report, *m_partition ) )
    {
        return Calamares::JobResult::error(
                   tr( "The installer failed to update partition table on disk '%1'." ).arg( m_device->name() ),
                   report.toText()
               );
    }

    backendPartitionTable->commit();
    return Calamares::JobResult::ok();
}
