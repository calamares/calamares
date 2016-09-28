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

QVariant UsersListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        User* user = m_currentUsers.at( index.row() );
        return QVariant( user->toString() );
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

    // TODO: remove
    addUser("prova", "test", "test", false);

    ui->usersListView->setModel(&m_userModel);
    ui->usersListView->show();
    CALAMARES_RETRANSLATE( ui->retranslateUi( this ); );
}

UsersPage::~UsersPage()
{
    delete ui;
}

void
UsersPage::addUserClicked() {
    QPointer<AddUserDialog> dlg = new AddUserDialog( this );

    if ( dlg->exec() == QDialog::Accepted ) {
        // TODO: put groups and avatar.
        addUser(dlg->login, dlg->name, dlg->password, dlg->autoLogin);
    }

    delete dlg;
}

void
UsersPage::deleteUserClicked() {
    QItemSelectionModel* selectionModel = ui->usersListView->selectionModel();

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
UsersPage::addUser(const QString &login, const QString &fullName, const QString &password, bool autologin) {
    User* newUser = new User(login, fullName, QStringList());
    m_userModel.addUser(newUser);

    ui->hostname->setText( login + "-pc" );
}

bool
UsersPage::isReady()
{
    return true;
//    bool readyFields = m_readyFullName &&
//                       m_readyHostname &&
//                       m_readyPassword &&
//                       m_readyUsername;
//    if ( !m_writeRootPassword || ui->checkBoxReusePassword->isChecked() )
//        return readyFields;

//    return readyFields && m_readyRootPassword;
}


QList< Calamares::job_ptr >
UsersPage::createJobs( const QStringList& defaultGroupsList )
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
        return list;

//    Calamares::Job* j;
//    j = new CreateUserJob( ui->textBoxUsername->text(),
//                           ui->textBoxFullName->text().isEmpty() ?
//                               ui->textBoxUsername->text() :
//                               ui->textBoxFullName->text(),
//                           ui->checkBoxAutoLogin->isChecked(),
//                           defaultGroupsList );
//    list.append( Calamares::job_ptr( j ) );

//    j = new SetPasswordJob( ui->textBoxUsername->text(),
//                            ui->textBoxUserPassword->text() );
//    list.append( Calamares::job_ptr( j ) );

//    if ( m_writeRootPassword )
//    {
//        if ( ui->checkBoxReusePassword->isChecked() )
//            j = new SetPasswordJob( "root",
//                                    ui->textBoxUserPassword->text() );
//        else
//            j = new SetPasswordJob( "root",
//                                    ui->textBoxRootPassword->text() );
//        list.append( Calamares::job_ptr( j ) );
//    }

//    j = new SetHostNameJob( ui->textBoxHostname->text() );
//    list.append( Calamares::job_ptr( j ) );

//    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
//    gs->insert( "hostname", ui->textBoxHostname->text() );
//    if ( ui->checkBoxAutoLogin->isChecked() )
//        gs->insert( "autologinUser", ui->textBoxUsername->text() );

//    gs->insert( "username", ui->textBoxUsername->text() );
//    gs->insert( "password", CalamaresUtils::obscure( ui->textBoxUserPassword->text() ) );

    return list;
}


void
UsersPage::onActivate()
{
    addUserClicked();
}


void
UsersPage::setWriteRootPassword( bool write )
{
//    ui->checkBoxReusePassword->setVisible( write );
//    m_writeRootPassword = write;
}


void
UsersPage::onFullNameTextEdited( const QString& textRef )
{
//    if ( textRef.isEmpty() )
//    {
//        ui->labelFullNameError->clear();
//        ui->labelFullName->clear();
//        if ( !m_customUsername )
//            ui->textBoxUsername->clear();
//        if ( !m_customHostname )
//            ui->textBoxHostname->clear();
//        m_readyFullName = false;
//    }
//    else
//    {
//        ui->labelFullName->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelFullName->size() ) );
//        m_readyFullName = true;
//        fillSuggestions();
//    }
//    checkReady( isReady() );
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
UsersPage::onUsernameTextEdited( const QString& textRef )
{
//    m_customUsername = true;
//    validateUsernameText( textRef );
}


void
UsersPage::validateUsernameText( const QString& textRef )
{
//    QString text( textRef );
//    QRegExp rx( USERNAME_RX );
//    QRegExpValidator val( rx );
//    int pos = -1;

//    if ( text.isEmpty() )
//    {
//        ui->labelUsernameError->clear();
//        ui->labelUsername->clear();
//        m_readyUsername = false;
//    }
//    else if ( text.length() > USERNAME_MAX_LENGTH )
//    {
//        ui->labelUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelUsername->size() ) );
//        ui->labelUsernameError->setText(
//            tr( "Your username is too long." ) );

//        m_readyUsername = false;
//    }
//    else if ( val.validate( text, pos ) == QValidator::Invalid )
//    {
//        ui->labelUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelUsername->size() ) );
//        ui->labelUsernameError->setText(
//            tr( "Your username contains invalid characters. Only lowercase letters and numbers are allowed." ) );

//        m_readyUsername = false;
//    }
//    else {
//        ui->labelUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelUsername->size() ) );
//        ui->labelUsernameError->clear();
//        m_readyUsername = true;
//    }

//    emit checkReady( isReady() );
}


void
UsersPage::onHostnameTextEdited( const QString& textRef )
{
//    m_customHostname = true;
//    validateHostnameText( textRef );
}


void
UsersPage::validateHostnameText( const QString& textRef )
{
//    QString text = textRef;
//    QRegExp rx( HOSTNAME_RX );
//    QRegExpValidator val( rx );
//    int pos = -1;

//    if ( text.isEmpty() )
//    {
//        ui->labelHostnameError->clear();
//        ui->labelHostname->clear();
//        m_readyHostname= false;
//    }
//    else if ( text.length() < HOSTNAME_MIN_LENGTH )
//    {
//        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelHostname->size() ) );
//        ui->labelHostnameError->setText(
//            tr( "Your hostname is too short." ) );

//        m_readyHostname = false;

//    }
//    else if ( text.length() > HOSTNAME_MAX_LENGTH )
//    {
//        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelHostname->size() ) );
//        ui->labelHostnameError->setText(
//            tr( "Your hostname is too long." ) );

//        m_readyHostname = false;

//    }
//    else if ( val.validate( text, pos ) == QValidator::Invalid )
//    {
//        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelHostname->size() ) );
//        ui->labelHostnameError->setText(
//            tr( "Your hostname contains invalid characters. Only letters, numbers and dashes are allowed." ) );

//        m_readyHostname = false;
//    }
//    else
//    {
//        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
//                                                                     CalamaresUtils::Original,
//                                                                     ui->labelHostname->size() ) );
//        ui->labelHostnameError->clear();
//        m_readyHostname = true;
//    }

//    emit checkReady( isReady() );
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


void
UsersPage::setAutologinDefault( bool checked )
{
//    ui->checkBoxAutoLogin->setChecked( checked );
//    emit checkReady( isReady() );
}

void
UsersPage::setReusePasswordDefault( bool checked )
{
//    ui->checkBoxReusePassword->setChecked( checked );
//    emit checkReady( isReady() );
}
