/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
#include "CreateUserJob.h"
#include "SetPasswordJob.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>



UsersPage::UsersPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_UserSetup )
    , m_readyFullName( false )
    , m_readyUsername( false )
    , m_readyHostname( false )
    , m_readyPassword( false )
    , m_readyRootPassword( false )
{
    ui->setupUi( this );

    // Connect signals and slots
    connect( ui->textBoxFullName, &QLineEdit::textEdited,
             this, &UsersPage::onFullNameTextEdited );
    connect( ui->textBoxUsername, &QLineEdit::textEdited,
             this, &UsersPage::onUsernameTextEdited );
    connect( ui->textBoxHostname, &QLineEdit::textEdited,
             this, &UsersPage::onHostnameTextEdited );
    connect( ui->textBoxUserPassword, &QLineEdit::textChanged,
             this, &UsersPage::onPasswordTextChanged );
    connect( ui->textBoxUserVerifiedPassword, &QLineEdit::textChanged,
             this, &UsersPage::onPasswordTextChanged );
    connect( ui->textBoxRootPassword, &QLineEdit::textChanged,
             this, &UsersPage::onRootPasswordTextChanged );
    connect( ui->textBoxVerifiedRootPassword, &QLineEdit::textChanged,
             this, &UsersPage::onRootPasswordTextChanged );

    m_customUsername = false;
    m_customHostname = false;
}


UsersPage::~UsersPage()
{
    delete ui;
}


bool
UsersPage::isReady()
{
    return m_readyFullName &&
           m_readyHostname &&
           m_readyPassword &&
           m_readyRootPassword &&
           m_readyUsername;
}


QList< Calamares::job_ptr >
UsersPage::createJobs()
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
        return list;

    Calamares::Job* j;
    j = new CreateUserJob( ui->textBoxUsername->text(),
                           QString(),
                           ui->checkBoxLoginAuto->isChecked() );
    list.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( ui->textBoxUsername->text(),
                            ui->textBoxUserPassword->text() );
    list.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( "root",
                            ui->textBoxRootPassword->text() );
    list.append( Calamares::job_ptr( j ) );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    gs->insert( "hostname", ui->textBoxHostname->text() );
    if ( ui->checkBoxLoginAuto->isChecked() )
        gs->insert( "autologinUser", ui->textBoxUsername->text() );

    gs->insert( "username", ui->textBoxUsername->text() );

    return list;
}


void
UsersPage::onFullNameTextEdited( const QString &textRef )
{
    if ( textRef.isEmpty() )
    {
        ui->labelFullNameError->clear();
        ui->labelFullName->clear();
        if ( !m_customUsername )
            ui->textBoxUsername->clear();
        if ( !m_customHostname )
            ui->textBoxHostname->clear();
    }
    else
    {
        ui->labelFullName->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelFullName->size() ) );
        m_readyFullName = true;
        fillSuggestions();
    }
    checkReady( isReady() );
}


void
UsersPage::fillSuggestions()
{
    QString fullName = ui->textBoxFullName->text();
    QRegExp rx( "[^a-zA-Z0-9 ]", Qt::CaseInsensitive );
    QString cleanName = CalamaresUtils::removeDiacritics( fullName )
                        .toLower().replace( rx, " " ).simplified();
    QStringList cleanParts = cleanName.split( ' ' );

    if ( !m_customUsername )
    {
        if ( !cleanParts.isEmpty() && !cleanParts.first().isEmpty() )
        {
            QString usernameSuggestion = cleanParts.first();
            for ( int i = 1; i < cleanParts.length(); ++i )
            {
                if ( !cleanParts.value( i ).isEmpty() )
                    usernameSuggestion.append( cleanParts.value( i ).at( 0 ) );
            }
            if ( m_usernameRx.indexIn( usernameSuggestion ) != -1 )
            {
                ui->textBoxUsername->setText( usernameSuggestion );
                validateUsernameText( usernameSuggestion );
                m_customUsername = false;
            }
        }
    }

    if ( !m_customHostname )
    {
        if ( !cleanParts.isEmpty() && !cleanParts.first().isEmpty() )
        {
            QString hostnameSuggestion = QString( "%1-pc" ).arg( cleanParts.first() );
            if ( m_hostnameRx.indexIn( hostnameSuggestion ) != -1 )
            {
                ui->textBoxHostname->setText( hostnameSuggestion );
                validateHostnameText( hostnameSuggestion );
                m_customHostname = false;
            }
        }
    }
}


