/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "RemoveVolumeGroupJob.h"

#include "core/KPMHelpers.h"

#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/ops/removevolumegroupoperation.h>
#include <kpmcore/util/report.h>

RemoveVolumeGroupJob::RemoveVolumeGroupJob( Device*, LvmDevice* device )
    : m_device( device )
{
}

QString
RemoveVolumeGroupJob::prettyName() const
{
    return tr( "Remove Volume Group named %1." ).arg( m_device->name() );
}

QString
RemoveVolumeGroupJob::prettyDescription() const
{
    return tr( "Remove Volume Group named <strong>%1</strong>." ).arg( m_device->name() );
}

QString
RemoveVolumeGroupJob::prettyStatusMessage() const
{
    return tr( "Remove Volume Group named %1." ).arg( m_device->name() );
}

Calamares::JobResult
RemoveVolumeGroupJob::exec()
{
    return KPMHelpers::execute(
        RemoveVolumeGroupOperation( *m_device ),
        tr( "The installer failed to remove a volume group named '%1'." ).arg( m_device->name() ) );
}
