/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Caio Jordão Carvalho <caiojcarvalho@gmail.com>
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

#include "ResizeVolumeGroupJob.h"

// KPMcore
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/ops/resizevolumegroupoperation.h>
#include <kpmcore/util/report.h>

ResizeVolumeGroupJob::ResizeVolumeGroupJob( LvmDevice* device, QVector< const Partition* >& partitionList )
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
