/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ResizeVolumeGroupJob.h"

// KPMcore
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/ops/resizevolumegroupoperation.h>
#include <kpmcore/util/report.h>

ResizeVolumeGroupJob::ResizeVolumeGroupJob( Device*, LvmDevice* device, QVector< const Partition* >& partitionList )
    : m_device( device )
    , m_partitionList( partitionList )
{
}

QString
ResizeVolumeGroupJob::prettyName() const
{
    return tr( "Resize volume group named %1 from %2 to %3." )
        .arg( m_device->name() )
        .arg( currentPartitions() )
        .arg( targetPartitions() );
}

QString
ResizeVolumeGroupJob::prettyDescription() const
{
    return tr( "Resize volume group named <strong>%1</strong> from <strong>%2</strong> to <strong>%3</strong>." )
        .arg( m_device->name() )
        .arg( currentPartitions() )
        .arg( targetPartitions() );
}

QString
ResizeVolumeGroupJob::prettyStatusMessage() const
{
    return tr( "Resize volume group named %1 from %2 to %3." )
        .arg( m_device->name() )
        .arg( currentPartitions() )
        .arg( targetPartitions() );
}

Calamares::JobResult
ResizeVolumeGroupJob::exec()
{
    Report report( nullptr );

    ResizeVolumeGroupOperation op( *m_device, m_partitionList );

    op.setStatus( Operation::OperationStatus::StatusRunning );

    QString message = tr( "The installer failed to resize a volume group named '%1'." ).arg( m_device->name() );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( message, report.toText() );
}

QString
ResizeVolumeGroupJob::currentPartitions() const
{
    QString result;

    for ( const Partition* p : m_device->physicalVolumes() )
    {
        result += p->deviceNode() + ", ";
    }

    result.chop( 2 );

    return result;
}

QString
ResizeVolumeGroupJob::targetPartitions() const
{
    QString result;

    for ( const Partition* p : m_partitionList )
    {
        result += p->deviceNode() + ", ";
    }

    result.chop( 2 );

    return result;
}
