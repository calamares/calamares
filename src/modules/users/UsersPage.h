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
#include <QItemSelection>
#include <QVariant>
#include <QWidget>

namespace Ui {
class UserCreation;
}

struct User {
    User(const QString& username, const QString& fullname, const QString& password, const QString& shell, bool autologin)
        : username(username), fullname(fullname), password(password), shell(shell), autologin(autologin) {}

    QString toString() const {
        return username;
    }

    QString username;
    QString fullname;
    QString password;
    QString shell;
    bool autologin;
};

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
    void addUser(const QString& login, const QString& fullName, const QString& password, const QString& shell, bool autologin);

    Ui::UserCreation* ui;
    UsersListModel m_userModel;

    const QRegExp HOSTNAME_RX = QRegExp( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
    const int HOSTNAME_MIN_LENGTH = 2;
    const int HOSTNAME_MAX_LENGTH = 24;

    bool m_readyHostname;
    bool m_customHostname;
    bool m_readyRootPassword;

    bool m_haveRootPassword;
    QStringList m_availableShells;
};

#endif // USERSPAGE_H
