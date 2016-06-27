/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
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

#ifndef GROUPSELECTIONWIDGET_H
#define GROUPSELECTIONWIDGET_H

#include "ui_groupselectionwidget.h"

#include <QSignalMapper>
#include <QWidget>

// Represents a widget to display and select a group.
class GroupSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroupSelectionWidget( QString name, QString description, QStringList packages, QWidget* parent = 0 );

    // Current status of the group: is it selected in the view?
    bool isToggled() const;

signals:
    void toggled( bool );

public slots:
    void toggleGroup( bool isToggled );

private:
    Ui::GroupSelectionWidget ui;
    static QSignalMapper* m_mapper;

    bool m_isToggled;
};

#endif // GROUPSELECTIONWIDGET_H
