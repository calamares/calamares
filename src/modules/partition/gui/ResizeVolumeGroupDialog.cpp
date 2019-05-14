/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "ResizeVolumeGroupDialog.h"

#include "gui/ListPhysicalVolumeWidgetItem.h"

#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/util/capacity.h>

#include <QComboBox>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QSpinBox>

ResizeVolumeGroupDialog::ResizeVolumeGroupDialog( LvmDevice *device,
                                                  const PartitionVector& availablePVs,
                                                  PartitionVector& selectedPVs,
                                                  QWidget* parent )
    : VolumeGroupBaseDialog( device->name(), device->physicalVolumes(), parent )
    , m_selectedPVs( selectedPVs )
{
    setWindowTitle( tr( "Resize Volume Group" ) );

    for ( int i = 0; i < pvList()->count(); i++ )
        pvList()->item(i)->setCheckState( Qt::Checked );

    for ( const Partition* p : availablePVs )
        pvList()->addItem( new ListPhysicalVolumeWidgetItem( p, false ) );

    peSize()->setValue( static_cast<int>( device->peSize() / Capacity::unitFactor(Capacity::Unit::Byte, Capacity::Unit::MiB) ) );

    vgName()->setEnabled( false );
    peSize()->setEnabled( false );
    vgType()->setEnabled( false );

    setUsedSizeValue( device->allocatedPE() * device->peSize() );
    setLVQuantity( device->partitionTable()->children().count() );
}

void
ResizeVolumeGroupDialog::accept()
{
    m_selectedPVs << checkedItems();

    QDialog::accept();
}
