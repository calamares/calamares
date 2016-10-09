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

#include "UsersPage.h"
#include "ui_page_usersetup.h"
#include "AddUserDialog.h"
#include <jobs/CreateUserJob.h>
#include <jobs/SetAvatarJob.h>
#include <jobs/SetPasswordJob.h>
#include <jobs/SetHostNameJob.h>
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <QBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QItemSelectionModel>
#include <QPointer>
#include <QRegExp>
#include <QRegExpValidator>

UsersListModel::~UsersListModel() {
    qDeleteAll(m_currentUsers);
}

int UsersListModel::rowCount(const QModelIndex &parent) const {
    return m_currentUsers.size();
}

int UsersListModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant UsersListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QVariant header;

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                header = QVariant(tr("User name"));
            break;

            case 1:
                header = QVariant(tr("Full name"));
            break;

            case 2:
                header = QVariant(tr("Shell"));
            break;

            case 3:
                header = QVariant(tr("Autologin?"));
            break;
        }
    }

    return header;
}

QVariant UsersListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        User* user = m_currentUsers.at( index.row() );
        QVariant data;

        switch (index.column()) {
            case 0:
                data = QVariant( user->toString() );
            break;

            case 1:
                data = QVariant( user->fullname );
            break;

            case 2:
                data = QVariant( user->shell );
            break;

            case 3:
                data = (user->autologin ? "yes" : "no");
        }

        return data;
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return QVariant();
}

Qt::ItemFlags UsersListModel::flags(const QModelIndex & /*index*/) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
}

void UsersListModel::addUser(User* user) {
    beginInsertRows( QModelIndex(), 0, 0);
    m_currentUsers.append(user);
    endInsertRows();
}

void UsersListModel::deleteUser(int index) {
    if (index < 0 || index >= m_currentUsers.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), 0, 0);
    m_currentUsers.removeAt(index);
    endRemoveRows();
}

QList<User *> UsersListModel::getUsers() const {
    return m_currentUsers;
}

UsersPage::UsersPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::UserCreation )
    , m_readyHostname( false )
    , m_readyRootPassword( false )
    , m_haveRootPassword( true )
{
    ui->setupUi( this );

    connect(ui->addUser, &QPushButton::clicked, this, &UsersPage::addUserClicked);
    connect(ui->deleteUser, &QPushButton::clicked, this, &UsersPage::deleteUserClicked);

    connect(ui->hostname, &QLineEdit::textChanged, this, &UsersPage::onHostnameTextEdited);

    if (m_haveRootPassword) {
        ui->rootPw->show();
        ui->confirmRootPw->show();
        ui->labelRootPw->show();
        ui->labelConfirmRootPw->show();

        connect(ui->rootPw, &QLineEdit::textChanged, this, &UsersPage::onRootPasswordTextChanged);
        connect(ui->confirmRootPw, &QLineEdit::textChanged, this, &UsersPage::onRootPasswordTextChanged);

    } else {
        ui->rootPw->hide();
        ui->confirmRootPw->hide();
        ui->labelRootPw->hide();
        ui->labelConfirmRootPw->hide();
    }

    // The columns will occupy all the space available in the view.
    ui->usersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // You can only select entire rows, not single cells, i.e. you
    // always select the user as a whole.
    ui->usersView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->usersView->setModel(&m_userModel);
    ui->usersView->show();
    CALAMARES_RETRANSLATE( ui->retranslateUi( this ); );
}

UsersPage::~UsersPage()
{
    delete ui;
}

void
UsersPage::addUserClicked() {
    QStringList existingUsers;
    bool userHasAutologin = false;

    for (const User* user : m_userModel.getUsers()) {
        existingUsers.append( user->username );

        if (user->autologin) {
            userHasAutologin = true;
        }
    }

    // Only allow autologin if the module configuration allows it,
    // and there exists no other users with autologin enabled.
    bool allowAutologin = m_autologin && !userHasAutologin;

    QPointer<AddUserDialog> dlg = new AddUserDialog(
                existingUsers, m_avatarFilePath.length() > 0, allowAutologin, m_availableShells, m_haveRootPassword, this );

    if ( dlg->exec() == QDialog::Accepted ) {
        addUser(dlg->login, dlg->name, dlg->password, dlg->shell, dlg->avatarFile, dlg->autoLogin);

        if (dlg->useUserPw && m_haveRootPassword) {
            ui->rootPw->setText(dlg->password);
            ui->confirmRootPw->setText(dlg->password);
        }
    }

    delete dlg;
}

void
UsersPage::deleteUserClicked() {
    QItemSelectionModel* selectionModel = ui->usersView->selectionModel();

    if (!selectionModel->hasSelection()) {
        return;
    }

    QModelIndex selectionIndex = selectionModel->currentIndex();
    if (!selectionIndex.isValid()) {
        return;
    }

    m_userModel.deleteUser(selectionIndex.row());
}

