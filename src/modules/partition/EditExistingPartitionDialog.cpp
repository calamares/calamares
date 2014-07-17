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

#include <PartitionInfo.h>
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

    PartitionTable* table = m_device->partitionTable();
    qint64 minSector = partition->firstSector() - table->freeSectorsBefore( *partition );
    qint64 maxSector = partition->lastSector() + table->freeSectorsAfter( *partition );

    m_ui->sizeSpinBox->setMaximum( mbSizeForSectorRange( minSector, maxSector ) );
    m_ui->sizeSpinBox->setValue( mbSizeForSectorRange( partition->firstSector(), partition->lastSector() ) );

    // Mount point
    m_ui->mountPointComboBox->setCurrentText( PartitionInfo::mountPoint( partition ) );
}

EditExistingPartitionDialog::~EditExistingPartitionDialog()
{}

qint64
EditExistingPartitionDialog::mbSizeForSectorRange( qint64 first, qint64 last ) const
{
    return ( last - first + 1 ) * m_device->logicalSectorSize() / 1024 / 1024;
}

void
EditExistingPartitionDialog::applyChanges( PartitionCoreModule* module )
{
    PartitionInfo::setMountPoint( m_partition, m_ui->mountPointComboBox->currentText() );
}
