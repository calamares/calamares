/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include <functional>

namespace Ui
{
class Page_UserSetup;
}

class UsersPage : public QWidget
{
    Q_OBJECT
public:
    explicit UsersPage( QWidget* parent = nullptr );
    virtual ~UsersPage();

    bool isReady();

    QList< Calamares::job_ptr > createJobs( const QStringList& defaultGroupsList );

    void onActivate();

    void setWriteRootPassword( bool show );
    void setAutologinDefault( bool checked );
    void setReusePasswordDefault( bool checked );

    void addPasswordCheck( const QString& key, const QVariant& value );

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

    /**
     * Support for (dynamic) checks on the password's validity.
     * This can be used to implement password requirements like
     * "at least 6 characters". Function addPasswordCheck()
     * instantiates these and adds them to the list of checks.
     */
    class PasswordCheck
    {
    public:
        /** Return true if the string is acceptable. */
        using AcceptFunc = std::function<bool( const QString& )>;
        using MessageFunc = std::function<QString()>;

        /** Generate a @p message if @p filter returns true */
        PasswordCheck( MessageFunc message, AcceptFunc filter );
        /** Yields @p message if @p filter returns true */
        PasswordCheck( const QString& message, AcceptFunc filter );
        /** Null check, always returns empty */
        PasswordCheck();

        /** Applies this check to the given password string @p s
         *  and returns an empty string if the password is ok
         *  according to this filter. Returns a message describing
         *  what is wrong if not.
         */
        QString filter( const QString& s ) const
        {
            return m_accept( s ) ? QString() : m_message();
        }

    private:
        MessageFunc m_message;
        AcceptFunc m_accept;
    } ;
    QVector<PasswordCheck> m_passwordChecks;

    const QRegExp USERNAME_RX = QRegExp( "^[a-z_][a-z0-9_-]*[$]?$" );
    const QRegExp HOSTNAME_RX = QRegExp( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
    const int USERNAME_MAX_LENGTH = 31;
    const int HOSTNAME_MIN_LENGTH = 2;
    const int HOSTNAME_MAX_LENGTH = 63;

    bool m_readyFullName;
    bool m_readyUsername;
    bool m_customUsername;
    bool m_readyHostname;
    bool m_customHostname;
    bool m_readyPassword;
    bool m_readyRootPassword;

    bool m_writeRootPassword;
};

#endif // USERSPAGE_H
