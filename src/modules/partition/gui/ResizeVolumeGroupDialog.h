/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef RESIZEVOLUMEGROUPDIALOG_H
#define RESIZEVOLUMEGROUPDIALOG_H

#include "gui/VolumeGroupBaseDialog.h"

class LvmDevice;

class ResizeVolumeGroupDialog : public VolumeGroupBaseDialog
{
    Q_OBJECT
public:
    ResizeVolumeGroupDialog( LvmDevice* device, const PartitionVector& availablePVs, QWidget* parent );
};

#endif  // RESIZEVOLUMEGROUPDIALOG_H
