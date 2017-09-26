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

#include "jobs/CreatePartitionTableJob.h"

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
#include <QProcess>

CreatePartitionTableJob::CreatePartitionTableJob( Device* device, PartitionTable::TableType type )
    : m_device( device )
    , m_type( type )
{
}

QString
CreatePartitionTableJob::prettyName() const
{
    return tr( "Create new %1 partition table on %2." )
            .arg( PartitionTable::tableTypeToName( m_type ) )
            .arg( m_device->deviceNode() );
}

QString CreatePartitionTableJob::prettyDescription() const
{
    return tr( "Create new <strong>%1</strong> partition table on <strong>%2</strong> (%3)." )
            .arg( PartitionTable::tableTypeToName( m_type ).toUpper() )
            .arg( m_device->deviceNode() )
            .arg( m_device->name() );
}


QString
CreatePartitionTableJob::prettyStatusMessage() const
{
    return tr( "Creating new %1 partition table on %2." )
            .arg( PartitionTable::tableTypeToName( m_type ).toUpper() )
            .arg( m_device->deviceNode() );
}


Calamares::JobResult
CreatePartitionTableJob::exec()
{
    Report report( nullptr );
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
    cDebug() << "Creating new partition table of type" << table->typeName()
             << ", uncommitted yet:\n" << table;

    QProcess lsblk;
    lsblk.setProgram( "lsblk" );
    lsblk.setProcessChannelMode( QProcess::MergedChannels );
    lsblk.start();
    lsblk.waitForFinished();
    cDebug() << "lsblk:\n" << lsblk.readAllStandardOutput();

    QProcess mount;
    mount.setProgram( "mount" );
    mount.setProcessChannelMode( QProcess::MergedChannels );
    mount.start();
    mount.waitForFinished();
    cDebug() << "mount:\n" << mount.readAllStandardOutput();

    bool ok = backendDevice->createPartitionTable( report, *table );
    if ( !ok )
    {
        return Calamares::JobResult::error(
                    message,
                    QString( "Text: %1\nCommand: %2\nOutput: %3\nStatus: %4" )
                        .arg( report.toText() )
                        .arg( report.command() )
                        .arg( report.output() )
                        .arg( report.status() )
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
    cDebug() << "CreatePartitionTableJob::createTable trying to make table for device"
             << m_device->deviceNode();
    return new PartitionTable( m_type,
                               PartitionTable::defaultFirstUsable( *m_device, m_type ),
                               PartitionTable::defaultLastUsable( *m_device, m_type )
                             );
}
