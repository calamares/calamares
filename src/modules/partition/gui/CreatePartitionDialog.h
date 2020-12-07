/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CREATEPARTITIONDIALOG_H
#define CREATEPARTITIONDIALOG_H

// KPMcore
#include <kpmcore/core/partitionrole.h>
#include <kpmcore/core/partitiontable.h>

#include <QDialog>
#include <QScopedPointer>


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
    /**
     * @brief Dialog for editing a new partition.
     *
     * For the (unlikely) case that a newly created partition is being re-edited,
     * pass a pointer to that @p partition, otherwise pass nullptr.
     */
    CreatePartitionDialog( Device* device,
                           PartitionNode* parentPartition,
                           Partition* partition,
                           const QStringList& usedMountPoints,
                           QWidget* parentWidget = nullptr );
    ~CreatePartitionDialog() override;

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

    PartitionTable::Flags newFlags() const;

private Q_SLOTS:
    void updateMountPointUi();
    void checkMountPointSelection();

private:
    QScopedPointer< Ui_CreatePartitionDialog > m_ui;
    PartitionSizeController* m_partitionSizeController;
    Device* m_device;
    PartitionNode* m_parent;
    PartitionRole m_role = PartitionRole( PartitionRole::None );
    QStringList m_usedMountPoints;

    void initGptPartitionTypeUi();
    void initMbrPartitionTypeUi();
    void initPartResizerWidget( Partition* );
};

#endif /* CREATEPARTITIONDIALOG_H */
