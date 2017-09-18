/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
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
#include "SetHostNameJob.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>

/** Add a standard pixmap to a label. */
static void
markLabel( QLabel* label, CalamaresUtils::ImageType i )
{
    label->setPixmap( CalamaresUtils::defaultPixmap( i, CalamaresUtils::Original, label->size() ) );
}

UsersPage::UsersPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_UserSetup )
    , m_readyFullName( false )
    , m_readyUsername( false )
    , m_readyHostname( false )
    , m_readyPassword( false )
    , m_readyRootPassword( false )
    , m_writeRootPassword( true )
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
    connect( ui->checkBoxReusePassword, &QCheckBox::stateChanged,
             this, [this]( int checked )
    {
        ui->labelChooseRootPassword->setVisible( !checked );
        ui->labelExtraRootPassword->setVisible( !checked );
        ui->labelRootPassword->setVisible( !checked );
        ui->labelRootPasswordError->setVisible( !checked );
        ui->textBoxRootPassword->setVisible( !checked );
        ui->textBoxVerifiedRootPassword->setVisible( !checked );
        checkReady( isReady() );
    } );

    m_customUsername = false;
    m_customHostname = false;

    setWriteRootPassword( true );
    ui->checkBoxReusePassword->setChecked( true );

    CALAMARES_RETRANSLATE( ui->retranslateUi( this ); )
}


UsersPage::~UsersPage()
{
    delete ui;
}


bool
UsersPage::isReady()
{
    bool readyFields = m_readyFullName &&
                       m_readyHostname &&
                       m_readyPassword &&
                       m_readyUsername;
    if ( !m_writeRootPassword || ui->checkBoxReusePassword->isChecked() )
        return readyFields;

    return readyFields && m_readyRootPassword;
}


QList< Calamares::job_ptr >
UsersPage::createJobs( const QStringList& defaultGroupsList )
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
        return list;

    Calamares::Job* j;
    j = new CreateUserJob( ui->textBoxUsername->text(),
                           ui->textBoxFullName->text().isEmpty() ?
                               ui->textBoxUsername->text() :
                               ui->textBoxFullName->text(),
                           ui->checkBoxAutoLogin->isChecked(),
                           defaultGroupsList );
    list.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( ui->textBoxUsername->text(),
                            ui->textBoxUserPassword->text() );
    list.append( Calamares::job_ptr( j ) );

    if ( m_writeRootPassword )
    {
        if ( ui->checkBoxReusePassword->isChecked() )
            j = new SetPasswordJob( "root",
                                    ui->textBoxUserPassword->text() );
        else
            j = new SetPasswordJob( "root",
                                    ui->textBoxRootPassword->text() );
        list.append( Calamares::job_ptr( j ) );
    }
    else
    {
        j = new SetPasswordJob( "root",
                                "" ); //explicitly disable root password
        list.append( Calamares::job_ptr( j ) );
    }

    j = new SetHostNameJob( ui->textBoxHostname->text() );
    list.append( Calamares::job_ptr( j ) );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    gs->insert( "hostname", ui->textBoxHostname->text() );
    if ( ui->checkBoxAutoLogin->isChecked() )
        gs->insert( "autologinUser", ui->textBoxUsername->text() );

    gs->insert( "username", ui->textBoxUsername->text() );
    gs->insert( "password", CalamaresUtils::obscure( ui->textBoxUserPassword->text() ) );

    return list;
}


void
UsersPage::onActivate()
{
    ui->textBoxFullName->setFocus();
}


void
UsersPage::setWriteRootPassword( bool write )
{
    ui->checkBoxReusePassword->setVisible( write );
    m_writeRootPassword = write;
}


