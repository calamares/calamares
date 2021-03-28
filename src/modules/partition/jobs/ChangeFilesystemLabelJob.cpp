/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016, Lisa Vitolo <shainer@chakraos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ChangeFilesystemLabelJob.h"

#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/ops/setfilesystemlabeloperation.h>
#include <kpmcore/util/report.h>

ChangeFilesystemLabelJob::ChangeFilesystemLabelJob( Device* device, Partition* partition, const QString& newLabel )
    : PartitionJob( partition )
    , m_device( device )
    , m_label( newLabel )
{
}


QString
ChangeFilesystemLabelJob::prettyName() const
{
    return tr( "Set filesystem label on %1." ).arg( partition()->partitionPath() );
}


QString
ChangeFilesystemLabelJob::prettyDescription() const
{
    return tr( "Set filesystem label <strong>%1</strong> to partition "
               "<strong>%2</strong>." )
        .arg( m_label )
        .arg( partition()->partitionPath() );
}


QString
ChangeFilesystemLabelJob::prettyStatusMessage() const
{
    return prettyDescription();
}


Calamares::JobResult
ChangeFilesystemLabelJob::exec()
{
    if ( m_label == partition()->fileSystem().label() )
    {
        return Calamares::JobResult::ok();
    }

    Report report( nullptr );
    SetFileSystemLabelOperation op( *partition(), m_label );
    op.setStatus( Operation::StatusRunning );

    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }
    return Calamares::JobResult::error(
        tr( "The installer failed to update partition table on disk '%1'." ).arg( m_device->name() ), report.toText() );
}
