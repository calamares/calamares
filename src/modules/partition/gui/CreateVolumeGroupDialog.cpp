/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CreateVolumeGroupDialog.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/lvmdevice.h>

#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>

CreateVolumeGroupDialog::CreateVolumeGroupDialog( QString& vgName,
                                                  QVector< const Partition* >& selectedPVs,
                                                  QVector< const Partition* > pvList,
                                                  qint64& pSize,
                                                  QWidget* parent )
    : VolumeGroupBaseDialog( vgName, pvList, parent )
    , m_selectedPVs( selectedPVs )
    , m_peSize( pSize )
{
    setWindowTitle( tr( "Create Volume Group" ) );

    peSize()->setValue( pSize );

    vgType()->setEnabled( false );
}

void
CreateVolumeGroupDialog::accept()
{
    QString& name = vgNameValue();
    name = vgName()->text();

    m_selectedPVs << checkedItems();

    qint64& pe = m_peSize;
    pe = peSize()->value();

    QDialog::accept();
}
