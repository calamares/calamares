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
#include "ui_usercreation.h"
#include "AddUserDialog.h"
#include "CreateUserJob.h"
#include "SetPasswordJob.h"
#include "SetHostNameJob.h"
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
    , m_readyFullName( false )
    , m_readyUsername( false )
    , m_readyHostname( false )
    , m_readyPassword( false )
    , m_readyRootPassword( false )
    , m_writeRootPassword( true )
{
    ui->setupUi( this );

    connect(ui->addUser, SIGNAL(clicked(bool)), this, SLOT(addUserClicked()));
    connect(ui->deleteUser, SIGNAL(clicked(bool)), this, SLOT(deleteUserClicked()));

    connect(ui->hostname, &QLineEdit::textChanged, this, &UsersPage::onHostnameTextEdited);

    if (m_haveRootPassword) {
        ui->rootPw->show();
        ui->confirmRootPw->show();
        ui->labelRootPw->show();
        ui->labelConfirmRootPw->show();
    } else {
        ui->rootPw->hide();
        ui->confirmRootPw->hide();
        ui->labelRootPw->hide();
        ui->labelConfirmRootPw->hide();
    }

    // TODO: remove
    addUser("prova", "Full Name", "test", "/bin/bash", false);

    ui->usersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    for (const User* user : m_userModel.getUsers()) {
        existingUsers.append( user->username );
    }

    QPointer<AddUserDialog> dlg = new AddUserDialog( existingUsers, m_availableShells, m_haveRootPassword, this );

    if ( dlg->exec() == QDialog::Accepted ) {
        // TODO: put groups and avatar.
        addUser(dlg->login, dlg->name, dlg->password, dlg->shell, dlg->autoLogin);

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
UsersPage::addUser(const QString &login, const QString &fullName, const QString &password, const QString &shell, bool autologin) {
    User* newUser = new User(login, fullName, shell, password, autologin);
    m_userModel.addUser(newUser);

    ui->hostname->setText( login + "-pc" );
}

bool
UsersPage::isReady()
{
    // TODO: look at hostname, readyRootPassword, and at least one user should exist.
    return true;
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

        if ( m_haveRootPassword )
        {
                j = new SetPasswordJob( "root",
                                        ui->rootPw->text() );
            list.append( Calamares::job_ptr( j ) );
        }

        j = new SetHostNameJob( ui->hostname->text() );
        list.append( Calamares::job_ptr( j ) );

        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        gs->insert( "hostname", ui->hostname->text() );
//        if ( user->autologin )
//            gs->insert( "autologinUser", user->username );

//        gs->insert( "username", user-> );
//        gs->insert( "password", CalamaresUtils::obscure( ui->textBoxUserPassword->text() ) );
    }

    return list;
}


void
UsersPage::onActivate()
{
    if (m_userModel.rowCount() == 0) {
        addUserClicked();
    }
}

void
UsersPage::fillSuggestions()
{
//    QString fullName = ui->textBoxFullName->text();
//    QRegExp rx( "[^a-zA-Z0-9 ]", Qt::CaseInsensitive );
//    QString cleanName = CalamaresUtils::removeDiacritics( fullName )
//                        .toLower().replace( rx, " " ).simplified();
//    QStringList cleanParts = cleanName.split( ' ' );

//    if ( !m_customUsername )
//    {
//        if ( !cleanParts.isEmpty() && !cleanParts.first().isEmpty() )
//        {
//            QString usernameSuggestion = cleanParts.first();
//            for ( int i = 1; i < cleanParts.length(); ++i )
//            {
//                if ( !cleanParts.value( i ).isEmpty() )
//                    usernameSuggestion.append( cleanParts.value( i ).at( 0 ) );
//            }
//            if ( USERNAME_RX.indexIn( usernameSuggestion ) != -1 )
//            {
//                ui->textBoxUsername->setText( usernameSuggestion );
//                validateUsernameText( usernameSuggestion );
//                m_customUsername = false;
//            }
//        }
//    }

//    if ( !m_customHostname )
//    {
//        if ( !cleanParts.isEmpty() && !cleanParts.first().isEmpty() )
//        {
//            QString hostnameSuggestion = QString( "%1-pc" ).arg( cleanParts.first() );
//            if ( HOSTNAME_RX.indexIn( hostnameSuggestion ) != -1 )
//            {
//                ui->textBoxHostname->setText( hostnameSuggestion );
//                validateHostnameText( hostnameSuggestion );
//                m_customHostname = false;
//            }
//        }
//    }
}

void
UsersPage::onHostnameTextEdited( const QString& textRef )
{
    m_customHostname = true;
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
UsersPage::onPasswordTextChanged( const QString& )
{
//    QString pw1 = ui->textBoxUserPassword->text();
//    QString pw2 = ui->textBoxUserVerifiedPassword->text();

//    if ( pw1.isEmpty() && pw2.isEmpty() )
//    {
//        ui->labelUserPasswordError->clear();
//        ui->labelUserPassword->clear();
//        m_readyPassword = false;
//    }
//    else if ( pw1 != pw2 )
//    {
//        ui->labelUserPasswordError->setText( tr( "Your passwords do not match!" ) );
//        ui->labelUserPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                         CalamaresUtils::Original,
//                                                                         ui->labelUserPassword->size() ) );
//        m_readyPassword = false;
//    }
//    else
//    {
//        ui->labelUserPasswordError->clear();
//        ui->labelUserPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
//                                                                         CalamaresUtils::Original,
//                                                                         ui->labelUserPassword->size() ) );
//        m_readyPassword = true;
//    }

//    emit checkReady( isReady() );
}


void
UsersPage::onRootPasswordTextChanged( const QString& )
{
//    QString pw1 = ui->textBoxRootPassword->text();
//    QString pw2 = ui->textBoxVerifiedRootPassword->text();

//    if ( pw1.isEmpty() && pw2.isEmpty() )
//    {
//        ui->labelRootPasswordError->clear();
//        ui->labelRootPassword->clear();
//        m_readyRootPassword = false;
//    }
//    else if ( pw1 != pw2 )
//    {
//        ui->labelRootPasswordError->setText( tr( "Your passwords do not match!" ) );
//        ui->labelRootPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                         CalamaresUtils::Original,
//                                                                         ui->labelRootPassword->size() ) );
//        m_readyRootPassword = false;
//    }
//    else
//    {
//        ui->labelRootPasswordError->clear();
//        ui->labelRootPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
//                                                                         CalamaresUtils::Original,
//                                                                         ui->labelRootPassword->size() ) );
//        m_readyRootPassword = true;
//    }

//    emit checkReady( isReady() );
}

void UsersPage::setHaveRootPassword(bool haveRootPassword) {
    m_haveRootPassword = haveRootPassword;
}

void UsersPage::setAvailableShells(const QStringList &shells) {
    m_availableShells = shells;
}