void
UsersPage::onUsernameTextEdited( const QString& textRef )
{
    m_customUsername = true;
    validateUsernameText( textRef );
}


void
UsersPage::validateUsernameText( const QString& textRef )
{
    QString text( textRef );
    QRegExp rx( m_usernameRx );
    QRegExpValidator val( rx );
    int pos = -1;

    if ( text.isEmpty() )
    {
        ui->labelUsernameError->clear();
        ui->labelUsername->clear();
        m_readyUsername = false;
    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        ui->labelUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelUsername->size() ) );
        --pos;

        if ( pos >= 0 && pos < text.size() )
            ui->labelUsernameError->setText(
                tr( "Your username contains an invalid character '%1'" )
                    .arg( text.at( pos ) ) );
        else
            ui->labelUsernameError->setText(
                tr( "Your username contains invalid characters!" ) );

        m_readyUsername = false;
    }
    else {
        ui->labelUsername->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelUsername->size() ) );
        ui->labelUsernameError->clear();
        m_readyUsername = true;
    }

    emit checkReady( isReady() );
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
    QRegExp rx( m_hostnameRx );
    QRegExpValidator val( rx );
    int pos = -1;

    if ( text.isEmpty() )
    {
        ui->labelHostnameError->clear();
        ui->labelHostname->clear();
        m_readyHostname= false;
    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        ui->labelHostname->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                     CalamaresUtils::Original,
                                                                     ui->labelHostname->size() ) );
        --pos;

        if ( pos >= 0 && pos < text.size() )
            ui->labelHostnameError->setText(
                tr( "Your username contains an invalid character '%1'" )
                    .arg( text.at( pos ) ) );
        else
            ui->labelHostnameError->setText(
                tr( "Your username contains invalid characters!" ) );

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
    QString pw1 = ui->textBoxUserPassword->text();
    QString pw2 = ui->textBoxUserVerifiedPassword->text();

    if ( pw1.isEmpty() && pw2.isEmpty() )
    {
        ui->labelUserPasswordError->clear();
        ui->labelUserPassword->clear();
        m_readyPassword = false;
    }
    else if ( pw1 != pw2 )
    {
        ui->labelUserPasswordError->setText( tr( "Your passwords do not match!" ) );
        ui->labelUserPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                         CalamaresUtils::Original,
                                                                         ui->labelUserPassword->size() ) );
        m_readyPassword = false;
    }
    else
    {
        ui->labelUserPasswordError->clear();
        ui->labelUserPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                         CalamaresUtils::Original,
                                                                         ui->labelUserPassword->size() ) );
        m_readyPassword = true;
    }

    emit checkReady( isReady() );
}


void
UsersPage::onRootPasswordTextChanged( const QString& )
{
    QString pw1 = ui->textBoxRootPassword->text();
    QString pw2 = ui->textBoxVerifiedRootPassword->text();

    if ( pw1.isEmpty() && pw2.isEmpty() )
    {
        ui->labelRootPasswordError->clear();
        ui->labelRootPassword->clear();
        m_readyRootPassword = false;
    }
    else if ( pw1 != pw2 )
    {
        ui->labelRootPasswordError->setText( tr( "Your passwords do not match!" ) );
        ui->labelRootPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                                         CalamaresUtils::Original,
                                                                         ui->labelRootPassword->size() ) );
        m_readyRootPassword = false;
    }
    else
    {
        ui->labelRootPasswordError->clear();
        ui->labelRootPassword->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                                         CalamaresUtils::Original,
                                                                         ui->labelRootPassword->size() ) );
        m_readyRootPassword = true;
    }

    emit checkReady( isReady() );
}
