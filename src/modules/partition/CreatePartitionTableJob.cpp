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

#include <CreatePartitionTableJob.h>

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

CreatePartitionTableJob::CreatePartitionTableJob( Device* device, PartitionTable::TableType type )
    : m_device( device )
    , m_type( type )
{
}

QString
CreatePartitionTableJob::prettyName() const
{
    return tr( "Create partition table" ); // FIXME
}

Calamares::JobResult
CreatePartitionTableJob::exec()
{
    Report report( 0 );
    QString message = tr( "The installer failed to create a partition table on %1." ).arg( m_device->name() );

    CoreBackend* backend = CoreBackendManager::self()->backend();
    QScopedPointer< CoreBackendDevice > backendDevice( backend->openDevice( m_device->deviceNode() ) );
    if ( !backendDevice.data() )
    {
        return Calamares::JobResult::error(
                   message,
                   tr( "Could not open device %1." ).arg( m_device->deviceNode() )
               );
    }

    QScopedPointer< PartitionTable > table( createTable() );
    bool ok = backendDevice->createPartitionTable( report, *table );
    if ( !ok )
    {
        return Calamares::JobResult::error(
                   message,
                   report.toText()
               );
    }

    return Calamares::JobResult::ok();
}

void
CreatePartitionTableJob::updatePreview()
{
    // Device takes ownership of its table, but does not destroy the current
    // one when setPartitionTable() is called, so do it ourself
    delete m_device->partitionTable();
    m_device->setPartitionTable( createTable() );
    m_device->partitionTable()->updateUnallocated( *m_device );
}

PartitionTable*
CreatePartitionTableJob::createTable()
{
    return new PartitionTable( m_type,
                               PartitionTable::defaultFirstUsable( *m_device, m_type ),
                               PartitionTable::defaultLastUsable( *m_device, m_type )
                             );
}
