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

/** @brief Add an error message and pixmap to a label. */
static inline void
labelError( QLabel* pix, QLabel* label, CalamaresUtils::ImageType icon, const QString& message )
{
    label->setText( message );
    pix->setPixmap( CalamaresUtils::defaultPixmap( icon, CalamaresUtils::Original, label->size() ) );
}

/** @brief Clear error, set happy pixmap on a label to indicate "ok". */
static inline void
labelOk( QLabel* pix, QLabel* label )
{
    label->clear();
    pix->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::StatusOk, CalamaresUtils::Original, label->size() ) );
}

/** @brief Sets error or ok on a label depending on @p status and @p value
 *
 * - An **empty** @p value gets no message and no icon.
 * - A non-empty @p value, with an **empty** @p status gets an "ok".
 * - A non-empty @p value with a non-empty @p status gets an error indicator.
 */
static inline void
labelStatus( QLabel* pix, QLabel* label, const QString& value, const QString& status )
{
    if ( status.isEmpty() )
    {
        if ( value.isEmpty() )
        {
            // This is different from labelOK() because no checkmark is shown
            label->clear();
            pix->clear();
        }
        else
        {
            labelOk( pix, label );
        }
    }
    else
    {
        labelError( pix, label, CalamaresUtils::ImageType::StatusError, status );
    }
}

UsersPage::UsersPage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_UserSetup )
    , m_config( config )
{
    ui->setupUi( this );

    ui->checkBoxReusePassword->setVisible( m_config->writeRootPassword() );
    ui->checkBoxReusePassword->setChecked( m_config->reuseUserPasswordForRoot() );

    ui->checkBoxValidatePassword->setVisible( m_config->permitWeakPasswords() );
    ui->checkBoxValidatePassword->setChecked( m_config->requireStrongPasswords() );

    // Connect signals and slots
    ui->textBoxUserPassword->setText( config->userPassword() );
    connect( ui->textBoxUserPassword, &QLineEdit::textChanged, config, &Config::setUserPassword );
    connect( config, &Config::userPasswordChanged, ui->textBoxUserPassword, &QLineEdit::setText );
    ui->textBoxUserVerifiedPassword->setText( config->userPasswordSecondary() );
    connect( ui->textBoxUserVerifiedPassword, &QLineEdit::textChanged, config, &Config::setUserPasswordSecondary );
    connect( config, &Config::userPasswordSecondaryChanged, ui->textBoxUserVerifiedPassword, &QLineEdit::setText );
    connect( config, &Config::userPasswordStatusChanged, this, &UsersPage::reportUserPasswordStatus );

    ui->textBoxRootPassword->setText( config->rootPassword() );
    connect( ui->textBoxRootPassword, &QLineEdit::textChanged, config, &Config::setRootPassword );
    connect( config, &Config::rootPasswordChanged, ui->textBoxRootPassword, &QLineEdit::setText );
    ui->textBoxVerifiedRootPassword->setText( config->rootPasswordSecondary() );
    connect( ui->textBoxVerifiedRootPassword, &QLineEdit::textChanged, config, &Config::setRootPasswordSecondary );
    connect( config, &Config::rootPasswordSecondaryChanged, ui->textBoxVerifiedRootPassword, &QLineEdit::setText );
    connect( config, &Config::rootPasswordStatusChanged, this, &UsersPage::reportRootPasswordStatus );

    connect( ui->checkBoxValidatePassword, &QCheckBox::stateChanged, this, [this]( int checked ) {
        m_config->setRequireStrongPasswords( checked != Qt::Unchecked );
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

    if ( m_config->writeRootPassword() )
    {
        connect( ui->checkBoxReusePassword, &QCheckBox::stateChanged, this, [this]( int checked ) {
            m_config->setReuseUserPasswordForRoot( checked != Qt::Unchecked );
        } );
        connect( config, &Config::reuseUserPasswordForRootChanged, ui->checkBoxReusePassword, &QCheckBox::setChecked );
        connect( ui->checkBoxReusePassword, &QCheckBox::stateChanged, this, &UsersPage::onReuseUserPasswordChanged );
    }

    if ( m_config->permitWeakPasswords() )
    {
        connect( ui->checkBoxValidatePassword, &QCheckBox::stateChanged, this, [this]( int checked ) {
            m_config->setRequireStrongPasswords( checked != Qt::Unchecked );
        } );
        connect( config, &Config::requireStrongPasswordsChanged, ui->checkBoxValidatePassword, &QCheckBox::setChecked );
    }

    CALAMARES_RETRANSLATE_SLOT( &UsersPage::retranslate )

    onReuseUserPasswordChanged( m_config->reuseUserPasswordForRoot() );
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

    const auto up = m_config->userPasswordStatus();
    reportUserPasswordStatus( up.first, up.second );
    const auto rp = m_config->rootPasswordStatus();
    reportRootPasswordStatus( rp.first, rp.second );
}


void
UsersPage::onActivate()
{
    ui->textBoxFullName->setFocus();
    const auto up = m_config->userPasswordStatus();
    reportUserPasswordStatus( up.first, up.second );
    const auto rp = m_config->rootPasswordStatus();
    reportRootPasswordStatus( rp.first, rp.second );
}


void
UsersPage::onFullNameTextEdited( const QString& fullName )
{
    labelStatus( ui->labelFullName, ui->labelFullNameError, fullName, QString() );
}

void
UsersPage::reportLoginNameStatus( const QString& status )
{
    labelStatus( ui->labelUsername, ui->labelUsernameError, m_config->loginName(), status );
}

void
UsersPage::reportHostNameStatus( const QString& status )
{
    labelStatus( ui->labelHostname, ui->labelHostnameError, m_config->hostName(), status );
}

static inline void
passwordStatus( QLabel* iconLabel, QLabel* messageLabel, int validity, const QString& message )
{
    switch ( validity )
    {
    case Config::PasswordValidity::Valid:
        labelOk( iconLabel, messageLabel );
        break;
    case Config::PasswordValidity::Weak:
        labelError( iconLabel, messageLabel, CalamaresUtils::StatusWarning, message );
        break;
    case Config::PasswordValidity::Invalid:
    default:
        labelError( iconLabel, messageLabel, CalamaresUtils::StatusError, message );
        break;
    }
}

void
UsersPage::reportRootPasswordStatus( int validity, const QString& message )
{
    passwordStatus( ui->labelRootPassword, ui->labelRootPasswordError, validity, message );
}

void
UsersPage::reportUserPasswordStatus( int validity, const QString& message )
{
    passwordStatus( ui->labelUserPassword, ui->labelUserPasswordError, validity, message );
}


void
UsersPage::onReuseUserPasswordChanged( const int checked )
{
    /* When "reuse" is checked, hide the fields for explicitly
     * entering the root password. However, if we're going to
     * disable the root password anyway, hide them all regardless of
     * the checkbox -- so when writeRoot is false, visible needs
     * to be false, to hide them all.
     *
     * In principle this is only connected when writeRootPassword is @c true,
     * but it is **always** called at least once in the constructor
     * to set up initial visibility.
     */
    const bool visible = m_config->writeRootPassword() ? !checked : false;
    ui->labelChooseRootPassword->setVisible( visible );
    ui->labelRootPassword->setVisible( visible );
    ui->labelRootPasswordError->setVisible( visible );
    ui->textBoxRootPassword->setVisible( visible );
    ui->textBoxVerifiedRootPassword->setVisible( visible );
}