void
UsersPage::addUser(const QString &login, const QString &fullName, const QString &password, const QString &shell, const QString& avatarFile, bool autologin) {
    User* newUser = new User(login, fullName, password, shell, avatarFile, autologin);
    m_userModel.addUser(newUser);

    ui->hostname->setText( login + "-pc" );

    emit checkReady( isReady() );
}

bool
UsersPage::isReady()
{
    return (m_readyHostname &&
            // At least one user should have been created.
            m_userModel.getUsers().size() > 0 &&
            (!m_haveRootPassword || m_readyRootPassword));
}


QList< Calamares::job_ptr >
UsersPage::createJobs( const QStringList& defaultGroupsList )
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
        return list;

    for (const User* user : m_userModel.getUsers()) {

        Calamares::Job* j;
        j = new CreateUserJob( user->username,
                               (user->fullname.length() > 0) ? user->fullname : user->username,
                               user->shell,
                               user->autologin,
                               defaultGroupsList );

        list.append( Calamares::job_ptr( j ) );

        j = new SetPasswordJob( user->username, user->password );
        list.append( Calamares::job_ptr( j ) );

        j = new SetHostNameJob( ui->hostname->text() );
        list.append( Calamares::job_ptr( j ) );

        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        gs->insert( "hostname", ui->hostname->text() );

        // Given the validation we do, we assume this is always true
        // for at most one user in the page.
        if ( user->autologin )
            gs->insert( "autologinUser", user->username );

        if ( !user->avatarFile.length() > 0 ) {
            if (m_avatarFilePath.contains("~")) {
                    QString home( "/home/ " + user->username);
                    m_avatarFilePath.replace("~", home);
            }

            j = new SetAvatarJob( user->avatarFile, m_avatarFilePath );
            list.append( Calamares::job_ptr(j) );
        }
    }

    if ( m_haveRootPassword )
    {
        Calamares::Job* j = new SetPasswordJob( "root", ui->rootPw->text() );
        list.append( Calamares::job_ptr( j ) );
    }

    return list;
}


void
UsersPage::onActivate()
{
    emit checkReady( isReady() );

    // If there is no user yet, open the dialog as soon as the
    // page is enabled. This makes it easy for people who want
    // to create one user.
    if (m_userModel.rowCount() == 0) {
        addUserClicked();
    }
}

void
UsersPage::onHostnameTextEdited( const QString& textRef )
{
    validateHostnameText( textRef );
}

void
UsersPage::validateHostnameText( const QString& textRef )
{
    QString text = textRef;
    QRegExp rx( HOSTNAME_RX );
    QRegExpValidator val( rx );
    int pos = -1;

    if ( text.isEmpty() )
    {
        ui->labelHostnameError->clear();
        ui->labelHostname->clear();
        m_readyHostname= false;
    }
    else if ( text.length() < HOSTNAME_MIN_LENGTH )
    {
        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelHostname->size() ) );
        ui->labelHostnameError->setText(
            tr( "Your hostname is too short." ) );

        m_readyHostname = false;

    }
    else if ( text.length() > HOSTNAME_MAX_LENGTH )
    {
        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelHostname->size() ) );
        ui->labelHostnameError->setText(
            tr( "Your hostname is too long." ) );

        m_readyHostname = false;

    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelHostname->size() ) );
        ui->labelHostnameError->setText(
            tr( "Your hostname contains invalid characters. Only letters, numbers and dashes are allowed." ) );

        m_readyHostname = false;
    }
    else
    {
        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelHostname->size() ) );
        ui->labelHostnameError->clear();
        m_readyHostname = true;
    }

    emit checkReady( isReady() );
}

void
UsersPage::onRootPasswordTextChanged( const QString& textRef )
{
    QString pw1 = ui->rootPw->text();
    QString pw2 = ui->confirmRootPw->text();

    if ( pw1.isEmpty() && pw2.isEmpty() )
    {
        ui->labelRootPwError->clear();
        ui->labelRootPwIcon->clear();
        m_readyRootPassword = false;
    }
    else if ( pw1 != pw2 )
    {
        ui->labelRootPwError->setText( tr( "Your passwords do not match!" ) );
        ui->labelRootPwIcon->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                         CalamaresUtils::Original,
                                                                         ui->labelRootPwIcon->size() ) );
        m_readyRootPassword = false;
    }
    else
    {
        ui->labelRootPwError->clear();
        ui->labelRootPwIcon->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                         CalamaresUtils::Original,
                                                                         ui->labelRootPwIcon->size() ) );
        m_readyRootPassword = true;
    }

    emit checkReady( isReady() );
}

void UsersPage::setAutologin(bool autologin) {
    m_autologin = autologin;
}

void UsersPage::setHaveRootPassword(bool haveRootPassword) {
    m_haveRootPassword = haveRootPassword;
}

void UsersPage::setAvatarFilePath(const QString &path) {
    m_avatarFilePath = path;
}

void UsersPage::setAvailableShells(const QStringList &shells) {
    m_availableShells = shells;
}
