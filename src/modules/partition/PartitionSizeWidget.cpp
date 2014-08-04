/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <PartitionSizeWidget.h>

#include <utils/Logger.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>

PartitionSizeWidget::PartitionSizeWidget( QWidget* parent )
    : QSpinBox( parent )
{
}

void
PartitionSizeWidget::init( Device* device, Partition* partition )
{
    m_device = device;
    m_partition = partition;
    Q_ASSERT( m_device->partitionTable() );

    qint64 minSector = computeMinSector();
    qint64 maxSector = computeMaxSector();
    cLog() << minSector << maxSector;
    setMaximum( mbSizeForSectorRange( minSector, maxSector ) );

    m_initialValue = mbSizeForSectorRange( partition->firstSector(), partition->lastSector() );
    setValue( m_initialValue );
}

PartitionSizeWidget::SectorRange
PartitionSizeWidget::sectorRange() const
{
    qint64 minSector = computeMinSector();
    qint64 maxSector = computeMaxSector();

    int mbSize = value();
    if ( mbSize == maximum() )
    {
        // If we are at the maximum value, select the last sector to avoid
        // potential rounding errors which could leave a few sectors at the end
        // unused
        return SectorRange( minSector, maxSector );
    }

    qint64 lastSector = minSector + qint64( mbSize ) * 1024 * 1024 / m_device->logicalSectorSize();
    Q_ASSERT( lastSector <= maxSector );
    if ( lastSector > maxSector )
    {
        cLog() << "lastSector (" << lastSector << ") > maxSector (" << maxSector << "). This should not happen!";
        lastSector = maxSector;
    }
    return SectorRange( minSector, lastSector );
}

bool
PartitionSizeWidget::isDirty() const
{
    return m_initialValue != value();
}

qint64
PartitionSizeWidget::mbSizeForSectorRange( qint64 first, qint64 last ) const
{
    return ( last - first + 1 ) * m_device->logicalSectorSize() / 1024 / 1024;
}

qint64
PartitionSizeWidget::computeMaxSector() const
{
    Q_ASSERT( m_device );
    Q_ASSERT( m_partition );
    return m_partition->lastSector() + m_device->partitionTable()->freeSectorsAfter( *m_partition );
}

qint64
PartitionSizeWidget::computeMinSector() const
{
    Q_ASSERT( m_device );
    Q_ASSERT( m_partition );
    return m_partition->firstSector() - m_device->partitionTable()->freeSectorsBefore( *m_partition );
}
