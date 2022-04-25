/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "FormatPartitionJob.h"

#include "core/KPMHelpers.h"

#include "partition/FileSystem.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/createfilesystemoperation.h>
#include <kpmcore/util/report.h>

using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

FormatPartitionJob::FormatPartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
FormatPartitionJob::prettyName() const
{
    return tr( "Format partition %1 (file system: %2, size: %3 MiB) on %4." )
        .arg( m_partition->partitionPath() )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( m_partition->capacity() / 1024 / 1024 )
        .arg( m_device->name() );
}


QString
FormatPartitionJob::prettyDescription() const
{
    return tr( "Format <strong>%3MiB</strong> partition <strong>%1</strong> with "
               "file system <strong>%2</strong>." )
        .arg( m_partition->partitionPath() )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( m_partition->capacity() / 1024 / 1024 );
}


QString
FormatPartitionJob::prettyStatusMessage() const
{
    QString partitionLabel = m_partition->label().isEmpty()
        ? m_partition->partitionPath()
        : tr( "%1 (%2)", "partition label %1 (device path %2)" )
              .arg( m_partition->label(), m_partition->partitionPath() );
    return tr( "Formatting partition %1 with "
               "file system %2." )
        .arg( partitionLabel, userVisibleFS( m_partition->fileSystem() ) );
}


Calamares::JobResult
FormatPartitionJob::exec()
{
    const auto fsType = m_partition->fileSystem().type();
    auto r = KPMHelpers::execute( CreateFileSystemOperation( *m_device, *m_partition, fsType ),
                                  tr( "The installer failed to format partition %1 on disk '%2'." )
                                      .arg( m_partition->partitionPath(), m_device->name() ) );
    if ( fsType == FileSystem::Xfs && r.succeeded() )
    {
        // We are going to try to set modern timestamps for the filesystem,
        // (ignoring whether this succeeds). Requires a sufficiently-new
        // xfs_admin and xfs_repair and might be made obsolete by newer
        // kpmcore releases.
        CalamaresUtils::System::runCommand( { "xfs_admin", "-O", "bigtime=1", m_partition->partitionPath() },
                                            std::chrono::seconds( 60 ) );
    }
    return r;
}