void
UsersPage::onFullNameTextEdited( const QString& textRef )
{
    if ( textRef.isEmpty() )
    {
        ui->labelFullNameError->clear();
        ui->labelFullName->clear();
        if ( !m_customUsername )
            ui->textBoxUsername->clear();
        if ( !m_customHostname )
            ui->textBoxHostname->clear();
        m_readyFullName = false;
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
            if ( USERNAME_RX.indexIn( usernameSuggestion ) != -1 )
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
            if ( HOSTNAME_RX.indexIn( hostnameSuggestion ) != -1 )
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
    QRegExp rx( USERNAME_RX );
    QRegExpValidator val( rx );
    int pos = -1;

    if ( text.isEmpty() )
    {
        ui->labelUsernameError->clear();
        ui->labelUsername->clear();
        m_readyUsername = false;
    }
    else if ( text.length() > USERNAME_MAX_LENGTH )
    {
        markLabel( ui->labelUsername, CalamaresUtils::No );
        ui->labelUsernameError->setText(
            tr( "Your username is too long." ) );

        m_readyUsername = false;
    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        markLabel( ui->labelUsername, CalamaresUtils::No );
        ui->labelUsernameError->setText(
            tr( "Your username contains invalid characters. Only lowercase letters and numbers are allowed." ) );

        m_readyUsername = false;
    }
    else {
        markLabel( ui->labelUsername, CalamaresUtils::Yes );
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
        markLabel( ui->labelHostname, CalamaresUtils::No );
        ui->labelHostnameError->setText(
            tr( "Your hostname is too short." ) );

        m_readyHostname = false;

    }
    else if ( text.length() > HOSTNAME_MAX_LENGTH )
    {
        markLabel( ui->labelHostname, CalamaresUtils::No );
        ui->labelHostnameError->setText(
            tr( "Your hostname is too long." ) );

        m_readyHostname = false;

    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        markLabel( ui->labelHostname, CalamaresUtils::No );
        ui->labelHostnameError->setText(
            tr( "Your hostname contains invalid characters. Only letters, numbers and dashes are allowed." ) );

        m_readyHostname = false;
    }
    else
    {
        markLabel( ui->labelHostname, CalamaresUtils::Yes );
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
        markLabel( ui->labelUserPassword, CalamaresUtils::No );
        m_readyPassword = false;
    }
    else
    {
        bool ok = true;
        for ( auto pc : m_passwordChecks )
        {
            QString s = pc.filter( pw1 );
            if ( !s.isEmpty() )
            {
                ui->labelUserPasswordError->setText( s );
                markLabel( ui->labelUserPassword, CalamaresUtils::No );
                ok = false;
                m_readyPassword = false;
            }
        }

        if ( ok )
        {
            ui->labelUserPasswordError->clear();
            markLabel( ui->labelUserPassword, CalamaresUtils::Yes );
            m_readyPassword = true;
        }
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
        markLabel( ui->labelRootPassword, CalamaresUtils::No );
        m_readyRootPassword = false;
    }
    else
    {
        bool ok = true;
        for ( auto pc : m_passwordChecks )
        {
            QString s = pc.filter( pw1 );
            if ( !s.isEmpty() )
            {
                ui->labelRootPasswordError->setText( s );
                markLabel( ui->labelRootPassword, CalamaresUtils::No );
                ok = false;
                m_readyRootPassword = false;
            }
        }

        if ( ok )
        {
            ui->labelRootPasswordError->clear();
            markLabel( ui->labelRootPassword, CalamaresUtils::Yes );
            m_readyRootPassword = true;
        }
    }

    emit checkReady( isReady() );
}


void
UsersPage::setAutologinDefault( bool checked )
{
    ui->checkBoxAutoLogin->setChecked( checked );
    emit checkReady( isReady() );
}

void
UsersPage::setReusePasswordDefault( bool checked )
{
    ui->checkBoxReusePassword->setChecked( checked );
    emit checkReady( isReady() );
}

UsersPage::PasswordCheck::PasswordCheck()
    : m_message()
    , m_accept( []( const QString& s )
{
    return true;
} )
{
}

UsersPage::PasswordCheck::PasswordCheck( const QString& m, AcceptFunc a )
    : m_message( [m](){ return m; } )
    , m_accept( a )
{
}

UsersPage::PasswordCheck::PasswordCheck( MessageFunc m, AcceptFunc a )
    : m_message( m )
    , m_accept( a )
{
}

void
UsersPage::addPasswordCheck( const QString& key, const QVariant& value )
{
    if ( key == "minLength" )
    {
        int minLength = -1;
        if ( value.canConvert( QVariant::Int ) )
            minLength = value.toInt();
        if ( minLength > 0 )
        {
            cDebug() << key << " .. set to" << minLength;
            m_passwordChecks.push_back(
                PasswordCheck(
                    []()
            {
                return tr( "Password is too short" );
            },
            [minLength]( const QString& s )
            {
                return s.length() >= minLength;
            } ) );
        }
    }
    else if ( key == "maxLength" )
    {
        int maxLength = -1;
        if ( value.canConvert( QVariant::Int ) )
            maxLength = value.toInt();
        if ( maxLength > 0 )
        {
            cDebug() << key << " .. set to" << maxLength;
            m_passwordChecks.push_back(
                PasswordCheck( []()
            {
                return tr( "Password is too long" );
            }, [maxLength]( const QString& s )
            {
                return s.length() <= maxLength;
            } ) );
        }
    }
    else
        cDebug() << "WARNING: Unknown password-check key" << '"' << key << '"';
}
