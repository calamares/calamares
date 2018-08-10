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

#include "DeactivateVolumeGroupJob.h"

#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/ops/deactivatevolumegroupoperation.h>
#include <kpmcore/util/report.h>

DeactivateVolumeGroupJob::DeactivateVolumeGroupJob( LvmDevice* device )
    : m_device( device )
{

}

QString
DeactivateVolumeGroupJob::prettyName() const
{
    return tr( "Deactivate volume group named %1." )
            .arg( m_device->name() );
}

QString
DeactivateVolumeGroupJob::prettyDescription() const
{
    return tr( "Deactivate volume group named <strong>%1</strong>." )
            .arg( m_device->name() );
}

QString
DeactivateVolumeGroupJob::prettyStatusMessage() const
{
    return tr( "Deactivate volume group named %1." )
            .arg( m_device->name() );
}

Calamares::JobResult
DeactivateVolumeGroupJob::exec()
{
    Report report( nullptr );

    DeactivateVolumeGroupOperation op( *m_device );

    op.setStatus( Operation::OperationStatus::StatusRunning );

    QString message = tr( "The installer failed to deactivate a volume group named %1." ).arg( m_device->name() );
    if ( op.execute( report ) )
    {
        op.preview();
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error(message, report.toText());
}
