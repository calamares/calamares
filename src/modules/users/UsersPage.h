/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#ifndef USERSPAGE_H
#define USERSPAGE_H

#include <QWidget>

class Config;

class QLabel;

namespace Ui
{
class Page_UserSetup;
}

class UsersPage : public QWidget
{
    Q_OBJECT
public:
    explicit UsersPage( Config* config, QWidget* parent = nullptr );
    virtual ~UsersPage();

    void onActivate();

protected slots:
    void onFullNameTextEdited( const QString& );
    void reportLoginNameStatus( const QString& );
    void reportHostNameStatus( const QString& );
    void onReuseUserPasswordChanged( const int );
    void reportUserPasswordStatus( int, const QString& );
    void reportRootPasswordStatus( int, const QString& );

private:
    void retranslate();

    Ui::Page_UserSetup* ui;
    Config* m_config;
};

#endif  // USERSPAGE_H
