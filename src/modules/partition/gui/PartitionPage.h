/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef PARTITIONPAGE_H
#define PARTITIONPAGE_H

#include <QWidget>
#include <QScopedPointer>
#include <QMutex>

class PartitionCoreModule;
class Ui_PartitionPage;

class Device;
class DeviceModel;
class Partition;

/**
 * The user interface for the module.
 *
 * Shows the information exposed by PartitionCoreModule and asks it to schedule
 * jobs according to user actions.
 */
class PartitionPage : public QWidget
{
    Q_OBJECT
public:
    explicit PartitionPage( PartitionCoreModule* core, QWidget* parent = nullptr );
    ~PartitionPage();

    void onRevertClicked();

private:
    QScopedPointer< Ui_PartitionPage > m_ui;
    PartitionCoreModule* m_core;
    void updateButtons();
    void onNewPartitionTableClicked();
    void onCreateClicked();
    void onEditClicked();
    void onDeleteClicked();
    void onPartitionViewActivated();
    void onPartitionModelReset();

    void updatePartitionToCreate( Device*, Partition* );
    void editExistingPartition( Device*, Partition* );
    void updateBootLoaderInstallPath();
    void updateFromCurrentDevice();
    void updateBootLoaderIndex();

    QStringList getCurrentUsedMountpoints();

    QMutex m_revertMutex;
    int    m_lastSelectedBootLoaderIndex;
    bool   m_isEfi;
};

#endif // PARTITIONPAGE_H
