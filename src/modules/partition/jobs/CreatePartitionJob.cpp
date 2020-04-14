/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2020, Adriaan de Groot <groot@kde.org>
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

#include "CreatePartitionJob.h"

#include "partition/FileSystem.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/ops/newoperation.h>
#include <kpmcore/util/report.h>

using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

CreatePartitionJob::CreatePartitionJob( Device* device, Partition* partition )
    : PartitionJob( partition )
    , m_device( device )
{
}

QString
CreatePartitionJob::prettyName() const
{
    return tr( "Create new %2MiB partition on %4 (%3) with file system %1." )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
        .arg( m_device->name() )
        .arg( m_device->deviceNode() );
}


QString
CreatePartitionJob::prettyDescription() const
{
    return tr( "Create new <strong>%2MiB</strong> partition on <strong>%4</strong> "
               "(%3) with file system <strong>%1</strong>." )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( CalamaresUtils::BytesToMiB( m_partition->capacity() ) )
        .arg( m_device->name() )
        .arg( m_device->deviceNode() );
}


QString
CreatePartitionJob::prettyStatusMessage() const
{
    return tr( "Creating new %1 partition on %2." )
        .arg( userVisibleFS( m_partition->fileSystem() ) )
        .arg( m_device->deviceNode() );
}

Calamares::JobResult
CreatePartitionJob::exec()
{
    Report report( nullptr );
    NewOperation op( *m_device, m_partition );
    op.setStatus( Operation::StatusRunning );

    QString message = tr( "The installer failed to create partition on disk '%1'." ).arg( m_device->name() );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( message, report.toText() );
}

void
CreatePartitionJob::updatePreview()
{
    m_device->partitionTable()->removeUnallocated();
    m_partition->parent()->insert( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}
