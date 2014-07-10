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

#include <DeletePartitionJob.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>

DeletePartitionJob::DeletePartitionJob( Device* device, Partition* partition )
    : m_device( device )
    , m_partition( partition )
{
}

QString
DeletePartitionJob::prettyName() const
{
    return tr( "Delete partition %1" ).arg( m_partition->partitionPath() );
}

Calamares::JobResult
DeletePartitionJob::exec()
{
    return Calamares::JobResult::ok();
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
    {
        parentPartition->adjustLogicalNumbers( m_partition->number(), -1 );
    }
}
