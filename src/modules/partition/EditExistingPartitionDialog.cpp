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

#include <EditExistingPartitionDialog.h>

#include <PartitionCoreModule.h>
#include <PartitionInfo.h>
#include <PMUtils.h>
#include <ui_EditExistingPartitionDialog.h>
#include <utils/Logger.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>

// Qt
#include <QComboBox>

EditExistingPartitionDialog::EditExistingPartitionDialog( Device* device, Partition* partition, QWidget* parentWidget )
    : QDialog( parentWidget )
    , m_ui( new Ui_EditExistingPartitionDialog )
    , m_device( device )
    , m_partition( partition )
{
    m_ui->setupUi( this );
    m_ui->sizeSpinBox->init( device, partition );
    m_ui->mountPointComboBox->setCurrentText( PartitionInfo::mountPoint( partition ) );
}

EditExistingPartitionDialog::~EditExistingPartitionDialog()
{}

void
EditExistingPartitionDialog::applyChanges( PartitionCoreModule* core )
{
    PartitionInfo::setMountPoint( m_partition, m_ui->mountPointComboBox->currentText() );

    if ( m_ui->sizeSpinBox->isDirty() )
    {
        PartitionSizeWidget::SectorRange range = m_ui->sizeSpinBox->sectorRange();
        if ( m_ui->formatRadioButton->isChecked() )
        {
            Partition* newPartition = PMUtils::createNewPartition(
                                          m_partition->parent(),
                                          *m_device,
                                          m_partition->roles(),
                                          m_partition->fileSystem().type(),
                                          range.first,
                                          range.second );
            PartitionInfo::setMountPoint( newPartition, PartitionInfo::mountPoint( m_partition ) );
            PartitionInfo::setFormat( newPartition, true );

            core->deletePartition( m_device, m_partition );
            core->createPartition( m_device, newPartition );
        }
        else
        {
            //core->resizePartition( m_device, m_partition );
        }
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
