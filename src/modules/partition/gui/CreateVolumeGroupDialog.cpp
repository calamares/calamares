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

CreateVolumeGroupDialog::CreateVolumeGroupDialog( QVector< const Partition* > pvList,
                                                  qint32 physicalExtentSize,
                                                  QWidget* parent )
    : VolumeGroupBaseDialog( parent, QString(), pvList )
{
    setWindowTitle( tr( "Create Volume Group" ) );

    peSizeWidget()->setValue( physicalExtentSize );
    vgTypeWidget()->setEnabled( false );
}
