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
class Ui_CreatePartitionDialog;

class CreatePartitionDialog : public QDialog
{
    Q_OBJECT
public:
    CreatePartitionDialog( Device* device, PartitionNode* parentPartition, QWidget* parentWidget = nullptr );
    ~CreatePartitionDialog();

    void initFromFreeSpace( Partition* partition );
    void initFromPartitionToCreate( Partition* partition );
    Partition* createPartition();
    virtual int exec();

private Q_SLOTS:
    void updateMountPointUi();

private:
    QScopedPointer< Ui_CreatePartitionDialog > m_ui;
    Device* m_device;
    qint64 m_minSector = 0;
    qint64 m_maxSector = 0;
    QList<QString> m_used_mountpoints;
    PartitionNode* m_parent;
    PartitionRole m_role = PartitionRole( PartitionRole::None );

    void initSectorRange( Partition* );

    qint64 mbSizeForSectorRange( qint64 first, qint64 last ) const;

    bool validate();
};

#endif /* CREATEPARTITIONDIALOG_H */
