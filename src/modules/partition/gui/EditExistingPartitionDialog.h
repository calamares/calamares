/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef EDITEXISTINGPARTITIONDIALOG_H
#define EDITEXISTINGPARTITIONDIALOG_H

#include <kpmcore/core/partitiontable.h>

#include <QDialog>
#include <QScopedPointer>

class PartitionCoreModule;
class Device;
class Partition;
class PartitionSizeController;
class Ui_EditExistingPartitionDialog;

/**
 * The dialog which is shown to edit a partition which already existed when the installer started.
 *
 * It lets you decide how to reuse the partition: whether to keep its content
 * or reformat it, whether to resize or move it.
 */
class EditExistingPartitionDialog : public QDialog
{
    Q_OBJECT
public:
    struct FreeSpace
    {
        Partition* p;
    };

    EditExistingPartitionDialog( Device* device,
                                 Partition* partition,
                                 const QStringList& usedMountPoints,
                                 QWidget* parentWidget = nullptr );
    ~EditExistingPartitionDialog() override;

    void applyChanges( PartitionCoreModule* module );

private slots:
    void checkMountPointSelection();

private:
    QScopedPointer< Ui_EditExistingPartitionDialog > m_ui;
    Device* m_device;
    Partition* m_partition;
    PartitionSizeController* m_partitionSizeController;
    QStringList m_usedMountPoints;

    PartitionTable::Flags newFlags() const;
    void replacePartResizerWidget();
    void updateMountPointPicker();
    void toggleEncryptWidget();
};

#endif /* EDITEXISTINGPARTITIONDIALOG_H */
