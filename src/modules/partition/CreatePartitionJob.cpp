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

#include <CreatePartitionJob.h>

#include <utils/Logger.h>

// CalaPM
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>
#include <backend/corebackenddevice.h>
#include <backend/corebackendpartition.h>
#include <backend/corebackendpartitiontable.h>
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>
#include <util/report.h>

// Qt
#include <QScopedPointer>

CreatePartitionJob::CreatePartitionJob( Device* device, Partition* partition )
    : m_device( device )
    , m_partition( partition )
{
}

QString
CreatePartitionJob::prettyName() const
{
    return tr( "Create partition" ); // FIXME
}

Calamares::JobResult
CreatePartitionJob::exec()
{
    Report report( 0 );
    QString message = tr( "The installer failed to create partition on disk '%1'." ).arg( m_device->name() );

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

    QString partitionPath = backendPartitionTable->createPartition( report, *m_partition );
    if ( partitionPath.isEmpty() )
    {
        return Calamares::JobResult::error(
                   message,
                   report.toText()
               );
    }
    backendPartitionTable->commit();

    FileSystem& fs = m_partition->fileSystem();
    if ( fs.type() == FileSystem::Unformatted )
        return Calamares::JobResult::ok();

    if ( !fs.create( report, partitionPath ) )
    {
        return Calamares::JobResult::error(
                   tr( "The installer failed to create file system on partition %1." ).arg( partitionPath ),
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

void
CreatePartitionJob::updatePreview()
{
    m_device->partitionTable()->removeUnallocated();
    m_partition->parent()->insert( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}
