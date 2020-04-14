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

#include "CreateVolumeGroupJob.h"

// KPMcore
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/ops/createvolumegroupoperation.h>
#include <kpmcore/util/report.h>

CreateVolumeGroupJob::CreateVolumeGroupJob( QString& vgName, QVector< const Partition* > pvList, const qint32 peSize )
    : m_vgName( vgName )
    , m_pvList( pvList )
    , m_peSize( peSize )
{
}

QString
CreateVolumeGroupJob::prettyName() const
{
    return tr( "Create new volume group named %1." ).arg( m_vgName );
}

QString
CreateVolumeGroupJob::prettyDescription() const
{
    return tr( "Create new volume group named <strong>%1</strong>." ).arg( m_vgName );
}

QString
CreateVolumeGroupJob::prettyStatusMessage() const
{
    return tr( "Creating new volume group named %1." ).arg( m_vgName );
}

Calamares::JobResult
CreateVolumeGroupJob::exec()
{
    Report report( nullptr );

    CreateVolumeGroupOperation op( m_vgName, m_pvList, m_peSize );

    op.setStatus( Operation::StatusRunning );

    QString message = tr( "The installer failed to create a volume group named '%1'." ).arg( m_vgName );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( message, report.toText() );
}

void
CreateVolumeGroupJob::updatePreview()
{
    LvmDevice::s_DirtyPVs << m_pvList;
}

void
CreateVolumeGroupJob::undoPreview()
{
    for ( const auto& pv : m_pvList )
    {
        if ( LvmDevice::s_DirtyPVs.contains( pv ) )
        {
            LvmDevice::s_DirtyPVs.removeAll( pv );
        }
    }
}
