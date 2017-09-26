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


#ifndef BOOTINFOWIDGET_H
#define BOOTINFOWIDGET_H

#include <QWidget>

class QLabel;

class BootInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BootInfoWidget( QWidget* parent = nullptr );

public slots:
    void retranslateUi();

private:
    QLabel* m_bootIcon;
    QLabel* m_bootLabel;
};

#endif // BOOTINFOWIDGET_H
