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

#ifndef EDITEXISTINGPARTITIONDIALOG_H
#define EDITEXISTINGPARTITIONDIALOG_H

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
    EditExistingPartitionDialog( Device* device, Partition* partition, QWidget* parentWidget = nullptr );
    ~EditExistingPartitionDialog();

    void applyChanges( PartitionCoreModule* module );

private:
    QScopedPointer< Ui_EditExistingPartitionDialog > m_ui;
    Device* m_device;
    Partition* m_partition;
    PartitionSizeController* m_partitionSizeController;

    void replacePartResizerWidget();
};

#endif /* EDITEXISTINGPARTITIONDIALOG_H */
