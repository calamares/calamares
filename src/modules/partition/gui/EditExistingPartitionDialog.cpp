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

#include <gui/EditExistingPartitionDialog.h>

#include <core/ColorUtils.h>
#include <core/PartitionCoreModule.h>
#include <core/PartitionInfo.h>
#include <core/PMUtils.h>
#include <gui/PartitionSizeController.h>

#include <ui_EditExistingPartitionDialog.h>

#include <utils/Logger.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystemfactory.h>

// Qt
#include <QComboBox>

EditExistingPartitionDialog::EditExistingPartitionDialog( Device* device, Partition* partition, QWidget* parentWidget )
    : QDialog( parentWidget )
    , m_ui( new Ui_EditExistingPartitionDialog )
    , m_device( device )
    , m_partition( partition )
    , m_partitionSizeController( new PartitionSizeController( this ) )
{
    m_ui->setupUi( this );

    // Create a partition for partResizerWidget because it alters the first and
    // last sectors when used
    m_partResizerWidgetPartition.reset( PMUtils::clonePartition( m_device, m_partition ) );

    QColor color = ColorUtils::colorForPartition( m_partition );
    m_partitionSizeController->init( m_device, m_partResizerWidgetPartition.data(), color );
    m_partitionSizeController->setSpinBox( m_ui->sizeSpinBox );

    m_ui->mountPointComboBox->setCurrentText( PartitionInfo::mountPoint( partition ) );

    replacePartResizerWidget();

    connect( m_ui->formatRadioButton, &QAbstractButton::toggled, [ this ]( bool )
    {
        replacePartResizerWidget();
    } );
}

EditExistingPartitionDialog::~EditExistingPartitionDialog()
{}

void
EditExistingPartitionDialog::applyChanges( PartitionCoreModule* core )
{
    PartitionInfo::setMountPoint( m_partition, m_ui->mountPointComboBox->currentText() );

    qint64 newFirstSector = m_partResizerWidgetPartition->firstSector();
    qint64 newLastSector = m_partResizerWidgetPartition->lastSector();
    bool partitionChanged = newFirstSector != m_partition->firstSector() || newLastSector != m_partition->lastSector();

    if ( partitionChanged )
    {
        if ( m_ui->formatRadioButton->isChecked() )
        {
            Partition* newPartition = PMUtils::createNewPartition(
                                          m_partition->parent(),
                                          *m_device,
                                          m_partition->roles(),
                                          m_partition->fileSystem().type(),
                                          newFirstSector,
                                          newLastSector );
            PartitionInfo::setMountPoint( newPartition, PartitionInfo::mountPoint( m_partition ) );
            PartitionInfo::setFormat( newPartition, true );

            core->deletePartition( m_device, m_partition );
            core->createPartition( m_device, newPartition );
        }
        else
            core->resizePartition( m_device, m_partition, newFirstSector, newLastSector );
    }
    else
    {
        // No size changes
        if ( m_ui->formatRadioButton->isChecked() )
            core->formatPartition( m_device, m_partition );
        else
            core->refreshPartition( m_device, m_partition );
    }
}

void
EditExistingPartitionDialog::replacePartResizerWidget()
{
    /*
     * There is no way to reliably update the partition used by
     * PartResizerWidget, which is necessary when we switch between "format" and
     * "keep". This is a hack which replaces the existing PartResizerWidget
     * with a new one.
     */

    bool format = m_ui->formatRadioButton->isChecked();

    qint64 used = format ? 0 : m_partition->fileSystem().sectorsUsed();
    m_partResizerWidgetPartition->fileSystem().setSectorsUsed( used );

    qint64 minFirstSector = m_partition->firstSector() - m_device->partitionTable()->freeSectorsBefore( *m_partition );
    qint64 maxLastSector = m_partition->lastSector() + m_device->partitionTable()->freeSectorsAfter( *m_partition );

    PartResizerWidget* widget = new PartResizerWidget( this );
    widget->init( *m_device, *m_partResizerWidgetPartition, minFirstSector, maxLastSector );

    if ( !format )
    {
        // If we are not formatting, make sure the space between the first and
        // last sectors is big enough to fit the existing content.
        widget->updateLastSector( m_partResizerWidgetPartition->lastSector() );
        widget->updateFirstSector( m_partResizerWidgetPartition->firstSector() );
    }

    layout()->replaceWidget( m_ui->partResizerWidget, widget );
    delete m_ui->partResizerWidget;
    m_ui->partResizerWidget = widget;

    m_partitionSizeController->setPartResizerWidget( widget );
}
