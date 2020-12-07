/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CREATEVOLUMEGROUPDIALOG_H
#define CREATEVOLUMEGROUPDIALOG_H

#include "gui/VolumeGroupBaseDialog.h"

class CreateVolumeGroupDialog : public VolumeGroupBaseDialog
{
    Q_OBJECT
public:
    CreateVolumeGroupDialog( QString& vgName,
                             QVector< const Partition* >& selectedPVs,
                             QVector< const Partition* > pvList,
                             qint64& pSize,
                             QWidget* parent );

    void accept() override;

private:
    QVector< const Partition* >& m_selectedPVs;

    qint64& m_peSize;
};

#endif  // CREATEVOLUMEGROUPDIALOG_H
