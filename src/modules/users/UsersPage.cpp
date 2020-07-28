/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
 *   Copyright 2020, Gabriel Craciunescu <crazy@frugalware.org>
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

#include "Config.h"
#include "ui_page_usersetup.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/String.h"

#include <QBoxLayout>
#include <QFile>
#include <QLabel>
#include <QLineEdit>

/** @brief How bad is the error for labelError() ? */
enum class Badness
{
    Fatal,
    Warning
};

/** Add an error message and pixmap to a label. */
static inline void
labelError( QLabel* pix, QLabel* label, const QString& message, Badness bad = Badness::Fatal )
{
    label->setText( message );
    pix->setPixmap( CalamaresUtils::defaultPixmap( ( bad == Badness::Fatal ) ? CalamaresUtils::StatusError
                                                                             : CalamaresUtils::StatusWarning,
                                                   CalamaresUtils::Original,
                                                   label->size() ) );
}

/** Clear error, indicate OK on a label. */
static inline void
labelOk( QLabel* pix, QLabel* label )
{
    label->clear();
    pix->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes, CalamaresUtils::Original, label->size() ) );
}

/** Indicate error, update @p ok based on @p status */
static inline void
labelStatus( QLabel* pix, QLabel* label, const QString& value, const QString& status, bool& ok )
{
    if ( status.isEmpty() )
    {
        if ( value.isEmpty() )
        {
            // This is different from labelOK() because no checkmark is shown
            label->clear();
            pix->clear();
            ok = false;
        }
        else
        {
            labelOk( pix, label );
            ok = true;
        }
    }
    else
    {
        labelError( pix, label, status );
        ok = false;
    }
}

UsersPage::UsersPage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_UserSetup )
    , m_config( config )
    , m_readyFullName( false )
    , m_readyUsername( false )
    , m_readyHostname( false )
    , m_readyPassword( false )
    , m_readyRootPassword( false )
{
    ui->setupUi( this );

    // Connect signals and slots
    connect( ui->textBoxUserPassword, &QLineEdit::textChanged, this, &UsersPage::onPasswordTextChanged );
    connect( ui->textBoxUserVerifiedPassword, &QLineEdit::textChanged, this, &UsersPage::onPasswordTextChanged );
    connect( ui->textBoxRootPassword, &QLineEdit::textChanged, this, &UsersPage::onRootPasswordTextChanged );
    connect( ui->textBoxVerifiedRootPassword, &QLineEdit::textChanged, this, &UsersPage::onRootPasswordTextChanged );
    connect( ui->checkBoxValidatePassword, &QCheckBox::stateChanged, this, [this]( int ) {
        onPasswordTextChanged( ui->textBoxUserPassword->text() );
        onRootPasswordTextChanged( ui->textBoxRootPassword->text() );
        checkReady( isReady() );
    } );
    connect( ui->checkBoxReusePassword, &QCheckBox::stateChanged, this, [this]( const int checked ) {
        /* When "reuse" is checked, hide the fields for explicitly
         * entering the root password. However, if we're going to
         * disable the root password anyway, hide them all regardless of
         * the checkbox -- so when writeRoot is false, checked needs
         * to be true, to hide them all.
         */
        const bool visible = m_config->writeRootPassword() ? !checked : false;
        ui->labelChooseRootPassword->setVisible( visible );
        ui->labelRootPassword->setVisible( visible );
        ui->labelRootPasswordError->setVisible( visible );
        ui->textBoxRootPassword->setVisible( visible );
        ui->textBoxVerifiedRootPassword->setVisible( visible );
        checkReady( isReady() );
    } );

    connect( ui->textBoxFullName, &QLineEdit::textEdited, config, &Config::setFullName );
    connect( config, &Config::fullNameChanged, this, &UsersPage::onFullNameTextEdited );

    connect( ui->textBoxHostName, &QLineEdit::textEdited, config, &Config::setHostName );
    connect( config, &Config::hostNameChanged, ui->textBoxHostName, &QLineEdit::setText );
    connect( config, &Config::hostNameStatusChanged, this, &UsersPage::reportHostNameStatus );

    connect( ui->textBoxLoginName, &QLineEdit::textEdited, config, &Config::setLoginName );
    connect( config, &Config::loginNameChanged, ui->textBoxLoginName, &QLineEdit::setText );
    connect( config, &Config::loginNameStatusChanged, this, &UsersPage::reportLoginNameStatus );

    connect( ui->checkBoxDoAutoLogin, &QCheckBox::stateChanged, this, [this]( int checked ) {
        m_config->setAutoLogin( checked != Qt::Unchecked );
    } );
    connect( config, &Config::autoLoginChanged, ui->checkBoxDoAutoLogin, &QCheckBox::setChecked );

    ui->checkBoxReusePassword->setVisible( m_config->writeRootPassword() );
    ui->checkBoxReusePassword->setChecked( true );
    ui->checkBoxValidatePassword->setChecked( true );

    setPasswordCheckboxVisible( false );

    CALAMARES_RETRANSLATE_SLOT( &UsersPage::retranslate );
}

UsersPage::~UsersPage()
{
    delete ui;
}

void
UsersPage::retranslate()
{
    ui->retranslateUi( this );
    if ( Calamares::Settings::instance()->isSetupMode() )
    {
        ui->textBoxLoginName->setToolTip( tr( "<small>If more than one person will "
                                              "use this computer, you can create multiple "
                                              "accounts after setup.</small>" ) );
    }
    else
    {
        ui->textBoxLoginName->setToolTip( tr( "<small>If more than one person will "
                                              "use this computer, you can create multiple "
                                              "accounts after installation.</small>" ) );
    }
    // Re-do password checks (with output messages) as well.
    // .. the password-checking methods get their values from the text boxes,
    //    not from their parameters.
    onPasswordTextChanged( QString() );
    onRootPasswordTextChanged( QString() );
}


