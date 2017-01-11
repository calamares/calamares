/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Lisa Vitolo <shainer@chakralinux.org>
 *
 *   Portions from Tribe (Chakra Linux)
 *   by Dario Freddi, Drake Justice and Manuel Tortosa
 *   Copyright (C) 2013 Free Software Foundation, Inc.
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

#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include "ui_adduserdialog.h"

#include <QLineEdit>
#include <QValidator>
#include <QRegExp>

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    /*
     * - existingUsers: username of the users that were already created.
     * This avoids us creating a second one with the same name.
     * - avatar: whether we should allow to choose an avatar.
     * - allowAutologin: whether we should allow the autologin option.
     * - checkAutologin: if allowAutologin is true, will it be checked by default or not? Ignored if false.
     * - shells: the available login shells for users.
     */
    AddUserDialog(const QStringList &existingUsers, bool avatar, bool allowAutologin, bool checkAutologin, const QStringList &shells, bool haveRootPassword, QWidget *parent = 0);
    virtual ~AddUserDialog();

    QString login;
    QString shell;
    QString password;
    QString avatarFile;
    QString fullName;

    bool autoLogin;
    bool useUserPw;

    void validateUsername(const QString&);

public slots:
    void accept() override;

signals:
    void addUserClicked();

private slots:
    void avatarClicked();
    void passwordChanged();
    void updateValidityUi();

private:
    Ui::AddUserDialog ui;

    QStringList m_existingUsers;
    QStringList m_badUsernames;
    bool m_validUsername;
    bool m_passwordsMatch;
    bool m_passwordsEmpty;

    const QRegExp USERNAME_RX = QRegExp( "^[a-z_][a-z0-9_-]*[$]?$" );
    const int USERNAME_MAX_LENGTH = 31;
};

#endif /* ADDUSERDIALOG_H */
