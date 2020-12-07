/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "DeletePartitionJob.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/deleteoperation.h>
#include <kpmcore/util/report.h>

DeletePartitionJob::DeletePartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
DeletePartitionJob::prettyName() const
{
    return tr( "Delete partition %1." ).arg( m_partition->partitionPath() );
}


QString
DeletePartitionJob::prettyDescription() const
{
    return tr( "Delete partition <strong>%1</strong>." ).arg( m_partition->partitionPath() );
}


QString
DeletePartitionJob::prettyStatusMessage() const
{
    return tr( "Deleting partition %1." ).arg( m_partition->partitionPath() );
}


Calamares::JobResult
DeletePartitionJob::exec()
{
    Report report( nullptr );
    DeleteOperation op( *m_device, m_partition );
    op.setStatus( Operation::StatusRunning );

    QString message = tr( "The installer failed to delete partition %1." ).arg( m_partition->devicePath() );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( message, report.toText() );
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
