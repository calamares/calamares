/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~UsersPage() override;

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
