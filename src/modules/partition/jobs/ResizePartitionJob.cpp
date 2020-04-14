/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Andrius Štikonas <andrius@stikonas.eu>
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

#include "ResizePartitionJob.h"

#include "utils/Units.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/ops/resizeoperation.h>
#include <kpmcore/util/report.h>

using CalamaresUtils::BytesToMiB;

//- ResizePartitionJob ---------------------------------------------------------
ResizePartitionJob::ResizePartitionJob( Device* device, Partition* partition, qint64 firstSector, qint64 lastSector )
    : PartitionJob( partition )
    , m_device( device )
    , m_oldFirstSector(
          partition->firstSector() )  // Keep a copy of old sectors because they will be overwritten in updatePreview()
    , m_oldLastSector( partition->lastSector() )
    , m_newFirstSector( firstSector )
    , m_newLastSector( lastSector )
{
}

QString
ResizePartitionJob::prettyName() const
{
    // FIXME: Copy PM ResizeOperation code which generates a description of the
    // operation
    return tr( "Resize partition %1." ).arg( partition()->partitionPath() );
}


QString
ResizePartitionJob::prettyDescription() const
{
    return tr( "Resize <strong>%2MiB</strong> partition <strong>%1</strong> to "
               "<strong>%3MiB</strong>." )
        .arg( partition()->partitionPath() )
        .arg( ( BytesToMiB( m_oldLastSector - m_oldFirstSector + 1 ) * partition()->sectorSize() ) )
        .arg( ( BytesToMiB( m_newLastSector - m_newFirstSector + 1 ) * partition()->sectorSize() ) );
}


QString
ResizePartitionJob::prettyStatusMessage() const
{
    return tr( "Resizing %2MiB partition %1 to "
               "%3MiB." )
        .arg( partition()->partitionPath() )
        .arg( ( BytesToMiB( m_oldLastSector - m_oldFirstSector + 1 ) * partition()->sectorSize() ) )
        .arg( ( BytesToMiB( m_newLastSector - m_newFirstSector + 1 ) * partition()->sectorSize() ) );
}


Calamares::JobResult
ResizePartitionJob::exec()
{
    Report report( nullptr );
    // Restore partition sectors that were modified for preview
    m_partition->setFirstSector( m_oldFirstSector );
    m_partition->setLastSector( m_oldLastSector );
    ResizeOperation op( *m_device, *m_partition, m_newFirstSector, m_newLastSector );
    op.setStatus( Operation::StatusRunning );
    connect( &op, &Operation::progress, this, &ResizePartitionJob::iprogress );

    QString errorMessage = tr( "The installer failed to resize partition %1 on disk '%2'." )
                               .arg( m_partition->partitionPath() )
                               .arg( m_device->name() );
    if ( op.execute( report ) )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( errorMessage, report.toText() );
}

void
ResizePartitionJob::updatePreview()
{
    m_device->partitionTable()->removeUnallocated();
    m_partition->parent()->remove( m_partition );
    m_partition->setFirstSector( m_newFirstSector );
    m_partition->setLastSector( m_newLastSector );
    m_partition->parent()->insert( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}


Device*
ResizePartitionJob::device() const
{
    return m_device;
}
