/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "jobs/CreatePartitionJob.h"

#include "utils/Logger.h"
#include "utils/Units.h"

// KPMcore
#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/backend/corebackenddevice.h>
#include <kpmcore/backend/corebackendpartition.h>
#include <kpmcore/backend/corebackendpartitiontable.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/util/report.h>

// Qt
#include <QScopedPointer>

CreatePartitionJob::CreatePartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
CreatePartitionJob::prettyName() const
{
    return tr( "Create new %2MB partition on %4 (%3) with file system %1." )
            .arg( m_partition->fileSystem().name() )
            .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
            .arg( m_device->name() )
            .arg( m_device->deviceNode() );
}


QString
CreatePartitionJob::prettyDescription() const
{
    return tr( "Create new <strong>%2MB</strong> partition on <strong>%4</strong> "
               "(%3) with file system <strong>%1</strong>." )
            .arg( m_partition->fileSystem().name() )
            .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
            .arg( m_device->name() )
            .arg( m_device->deviceNode() );
}


QString
CreatePartitionJob::prettyStatusMessage() const
{
    return tr( "Creating new %1 partition on %2." )
            .arg( m_partition->fileSystem().name() )
            .arg( m_device->deviceNode() );
}

Calamares::JobResult
CreatePartitionJob::exec()
{
    QString partitionPath;
    FileSystem *fs;
    Report report( nullptr );

    if (m_device->type() == Device::Disk_Device) {
        int step = 0;
        const qreal stepCount = 4;
        QString message = tr( "The installer failed to create partition on disk '%1'." ).arg( m_device->name() );

        progress( step++ / stepCount );
        CoreBackend* backend = CoreBackendManager::self()->backend();
        QScopedPointer<CoreBackendDevice> backendDevice( backend->openDevice( m_device->deviceNode() ) );
        if ( !backendDevice.data() )
        {
            return Calamares::JobResult::error(
                       message,
                       tr( "Could not open device '%1'." ).arg( m_device->deviceNode() )
                   );
        }

        progress( step++ / stepCount );
        QScopedPointer<CoreBackendPartitionTable> backendPartitionTable( backendDevice->openPartitionTable() );
        if ( !backendPartitionTable.data() )
        {
            return Calamares::JobResult::error(
                       message,
                       tr( "Could not open partition table." )
                   );
        }

        progress( step++ / stepCount );
        partitionPath = backendPartitionTable->createPartition( report, *m_partition );
        if ( partitionPath.isEmpty() )
        {
            return Calamares::JobResult::error(
                       message,
                       report.toText()
                   );
        }
        m_partition->setPartitionPath( partitionPath );
        backendPartitionTable->commit();

        progress( step++ / stepCount );
        fs = &m_partition->fileSystem();
        if ( fs->type() == FileSystem::Unformatted || fs->type() == FileSystem::Extended )
            return Calamares::JobResult::ok();

        if ( !backendPartitionTable->setPartitionSystemType( report, *m_partition ) )
        {
            return Calamares::JobResult::error(
                       tr( "The installer failed to update partition table on disk '%1'." ).arg( m_device->name() ),
                       report.toText()
                   );
        }

        backendPartitionTable->commit();
    }
    else
    {
        LvmDevice *dev = dynamic_cast<LvmDevice*>(m_device);
        m_partition->setState(Partition::StateNone);

        partitionPath = m_partition->partitionPath();
        QString lvname  = partitionPath.right(partitionPath.length() - partitionPath.lastIndexOf(QStringLiteral("/")) - 1);
        if ( !LvmDevice::createLV(report, *dev, *m_partition, lvname))
        {
            return Calamares::JobResult::error(
                       tr( "The installer failed to create LVM logical volume %1." ).arg( lvname ),
                       report.toText()
                   );
        }
        fs = &m_partition->fileSystem();
    }

    if ( !fs->create( report, partitionPath ) )
    {
        return Calamares::JobResult::error(
                   tr( "The installer failed to create file system on partition %1." ).arg( partitionPath ),
                   report.toText()
               );
    }

    return Calamares::JobResult::ok();
}

void
CreatePartitionJob::updatePreview()
{
    m_device->partitionTable()->removeUnallocated();
    m_partition->parent()->insert( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}
