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

private:
    /** @brief Delegated constructor
     *
     * This does all the shared UI setup.
     */
    CreatePartitionDialog( Device* device,
                           PartitionNode* parentPartition,
                           const QStringList& usedMountPoints,
                           QWidget* parentWidget );

public:
    struct FreeSpace
    {
        Partition* p;
    };
    struct FreshPartition
    {
        Partition* p;
    };

    /** @brief Dialog for editing a new partition based on free space.
     *
     * Creating from free space makes a wholly new partition with
     * no flags set at all.
     */
    CreatePartitionDialog( Device* device,
                           const FreeSpace& freeSpacePartition,
                           const QStringList& usedMountPoints,
                           QWidget* parentWidget = nullptr );
    /** @brief Dialog for editing a newly-created partition.
     *
     * A partition previously newly created (e.g. via this dialog
     * and the constructor above) can be re-edited.
     */
    CreatePartitionDialog( Device* device,
                           const FreshPartition& existingNewPartition,
                           const QStringList& usedMountPoints,
                           QWidget* parentWidget = nullptr );
    ~CreatePartitionDialog() override;

    Partition* getNewlyCreatedPartition();

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
