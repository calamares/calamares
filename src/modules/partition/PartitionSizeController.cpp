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

#include <PartitionSizeController.h>

// Qt
#include <QSpinBox>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <gui/partresizerwidget.h>

// stdc++
#include <limits>

PartitionSizeController::PartitionSizeController( QObject* parent )
    : QObject( parent )
{}

void
PartitionSizeController::setPartResizerWidget( PartResizerWidget* widget )
{
    if ( m_partResizerWidget )
        disconnect( m_partResizerWidget, 0, this, 0 );
    m_partResizerWidget = widget;
    // FIXME: Should be set by PartResizerWidget itself
    m_partResizerWidget->setFixedHeight( PartResizerWidget::handleHeight() );
    updateConnections();
}

void
PartitionSizeController::setSpinBox( QSpinBox* spinBox )
{
    if ( m_spinBox )
        disconnect( m_spinBox, 0, this, 0 );
    m_spinBox = spinBox;
    m_spinBox->setMaximum( std::numeric_limits< int >::max() );
    updateConnections();
}

void
PartitionSizeController::init( Device* device, Partition* partition )
{
    m_device = device;
    m_partition = partition;
}

void
PartitionSizeController::updateConnections()
{
    if ( !m_spinBox || !m_partResizerWidget )
        return;

    connect( m_spinBox, SIGNAL( editingFinished() ), SLOT( updatePartResizerWidget() ) );
    connect( m_partResizerWidget, SIGNAL( firstSectorChanged( qint64 ) ), SLOT( updateSpinBox() ) );
    connect( m_partResizerWidget, SIGNAL( lastSectorChanged( qint64 ) ), SLOT( updateSpinBox() ) );
    updateSpinBox();
}

void
PartitionSizeController::updatePartResizerWidget()
{
    if ( m_updating )
        return;
    m_updating = true;
    qint64 sectorSize = qint64( m_spinBox->value() ) * 1024 * 1024 / m_device->logicalSectorSize();

    qint64 firstSector = m_partition->firstSector();
    qint64 lastSector = firstSector + sectorSize - 1;
    if ( lastSector > m_partResizerWidget->maximumLastSector() )
    {
        qint64 delta = lastSector - m_partResizerWidget->maximumLastSector();
        firstSector -= delta;
        lastSector -= delta;
    }
    m_partResizerWidget->updateLastSector( lastSector );
    m_partResizerWidget->updateFirstSector( firstSector );

    // Update spinbox value in case it was an impossible value
    doUpdateSpinBox();
    m_updating = false;
}

void
PartitionSizeController::updateSpinBox()
{
    if ( m_updating )
        return;
    m_updating = true;
    doUpdateSpinBox();
    m_updating = false;
}

void
PartitionSizeController::doUpdateSpinBox()
{
    qint64 mbSize = ( m_partition->lastSector() - m_partition->firstSector() + 1 ) * m_device->logicalSectorSize() / 1024 / 1024;
    m_spinBox->setValue( mbSize );
}
