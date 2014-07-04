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

#ifndef CREATEPARTITIONDIALOG_H
#define CREATEPARTITIONDIALOG_H

#include <QDialog>
#include <QScopedPointer>

// CalaPM
#include <core/partitionrole.h>

class Device;
class Partition;
class PartitionInfo;
class Ui_CreatePartitionDialog;

class CreatePartitionDialog : public QDialog
{
    Q_OBJECT
public:
    CreatePartitionDialog( Device* device, Partition* freePartition, QWidget* parent = nullptr );
    ~CreatePartitionDialog();

    PartitionInfo* createPartitionInfo();

private Q_SLOTS:
    void updateMountPointUi();

private:
    QScopedPointer< Ui_CreatePartitionDialog > m_ui;
    Device* m_device;
    Partition* m_freePartition;
    PartitionRole m_role = PartitionRole( PartitionRole::None );
};

#endif /* CREATEPARTITIONDIALOG_H */
