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

#include "CheckPWQuality.h"
#include "Job.h"

#include <QWidget>

class QLabel;

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

    Calamares::JobList createJobs( const QStringList& defaultGroupsList );

    void onActivate();

    void setWriteRootPassword( bool show );
    void setPasswordCheckboxVisible( bool visible );
    void setValidatePasswordDefault( bool checked );
    void setAutologinDefault( bool checked );
    void setReusePasswordDefault( bool checked );

    /** @brief Process entries in the passwordRequirements config entry
     *
     * Called once for each item in the config entry, which should
     * be a key-value pair. What makes sense as a value depends on
     * the key. Supported keys are documented in users.conf.
     */
    void addPasswordCheck( const QString& key, const QVariant& value );

    ///@brief Hostname as entered / auto-filled
    QString getHostname() const;
    ///@brief Root password, depends on settings, may be empty
    QString getRootPassword() const;
    ///@brief User name and password
    QPair< QString, QString > getUserPassword() const;

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
    /** @brief Is the password acceptable?
     *
     * Checks the two copies of the password and places error messages in the
     * given QLabels. Returns true (and clears the error messages) if the
     * password is acceptable.
     */
    bool checkPasswordAcceptance( const QString& pw1, const QString& pw2, QLabel* badge, QLabel* message );

    void retranslate();

    Ui::Page_UserSetup* ui;

    PasswordCheckList m_passwordChecks;
    bool m_passwordChecksChanged = false;

    bool m_readyFullName;
    bool m_readyUsername;
    bool m_customUsername;
    bool m_readyHostname;
    bool m_customHostname;
    bool m_readyPassword;
    bool m_readyRootPassword;

    bool m_writeRootPassword;
};

#endif  // USERSPAGE_H
