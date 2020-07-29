/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
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

#ifndef USERS_CONFIG_H
#define USERS_CONFIG_H

#include <QObject>
#include <QVariantMap>

class Config : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString userShell READ userShell WRITE setUserShell NOTIFY userShellChanged )

    Q_PROPERTY( QString autologinGroup READ autologinGroup WRITE setAutologinGroup NOTIFY autologinGroupChanged )
    Q_PROPERTY( QString sudoersGroup READ sudoersGroup WRITE setSudoersGroup NOTIFY sudoersGroupChanged )

    Q_PROPERTY( bool doAutoLogin READ doAutoLogin WRITE setAutoLogin NOTIFY autoLoginChanged )

    Q_PROPERTY( QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged )
    Q_PROPERTY( QString loginName READ loginName WRITE setLoginName NOTIFY loginNameChanged )
    Q_PROPERTY( QString loginNameStatus READ loginNameStatus NOTIFY loginNameStatusChanged )

    Q_PROPERTY( QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged )
    Q_PROPERTY( QString hostNameStatus READ hostNameStatus NOTIFY hostNameStatusChanged )

public:
    Config( QObject* parent = nullptr );
    ~Config();

    void setConfigurationMap( const QVariantMap& );

    /** @brief Full path to the user's shell executable
     *
     * Typically this will be /bin/bash, but it can be set from
     * the config file with the *userShell* setting.
     */
    QString userShell() const { return m_userShell; }

    /// The group of which auto-login users must be a member
    QString autologinGroup() const { return m_autologinGroup; }
    /// The group of which users who can "sudo" must be a member
    QString sudoersGroup() const { return m_sudoersGroup; }

    /// The full (GECOS) name of the user
    QString fullName() const { return m_fullName; }
    /// The login name of the user
    QString loginName() const { return m_loginName; }
    /// Status message about login -- empty for "ok"
    QString loginNameStatus() const;

    /// The host name (name for the system)
    QString hostName() const { return m_hostName; }
    /// Status message about hostname -- empty for "ok"
    QString hostNameStatus() const;

    /// Should the user be automatically logged-in?
    bool doAutoLogin() const { return m_doAutoLogin; }
    /// Should the root password be written (if false, no password is set and the root account is disabled for login)
    bool writeRootPassword() const { return m_writeRootPassword; }

    const QStringList& defaultGroups() const { return m_defaultGroups; }

    static const QStringList& forbiddenLoginNames();
    static const QStringList& forbiddenHostNames();

public Q_SLOTS:
    /** @brief Sets the user's shell if possible
     *
     * If the path is empty, that's ok: no shell will be explicitly set,
     * so the user will get whatever shell is set to default in the target.
     *
     * The given non-empty @p path must be an absolute path (for use inside
     * the target system!); if it is not, the shell is not changed.
     */
    void setUserShell( const QString& path );

    /// Sets the autologin group; empty is ignored
    void setAutologinGroup( const QString& group );
    /// Sets the sudoer group; empty is ignored
    void setSudoersGroup( const QString& group );

    /// Sets the full name, may guess a loginName
    void setFullName( const QString& name );
    /// Sets the login name (flags it as "custom")
    void setLoginName( const QString& login );

    /// Sets the host name (flags it as "custom")
    void setHostName( const QString& host );

    /// Sets the autologin flag
    void setAutoLogin( bool b );

signals:
    void userShellChanged( const QString& );
    void autologinGroupChanged( const QString& );
    void sudoersGroupChanged( const QString& );
    void fullNameChanged( const QString& );
    void loginNameChanged( const QString& );
    void loginNameStatusChanged( const QString& );
    void hostNameChanged( const QString& );
    void hostNameStatusChanged( const QString& );
    void autoLoginChanged( bool );

private:
    QStringList m_defaultGroups;
    QString m_userShell;
    QString m_autologinGroup;
    QString m_sudoersGroup;
    QString m_fullName;
    QString m_loginName;
    QString m_hostName;
    bool m_doAutoLogin = false;
    bool m_writeRootPassword = true;

    bool m_customLoginName = false;
    bool m_customHostName = false;
};

#endif
