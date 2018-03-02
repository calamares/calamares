/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "jobs/DeletePartitionJob.h"

// KPMcore
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>
#include <ops/deleteoperation.h>
#include <util/report.h>

DeletePartitionJob::DeletePartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
DeletePartitionJob::prettyName() const
{
    return tr( "Delete partition %1." )
            .arg( m_partition->partitionPath() );
}


QString
DeletePartitionJob::prettyDescription() const
{
    return tr( "Delete partition <strong>%1</strong>." )
            .arg( m_partition->partitionPath() );
}


QString
DeletePartitionJob::prettyStatusMessage() const
{
    return tr( "Deleting partition %1." )
            .arg( m_partition->partitionPath() );
}


Calamares::JobResult
DeletePartitionJob::exec()
{
    Report report( nullptr );
    DeleteOperation op(*m_device, m_partition);
    op.setStatus(Operation::StatusRunning);

    QString message = tr( "The installer failed to delete partition %1." ).arg( m_partition->devicePath() );
    if (op.execute(report))
        return Calamares::JobResult::ok();

    return Calamares::JobResult::error(message, report.toText());
}

void
DeletePartitionJob::updatePreview()
{
    m_partition->parent()->remove( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );

    // Copied from PM DeleteOperation::checkAdjustLogicalNumbers():
    //
    // If the deleted partition is a logical one, we need to adjust the numbers
    // of the other logical partitions in the extended one, if there are any,
    // because the OS will do that, too: Logicals must be numbered without gaps,
    // i.e., a numbering like sda5, sda6, sda8 (after sda7 is deleted) will
    // become sda5, sda6, sda7
    Partition* parentPartition = dynamic_cast< Partition* >( m_partition->parent() );
    if ( parentPartition && parentPartition->roles().has( PartitionRole::Extended ) )
        parentPartition->adjustLogicalNumbers( m_partition->number(), -1 );
}
