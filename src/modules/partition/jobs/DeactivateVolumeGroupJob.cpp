/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    return tr( "Deactivate volume group named %1." ).arg( m_device->name() );
}

QString
DeactivateVolumeGroupJob::prettyDescription() const
{
    return tr( "Deactivate volume group named <strong>%1</strong>." ).arg( m_device->name() );
}

QString
DeactivateVolumeGroupJob::prettyStatusMessage() const
{
    return tr( "Deactivate volume group named %1." ).arg( m_device->name() );
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

    return Calamares::JobResult::error( message, report.toText() );
}
