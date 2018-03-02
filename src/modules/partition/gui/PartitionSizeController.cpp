/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "gui/PartitionSizeController.h"

#include "core/ColorUtils.h"
#include "core/KPMHelpers.h"

#include "utils/Units.h"

// Qt
#include <QSpinBox>

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/gui/partresizerwidget.h>

// stdc++
#include <limits>

PartitionSizeController::PartitionSizeController( QObject* parent )
    : QObject( parent )
{}

void
PartitionSizeController::init( Device* device, Partition* partition, const QColor& color )
{
    m_device = device;
    m_originalPartition = partition;
    // PartResizerWidget stores its changes directly in the partition it is
    // initialized with. We don't want the changes to be committed that way,
    // because it means we would have to revert them if the user cancel the
    // dialog the widget is in. Therefore we init PartResizerWidget with a clone
    // of the original partition.
    m_partition.reset( KPMHelpers::clonePartition( m_device, partition ) );
    m_partitionColor = color;
}

void
PartitionSizeController::setPartResizerWidget( PartResizerWidget* widget, bool format )
{
    Q_ASSERT( m_device );

    if ( m_partResizerWidget )
        disconnect( m_partResizerWidget, nullptr, this, nullptr );

    m_dirty = false;
    m_currentSpinBoxValue = -1;

    // Update partition filesystem. This must be done *before* the call to
    // PartResizerWidget::init() otherwise it will be ignored by the widget.
    // This is why this method accept a `format` boolean.
    qint64 used = format ? 0 : m_originalPartition->fileSystem().sectorsUsed();
    m_partition->fileSystem().setSectorsUsed( used );

    // Init PartResizerWidget
    m_partResizerWidget = widget;
    PartitionTable* table = m_device->partitionTable();
    qint64 minFirstSector = m_originalPartition->firstSector() - table->freeSectorsBefore( *m_originalPartition );
    qint64 maxLastSector = m_originalPartition->lastSector() + table->freeSectorsAfter( *m_originalPartition );
    m_partResizerWidget->init( *m_device, *m_partition.data(), minFirstSector, maxLastSector );

    // FIXME: Should be set by PartResizerWidget itself
    m_partResizerWidget->setFixedHeight( PartResizerWidget::handleHeight() );

    QPalette pal = widget->palette();
    pal.setColor( QPalette::Base, ColorUtils::freeSpaceColor() );
    pal.setColor( QPalette::Button, m_partitionColor );
    m_partResizerWidget->setPalette( pal );
    connectWidgets();

    if ( !format )
    {
        // If we are not formatting, update the widget to make sure the space
        // between the first and last sectors is big enough to fit the existing
        // content.
        m_updating = true;

        qint64 firstSector = m_partition->firstSector();
        qint64 lastSector = m_partition->lastSector();

        // This first time we call doAAUPRW with real first/last sector,
        // all further calls will come from updatePartResizerWidget, and
        // will therefore use values calculated from the SpinBox.
        doAlignAndUpdatePartResizerWidget( firstSector, lastSector );

        m_updating = false;
    }
}

void
PartitionSizeController::setSpinBox( QSpinBox* spinBox )
{
    if ( m_spinBox )
        disconnect( m_spinBox, nullptr, this, nullptr );
    m_spinBox = spinBox;
    m_spinBox->setMaximum( std::numeric_limits< int >::max() );
    connectWidgets();
}

void
PartitionSizeController::connectWidgets()
{
    if ( !m_spinBox || !m_partResizerWidget )
        return;

    connect( m_spinBox, SIGNAL( editingFinished() ), SLOT( updatePartResizerWidget() ) );
    connect( m_partResizerWidget, SIGNAL( firstSectorChanged( qint64 ) ), SLOT( updateSpinBox() ) );
    connect( m_partResizerWidget, SIGNAL( lastSectorChanged( qint64 ) ), SLOT( updateSpinBox() ) );

    // Init m_spinBox from m_partResizerWidget
    updateSpinBox();
}

void
PartitionSizeController::updatePartResizerWidget()
{
    if ( m_updating )
        return;
    if ( m_spinBox->value() == m_currentSpinBoxValue )
        return;

    m_updating = true;
    qint64 sectorSize = qint64( m_spinBox->value() ) * 1024 * 1024 / m_device->logicalSize();

    qint64 firstSector = m_partition->firstSector();
    qint64 lastSector = firstSector + sectorSize - 1;

    doAlignAndUpdatePartResizerWidget( firstSector, lastSector );

    m_updating = false;
}

void
PartitionSizeController::doAlignAndUpdatePartResizerWidget( qint64 firstSector,
                                                            qint64 lastSector )
{
    if ( lastSector > m_partResizerWidget->maximumLastSector() )
    {
        qint64 delta = lastSector - m_partResizerWidget->maximumLastSector();
        firstSector -= delta;
        lastSector -= delta;
    }
    if ( lastSector != m_partition->lastSector() )
    {
        m_partResizerWidget->updateLastSector( lastSector );
        m_dirty = true;
    }
    if ( firstSector != m_partition->firstSector() )
    {
        m_partResizerWidget->updateFirstSector( firstSector );
        m_dirty = true;
    }

    // Update spinbox value in case it was an impossible value
    doUpdateSpinBox();
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
    if ( !m_spinBox )
        return;
    int mbSize = CalamaresUtils::BytesToMiB( m_partition->length() * m_device->logicalSize() );
    m_spinBox->setValue( mbSize );
    if ( m_currentSpinBoxValue != -1 &&    //if it's not the first time we're setting it
         m_currentSpinBoxValue != mbSize ) //and the operation changes the SB value
        m_dirty = true;
    m_currentSpinBoxValue = mbSize;
}

qint64
PartitionSizeController::firstSector() const
{
    return m_partition->firstSector();
}

qint64
PartitionSizeController::lastSector() const
{
    return m_partition->lastSector();
}

bool
PartitionSizeController::isDirty() const
{
    return m_dirty;
}
