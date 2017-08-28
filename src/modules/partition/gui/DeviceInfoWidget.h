/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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


#ifndef DEVICEINFOWIDGET_H
#define DEVICEINFOWIDGET_H

#include <kpmcore/core/partitiontable.h>

#include <QWidget>

class QLabel;

class DeviceInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeviceInfoWidget( QWidget* parent = nullptr );

    void setPartitionTableType( PartitionTable::TableType type );

public slots:
    void retranslateUi();

private:
    QLabel* m_ptIcon;
    QLabel* m_ptLabel;
    PartitionTable::TableType m_tableType;
};

#endif // DEVICEINFOWIDGET_H
