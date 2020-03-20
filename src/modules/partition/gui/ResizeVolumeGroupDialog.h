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

#ifndef RESIZEVOLUMEGROUPDIALOG_H
#define RESIZEVOLUMEGROUPDIALOG_H

#include "gui/VolumeGroupBaseDialog.h"

class LvmDevice;

class ResizeVolumeGroupDialog : public VolumeGroupBaseDialog
{
    Q_OBJECT
public:
    using PartitionVector = QVector< const Partition* >;

    ResizeVolumeGroupDialog( LvmDevice *device,
                             const PartitionVector& availablePVs,
                             PartitionVector& selectedPVs,
                             QWidget* parent );

    void accept() override;

private:
    PartitionVector& m_selectedPVs;
};

#endif // RESIZEVOLUMEGROUPDIALOG_H
