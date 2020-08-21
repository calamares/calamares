/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
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

#ifndef RESIZEVOLUMEGROUPDIALOG_H
#define RESIZEVOLUMEGROUPDIALOG_H

#include "gui/VolumeGroupBaseDialog.h"

class LvmDevice;

class ResizeVolumeGroupDialog : public VolumeGroupBaseDialog
{
    Q_OBJECT
public:
    using PartitionVector = QVector< const Partition* >;

    ResizeVolumeGroupDialog( LvmDevice* device,
                             const PartitionVector& availablePVs,
                             PartitionVector& selectedPVs,
                             QWidget* parent );

    void accept() override;

private:
    PartitionVector& m_selectedPVs;
};

#endif  // RESIZEVOLUMEGROUPDIALOG_H
