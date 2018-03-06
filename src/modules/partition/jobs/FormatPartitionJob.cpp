/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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

#include "jobs/FormatPartitionJob.h"

#include "utils/Logger.h"

// KPMcore
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>
#include <ops/createfilesystemoperation.h>
#include <util/report.h>

FormatPartitionJob::FormatPartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
FormatPartitionJob::prettyName() const
{
    return tr( "Format partition %1 (file system: %2, size: %3 MB) on %4." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() )
           .arg( m_partition->capacity() / 1024 / 1024 )
            .arg( m_device->name() );
}


QString
FormatPartitionJob::prettyDescription() const
{
    return tr( "Format <strong>%3MB</strong> partition <strong>%1</strong> with "
               "file system <strong>%2</strong>." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() )
            .arg( m_partition->capacity() / 1024 / 1024 );
}


QString
FormatPartitionJob::prettyStatusMessage() const
{
    return tr( "Formatting partition %1 with "
               "file system %2." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() );
}


Calamares::JobResult
FormatPartitionJob::exec()
{
    Report report( nullptr );  // Root of the report tree, no parent
    CreateFileSystemOperation op(*m_device, *m_partition, m_partition->fileSystem().type());
    op.setStatus(Operation::StatusRunning);

    QString message = tr( "The installer failed to format partition %1 on disk '%2'." ).arg( m_partition->partitionPath(), m_device->name() );

    if (op.execute(report))
        return Calamares::JobResult::ok();

    return Calamares::JobResult::error(message, report.toText());
}
