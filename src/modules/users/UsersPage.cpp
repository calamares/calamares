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

#include "ui_page_usersetup.h"

#include "CreateUserJob.h"
#include "SetHostNameJob.h"
#include "SetPasswordJob.h"

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
#include <QRegExp>
#include <QRegExpValidator>

static const QRegExp USERNAME_RX( "^[a-z_][a-z0-9_-]*[$]?$" );
static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
static constexpr const int USERNAME_MAX_LENGTH = 31;
static constexpr const int HOSTNAME_MIN_LENGTH = 2;
static constexpr const int HOSTNAME_MAX_LENGTH = 63;

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
    connect( ui->textBoxFullName, &QLineEdit::textEdited, this, &UsersPage::onFullNameTextEdited );
    connect( ui->textBoxUsername, &QLineEdit::textEdited, this, &UsersPage::onUsernameTextEdited );
    connect( ui->textBoxHostname, &QLineEdit::textEdited, this, &UsersPage::onHostnameTextEdited );
    connect( ui->textBoxUserPassword, &QLineEdit::textChanged, this, &UsersPage::onPasswordTextChanged );
    connect( ui->textBoxUserVerifiedPassword, &QLineEdit::textChanged, this, &UsersPage::onPasswordTextChanged );
    connect( ui->textBoxRootPassword, &QLineEdit::textChanged, this, &UsersPage::onRootPasswordTextChanged );
    connect( ui->textBoxVerifiedRootPassword, &QLineEdit::textChanged, this, &UsersPage::onRootPasswordTextChanged );
    connect( ui->checkBoxValidatePassword, &QCheckBox::stateChanged, this, [ this ]( int ) {
        onPasswordTextChanged( ui->textBoxUserPassword->text() );
        onRootPasswordTextChanged( ui->textBoxRootPassword->text() );
        checkReady( isReady() );
    } );
    connect( ui->checkBoxReusePassword, &QCheckBox::stateChanged, this, [ this ]( int checked ) {
        /* When "reuse" is checked, hide the fields for explicitly
         * entering the root password. However, if we're going to
         * disable the root password anyway, hide them all regardless of
         * the checkbox -- so when writeRoot is false, checked needs
         * to be true, to hide them all.
         */
        if ( !m_writeRootPassword )
        {
            checked = true;
        }
        ui->labelChooseRootPassword->setVisible( !checked );
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
        ui->textBoxUsername->setToolTip( tr( "<small>If more than one person will "
                                             "use this computer, you can create multiple "
                                             "accounts after setup.</small>" ) );
    }
    else
    {
        ui->textBoxUsername->setToolTip( tr( "<small>If more than one person will "
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
UsersPage::isReady()
{
    bool readyFields = m_readyFullName && m_readyHostname && m_readyPassword && m_readyUsername;
    if ( !m_writeRootPassword || ui->checkBoxReusePassword->isChecked() )
    {
        return readyFields;
    }

    return readyFields && m_readyRootPassword;
}

QString
UsersPage::getHostname() const
{
    return ui->textBoxHostname->text();
}

QString
UsersPage::getRootPassword() const
{
    if ( m_writeRootPassword )
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
    return QPair< QString, QString >( ui->textBoxUsername->text(), ui->textBoxUserPassword->text() );
}

QList< Calamares::job_ptr >
UsersPage::createJobs( const QStringList& defaultGroupsList )
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
    {
        return list;
    }

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    Calamares::Job* j;
    j = new CreateUserJob( ui->textBoxUsername->text(),
                           ui->textBoxFullName->text().isEmpty() ? ui->textBoxUsername->text()
                                                                 : ui->textBoxFullName->text(),
                           ui->checkBoxAutoLogin->isChecked(),
                           defaultGroupsList );
    list.append( Calamares::job_ptr( j ) );

    if ( m_writeRootPassword )
    {
        gs->insert( "reuseRootPassword", ui->checkBoxReusePassword->isChecked() );
    }
    gs->insert( "hostname", ui->textBoxHostname->text() );
    if ( ui->checkBoxAutoLogin->isChecked() )
    {
        gs->insert( "autologinUser", ui->textBoxUsername->text() );
    }

    gs->insert( "username", ui->textBoxUsername->text() );
    gs->insert( "password", CalamaresUtils::obscure( ui->textBoxUserPassword->text() ) );

    return list;
}


void
UsersPage::onActivate()
{
    ui->textBoxFullName->setFocus();
    onPasswordTextChanged( QString() );
    onRootPasswordTextChanged( QString() );
}


void
UsersPage::setWriteRootPassword( bool write )
{
    m_writeRootPassword = write;
    ui->checkBoxReusePassword->setVisible( write );
}


void
UsersPage::onFullNameTextEdited( const QString& textRef )
{
    if ( textRef.isEmpty() )
    {
        ui->labelFullNameError->clear();
        ui->labelFullName->clear();
        if ( !m_customUsername )
        {
            ui->textBoxUsername->clear();
        }
        if ( !m_customHostname )
        {
            ui->textBoxHostname->clear();
        }
        m_readyFullName = false;
    }
    else
    {
        ui->labelFullName->setPixmap(
            CalamaresUtils::defaultPixmap( CalamaresUtils::Yes, CalamaresUtils::Original, ui->labelFullName->size() ) );
        m_readyFullName = true;
        fillSuggestions();
    }
    checkReady( isReady() );
}

/** @brief Guess the machine's name
 *
 * If there is DMI data, use that; otherwise, just call the machine "-pc".
 * Reads the DMI data just once.
 */
static QString
guessProductName()
{
    static bool tried = false;
    static QString dmiProduct;

    if ( !tried )
    {
        // yes validateHostnameText() but these files can be a mess
        QRegExp dmirx( "[^a-zA-Z0-9]", Qt::CaseInsensitive );
        QFile dmiFile( QStringLiteral( "/sys/devices/virtual/dmi/id/product_name" ) );

        if ( dmiFile.exists() && dmiFile.open( QIODevice::ReadOnly ) )
        {
            dmiProduct = QString::fromLocal8Bit( dmiFile.readAll().simplified().data() )
                             .toLower()
                             .replace( dmirx, " " )
                             .remove( ' ' );
        }
        if ( dmiProduct.isEmpty() )
        {
            dmiProduct = QStringLiteral( "-pc" );
        }
        tried = true;
    }
    return dmiProduct;
}

void
UsersPage::fillSuggestions()
{
    QString fullName = ui->textBoxFullName->text();
    QRegExp rx( "[^a-zA-Z0-9 ]", Qt::CaseInsensitive );
    QString cleanName = CalamaresUtils::removeDiacritics( fullName ).toLower().replace( rx, " " ).simplified();
    QStringList cleanParts = cleanName.split( ' ' );

    if ( !m_customUsername )
    {
        if ( !cleanParts.isEmpty() && !cleanParts.first().isEmpty() )
        {
            QString usernameSuggestion = cleanParts.first();
            for ( int i = 1; i < cleanParts.length(); ++i )
            {
                if ( !cleanParts.value( i ).isEmpty() )
                {
                    usernameSuggestion.append( cleanParts.value( i ).at( 0 ) );
                }
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
            QString hostnameSuggestion;
            QString productName = guessProductName();
            hostnameSuggestion = QString( "%1-%2" ).arg( cleanParts.first() ).arg( productName );
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
    QRegExpValidator val_whole( USERNAME_RX );
    QRegExpValidator val_start( QRegExp( "[a-z_].*" ) );  // anchors are implicit in QRegExpValidator
    int pos = -1;

    if ( text.isEmpty() )
    {
        ui->labelUsernameError->clear();
        ui->labelUsername->clear();
        m_readyUsername = false;
    }
    else if ( text.length() > USERNAME_MAX_LENGTH )
    {
        labelError( ui->labelUsername, ui->labelUsernameError, tr( "Your username is too long." ) );
        m_readyUsername = false;
    }
    else if ( val_start.validate( text, pos ) == QValidator::Invalid )
    {
        labelError( ui->labelUsername,
                    ui->labelUsernameError,
                    tr( "Your username must start with a lowercase letter or underscore." ) );
        m_readyUsername = false;
    }
    else if ( val_whole.validate( text, pos ) == QValidator::Invalid )
    {
        labelError( ui->labelUsername,
                    ui->labelUsernameError,
                    tr( "Only lowercase letters, numbers, underscore and hyphen are allowed." ) );
        m_readyUsername = false;
    }
    else
    {
        labelOk( ui->labelUsername, ui->labelUsernameError );
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
    QRegExpValidator val( HOSTNAME_RX );
    int pos = -1;

    if ( text.isEmpty() )
    {
        ui->labelHostnameError->clear();
        ui->labelHostname->clear();
        m_readyHostname = false;
    }
    else if ( text.length() < HOSTNAME_MIN_LENGTH )
    {
        labelError( ui->labelHostname, ui->labelHostnameError, tr( "Your hostname is too short." ) );
        m_readyHostname = false;
    }
    else if ( text.length() > HOSTNAME_MAX_LENGTH )
    {
        labelError( ui->labelHostname, ui->labelHostnameError, tr( "Your hostname is too long." ) );
        m_readyHostname = false;
    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        labelError( ui->labelHostname,
                    ui->labelHostnameError,
                    tr( "Only letters, numbers, underscore and hyphen are allowed." ) );
        m_readyHostname = false;
    }
    else
    {
        labelOk( ui->labelHostname, ui->labelHostnameError );
        m_readyHostname = true;
    }

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
