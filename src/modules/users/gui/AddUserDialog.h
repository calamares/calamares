/*
 * Copyright (c) 2008 - 2009  Dario Freddi <drf@chakra-project.org>
 *               2010 - 2011  Drake Justice <djustice@chakra-project.com>
 *                      2013  Manuel tortosa <manutortosa@chakra-project.org>
 *                      2016  Lisa Vitolo <shainer@chakralinux.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
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
     * - autologin: whether we should allow the autologin option.
     * - shells: the available login shells for users.
     */
    AddUserDialog(const QStringList &existingUsers, bool avatar, bool autologin, const QStringList &shells, bool haveRootPassword, QWidget *parent = 0);
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
