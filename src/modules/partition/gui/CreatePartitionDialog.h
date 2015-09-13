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
#include "PartitionPage.h"

class Device;
class Partition;
class PartitionNode;
class PartitionSizeController;
class Ui_CreatePartitionDialog;

/**
 * The dialog which is shown to create a new partition or to edit a
 * to-be-created partition.
 */
class CreatePartitionDialog : public QDialog
{
    Q_OBJECT
public:
    CreatePartitionDialog( Device* device, PartitionNode* parentPartition, QWidget* parentWidget = nullptr );
    ~CreatePartitionDialog();

    /**
     * Must be called when user wants to create a partition in
     * freeSpacePartition.
     */
    void initFromFreeSpace( Partition* freeSpacePartition );

    /**
     * Must be called when user wants to edit a to-be-created partition.
     */
    void initFromPartitionToCreate( Partition* partition );
    Partition* createPartition();
    virtual int exec();

private Q_SLOTS:
    void updateMountPointUi();

private:
    QScopedPointer< Ui_CreatePartitionDialog > m_ui;
    PartitionSizeController* m_partitionSizeController;
    Device* m_device;
    PartitionNode* m_parent;
    PartitionRole m_role = PartitionRole( PartitionRole::None );
    QList<QString> m_used_mountpoints;

    void initGptPartitionTypeUi();
    void initMbrPartitionTypeUi();
    void initPartResizerWidget( Partition* );
    bool validate();
};

#endif /* CREATEPARTITIONDIALOG_H */
