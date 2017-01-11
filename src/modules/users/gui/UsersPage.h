/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include <QAbstractListModel>
#include <QtGlobal>
#include <QItemSelection>
#include <QVariant>
#include <QWidget>

namespace Ui {
class UserCreation;
}

/*
 * Represents the properties of a user in the system.
 *
 * The fullname and avatar file can be empty and they will be ignored.
 * The password can technically be empty too, but that is of course
 * not recommended in general.
 */
struct User {
    User(const QString& username, const QString& fullname, const QString& password, const QString& shell, const QString& avatarFile, bool autologin)
        : username(username), fullname(fullname), password(password), shell(shell), avatarFile(avatarFile), autologin(autologin) {}

    QString toString() const {
        return username;
    }

    QString username;
    QString fullname;
    QString password;
    QString shell;
    QString avatarFile;
    bool autologin;
};

/*
 * Model to contain the users created during the installation
 * process. This is associated to a QTableView in the main UI.
 *
 * Each row is a user and each column a property of the user.
 */
class UsersListModel : public QAbstractTableModel {
    Q_OBJECT

public:
    virtual ~UsersListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex & /*index*/) const Q_DECL_OVERRIDE;

    void addUser(User *user);
    void deleteUser(int index);
    QList<User *> getUsers() const;

private:
    QList<User *> m_currentUsers;
};

class UsersPage : public QWidget
{
    Q_OBJECT

public:
    explicit UsersPage( QWidget* parent = nullptr );
    virtual ~UsersPage();

    bool isReady();

    QList< Calamares::job_ptr > createJobs( const QStringList& defaultGroupsList );

    void onActivate();

    // Setters for properties of this page, usually from configuration.
    void setAutologin( bool autologin );
    void setAvatarFilePath( const QString& path );
    void setAvailableShells( const QStringList& shells);
    void setHaveRootPassword(bool);

protected slots:
    void onHostnameTextEdited( const QString& );
    void validateHostnameText( const QString& );
    void onRootPasswordTextChanged( const QString& );

    void addUserClicked();
    void deleteUserClicked();

signals:
    void checkReady( bool );

private:
    void addUser(const QString& login, const QString& fullName, const QString& password, const QString& shell, const QString& avatarFile, bool autologin);

    Ui::UserCreation* ui;
    UsersListModel m_userModel;

    // Hostname validation.
    const QRegExp HOSTNAME_RX = QRegExp( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
    const int HOSTNAME_MIN_LENGTH = 2;
    const int HOSTNAME_MAX_LENGTH = 24;

    // Are the following fields valid with their current value?
    bool m_readyHostname;
    bool m_readyRootPassword;

    // Check autologin by default (if no other user is already in autologin mode)?
    bool m_autologin;
    // Allow to set a root password?
    bool m_haveRootPassword;
    // Path to copy the avatar file to, if the user selects one.
    QString m_avatarFilePath;
    // List of available shells for new users.
    QStringList m_availableShells;
};

#endif // USERSPAGE_H
