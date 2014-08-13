/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "Typedefs.h"

#include <QWidget>

namespace Ui {
class Page_UserSetup;
}

class UsersPage : public QWidget
{
    Q_OBJECT
public:
    explicit UsersPage( QWidget* parent = nullptr );
    virtual ~UsersPage();

    bool isReady();

    QList< Calamares::job_ptr > createJobs();

protected slots:
    void onFullNameTextEdited( const QString& );
    void fillSuggestions();
    void onUsernameTextEdited( const QString& );
    void validateUsernameText( const QString& );
    void onHostnameTextEdited( const QString& );
    void validateHostnameText( const QString& );
    void onPasswordTextChanged( const QString& );
    void onRootPasswordTextChanged( const QString& );

signals:
    void checkReady( bool );

private:
    Ui::Page_UserSetup* ui;

    const QRegExp m_usernameRx = QRegExp( "^[a-z_][a-z0-9_-]*[$]?$" );
    const QRegExp m_hostnameRx = QRegExp( "^[a-zA-Z][-a-zA-Z0-9_]*$" );

    bool m_readyFullName;
    bool m_readyUsername;
    bool m_customUsername;
    bool m_readyHostname;
    bool m_customHostname;
    bool m_readyPassword;
    bool m_readyRootPassword;

};

#endif // USERSPAGE_H