bool
UsersPage::isReady() const
{
    bool readyFields = m_readyFullName && m_readyHostname && m_readyPassword && m_readyUsername;
    // If we're going to write a root password, we need a valid one (or reuse the user's password)
    readyFields
        &= m_config->writeRootPassword() ? ( m_readyRootPassword || ui->checkBoxReusePassword->isChecked() ) : true;
    return readyFields;
}

QString
UsersPage::getRootPassword() const
{
    if ( m_config->writeRootPassword() )
    {
        if ( ui->checkBoxReusePassword->isChecked() )
        {
            return ui->textBoxUserPassword->text();
        }
        else
        {
            return ui->textBoxRootPassword->text();
        }
    }
    else
    {
        return QString();
    }
}

QPair< QString, QString >
UsersPage::getUserPassword() const
{
    return QPair< QString, QString >( m_config->loginName(), ui->textBoxUserPassword->text() );
}

void
UsersPage::fillGlobalStorage() const
{
    if ( !isReady() )
    {
        return;
    }

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    if ( m_config->writeRootPassword() )
    {
        gs->insert( "reuseRootPassword", ui->checkBoxReusePassword->isChecked() );
    }
    gs->insert( "password", CalamaresUtils::obscure( ui->textBoxUserPassword->text() ) );
}


void
UsersPage::onActivate()
{
    ui->textBoxFullName->setFocus();
    onPasswordTextChanged( QString() );
    onRootPasswordTextChanged( QString() );
}


void
UsersPage::onFullNameTextEdited( const QString& fullName )
{
    labelStatus( ui->labelFullName, ui->labelFullNameError, fullName, QString(), m_readyFullName );
    checkReady( isReady() );
}

void
UsersPage::reportLoginNameStatus( const QString& status )
{
    labelStatus( ui->labelUsername, ui->labelUsernameError, m_config->loginName(), status, m_readyUsername );
    emit checkReady( isReady() );
}

void
UsersPage::reportHostNameStatus( const QString& status )
{
    labelStatus( ui->labelHostname, ui->labelHostnameError, m_config->hostName(), status, m_readyHostname );
    emit checkReady( isReady() );
}

bool
UsersPage::checkPasswordAcceptance( const QString& pw1, const QString& pw2, QLabel* badge, QLabel* message )
{
    if ( pw1 != pw2 )
    {
        labelError( badge, message, tr( "Your passwords do not match!" ) );
        return false;
    }
    else
    {
        bool failureIsFatal = ui->checkBoxValidatePassword->isChecked();
        bool failureFound = false;

        if ( m_passwordChecksChanged )
        {
            std::sort( m_passwordChecks.begin(), m_passwordChecks.end() );
            m_passwordChecksChanged = false;
        }

        for ( auto pc : m_passwordChecks )
        {
            QString s = pc.filter( pw1 );

            if ( !s.isEmpty() )
            {
                labelError( badge, message, s, failureIsFatal ? Badness::Fatal : Badness::Warning );
                failureFound = true;
                if ( failureIsFatal )
                {
                    return false;
                }
            }
        }

        if ( !failureFound )
        {
            labelOk( badge, message );
        }

        // Here, if failureFound is true then we've found **warnings**,
        // which is ok to continue but the user should know.
        return true;
    }
}

void
UsersPage::onPasswordTextChanged( const QString& )
{
    m_readyPassword = checkPasswordAcceptance( ui->textBoxUserPassword->text(),
                                               ui->textBoxUserVerifiedPassword->text(),
                                               ui->labelUserPassword,
                                               ui->labelUserPasswordError );

    emit checkReady( isReady() );
}

void
UsersPage::onRootPasswordTextChanged( const QString& )
{
    m_readyRootPassword = checkPasswordAcceptance( ui->textBoxRootPassword->text(),
                                                   ui->textBoxVerifiedRootPassword->text(),
                                                   ui->labelRootPassword,
                                                   ui->labelRootPasswordError );
    emit checkReady( isReady() );
}


void
UsersPage::setPasswordCheckboxVisible( bool visible )
{
    ui->checkBoxValidatePassword->setVisible( visible );
}

void
UsersPage::setValidatePasswordDefault( bool checked )
{
    ui->checkBoxValidatePassword->setChecked( checked );
    emit checkReady( isReady() );
}

void
UsersPage::setReusePasswordDefault( bool checked )
{
    ui->checkBoxReusePassword->setChecked( checked );
    emit checkReady( isReady() );
}

void
UsersPage::addPasswordCheck( const QString& key, const QVariant& value )
{
    m_passwordChecksChanged = true;

    if ( key == "minLength" )
    {
        add_check_minLength( m_passwordChecks, value );
    }
    else if ( key == "maxLength" )
    {
        add_check_maxLength( m_passwordChecks, value );
    }
    else if ( key == "nonempty" )
    {
        if ( value.toBool() )
        {
            m_passwordChecks.push_back(
                PasswordCheck( []() { return QCoreApplication::translate( "PWQ", "Password is empty" ); },
                               []( const QString& s ) { return !s.isEmpty(); },
                               PasswordCheck::Weight( 1 ) ) );
        }
    }
#ifdef CHECK_PWQUALITY
    else if ( key == "libpwquality" )
    {
        add_check_libpwquality( m_passwordChecks, value );
    }
#endif  // CHECK_PWQUALITY
    else
    {
        cWarning() << "Unknown password-check key" << key;
    }
}
