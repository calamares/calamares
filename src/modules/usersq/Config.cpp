/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "Config.h"

#include "CreateUserJob.h"
#include "SetHostNameJob.h"
#include "SetPasswordJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include <QCoreApplication>

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/String.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>

static const QRegExp USERNAME_RX( "^[a-z_][a-z0-9_-]*[$]?$" );
static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
static constexpr const int USERNAME_MAX_LENGTH = 31;
static constexpr const int HOSTNAME_MIN_LENGTH = 2;
static constexpr const int HOSTNAME_MAX_LENGTH = 63;


/** Add an error message and pixmap to a label. */
void
Config::labelError(const QString& message, const Status::StatusCode &status )
{
    cDebug()<< "Settign error" << message << status;
    m_status.status = status;
    m_status.message = message;
//     m_status.icon = CalamaresUtils::defaultPixmapUrl( ( status == Status::StatusCode::Fatal ) ? CalamaresUtils::StatusError
//     : CalamaresUtils::StatusWarning,
//     CalamaresUtils::Original);
    emit statusChanged();
}

/** Clear error, indicate OK on a label. */
void
Config::labelOk(const Status::StatusCode &status )
{
    m_status.status = status;
    m_status.message = "";
    emit statusChanged();
//     pix->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes, CalamaresUtils::Original, label->size() ) );
}

Config::Config(QObject *parent) : QObject(parent)
, m_readyFullName( false )
, m_readyUsername( false )
, m_customUsername ( false )
, m_readyHostname( false )
, m_customHostname ( false )
, m_readyPassword( false )
, m_readyRootPassword( false )
, m_writeRootPassword( true )
, m_reusePassword( true )
, m_reusePasswordVisible( false )
, m_autologin( false )
, m_validatePasswords( true )
, m_validatePasswordsVisible( false )

{
    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate );
}


void
Config::retranslate()
{
//     ui->retranslateUi( this );
//     if ( Calamares::Settings::instance()->isSetupMode() )
//     {
//         ui->textBoxUsername->setToolTip( tr( "<small>If more than one person will "
//         "use this computer, you can create multiple "
//         "accounts after setup.</small>" ) );
//     }
//     else
//     {
//         ui->textBoxUsername->setToolTip( tr( "<small>If more than one person will "
//         "use this computer, you can create multiple "
//         "accounts after installation.</small>" ) );
//     }
    // Re-do password checks (with output messages) as well.
    // .. the password-checking methods get their values from the text boxes,
    //    not from their parameters.
    onPasswordTextChanged( m_userPassword, m_userPassword );
    onRootPasswordTextChanged( m_rootPassword, m_rootVerifiedPassword );
}


bool
Config::isReady()
{
    bool readyFields = m_readyFullName && m_readyHostname && m_readyPassword && m_readyUsername;
    if ( !m_writeRootPassword || m_reusePassword )
    {
        return readyFields;
    }

    return readyFields && m_readyRootPassword;
}


QList< Calamares::job_ptr >
Config::createJobs( const QStringList& defaultGroupsList )
{
    QList< Calamares::job_ptr > list;
    if ( !isReady() )
    {
        return list;
    }

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    Calamares::Job* j;
    j = new CreateUserJob( m_userName,
                          m_fullName.isEmpty() ? m_userName
                           :m_fullName,
                           m_autologin,
                           defaultGroupsList );
    list.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( m_userName, m_userPassword );
    list.append( Calamares::job_ptr( j ) );

    if ( m_writeRootPassword )
    {
        gs->insert( "reuseRootPassword", m_reusePassword );
        if ( m_reusePassword )
        {
            j = new SetPasswordJob( "root", m_userPassword );
        }
        else
        {
            j = new SetPasswordJob( "root", m_rootPassword );
        }
        list.append( Calamares::job_ptr( j ) );
    }
    else
    {
        j = new SetPasswordJob( "root",
                                "" );  //explicitly disable root password
        list.append( Calamares::job_ptr( j ) );
    }

    j = new SetHostNameJob( m_hostName );
    list.append( Calamares::job_ptr( j ) );

    gs->insert( "hostname",m_hostName );
    if ( m_autologin )
    {
        gs->insert( "autologinUser", m_userName );
    }

    gs->insert( "username", m_userName );
    gs->insert( "password", CalamaresUtils::obscure( m_userPassword ) );

    return list;
}


void
Config::onActivate()
{
    onPasswordTextChanged( m_userPassword, m_userPassword );
    onRootPasswordTextChanged( m_rootPassword, m_rootVerifiedPassword );
}

void
Config::setWriteRootPassword( bool write )
{
    m_reusePasswordVisible = write;
    m_writeRootPassword = write;

    emit reusePasswordVisibleChanged();
}

void
Config::onFullNameTextEdited( const QString& textRef )
{
    if ( textRef.isEmpty() )
    {
        m_fullName.clear();
        if ( !m_customUsername )
        {
           m_userName.clear();
        }
        if ( !m_customHostname )
        {
            m_hostName.clear();
        }
        m_readyFullName = false;
    }
    else
    {
        m_fullName = textRef;
        m_readyFullName = true;
        fillSuggestions();
    }

    emit fullNameReadyChanged();
    checkReady( isReady() );
}

void
Config::fillSuggestions()
{
    QString fullName = m_fullName;
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
                m_userName = usernameSuggestion;
                emit userNameChanged();
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
                m_hostName = hostnameSuggestion;
                emit hostNameChanged();
                validateHostnameText( hostnameSuggestion );
                m_customHostname = false;
            }
        }
    }
}

void
Config::onUsernameTextEdited( const QString& textRef )
{
    m_userName = textRef;
    m_customUsername = !textRef.isEmpty();
    validateUsernameText( textRef );
}

void
Config::validateUsernameText( const QString& textRef )
{
    QString text( textRef );
    QRegExpValidator val_whole( USERNAME_RX );
    QRegExpValidator val_start( QRegExp( "[a-z_].*" ) );  // anchors are implicit in QRegExpValidator
    int pos = -1;

    if ( text.isEmpty() )
    {
        m_readyUsername = false;
    }
    else if ( text.length() > USERNAME_MAX_LENGTH )
    {
        labelError( tr( "Your username is too long." ) );
        m_readyUsername = false;
    }
    else if ( val_start.validate( text, pos ) == QValidator::Invalid )
    {
        labelError( tr( "Your username must start with a lowercase letter or underscore." ) );
        m_readyUsername = false;
    }
    else if ( val_whole.validate( text, pos ) == QValidator::Invalid )
    {
        labelError( tr( "Only lowercase letters, numbers, underscore and hyphen are allowed." ) );
        m_readyUsername = false;
    }
    else
    {
        labelOk( );
        m_readyUsername = true;
    }

    emit userNameReadyChanged();
    emit checkReady( isReady() );
}


void
Config::onHostnameTextEdited( const QString& textRef )
{
    m_hostName = textRef;
    m_customHostname = true;
    validateHostnameText( textRef );
}

void
Config::validateHostnameText( const QString& textRef )
{
    QString text = textRef;
    QRegExpValidator val( HOSTNAME_RX );
    int pos = -1;

    if ( text.isEmpty() )
    {
        m_readyHostname = false;
    }
    else if ( text.length() < HOSTNAME_MIN_LENGTH )
    {
        labelError( tr( "Your hostname is too short." ) );
        m_readyHostname = false;
    }
    else if ( text.length() > HOSTNAME_MAX_LENGTH )
    {
        labelError( tr( "Your hostname is too long." ) );
        m_readyHostname = false;
    }
    else if ( val.validate( text, pos ) == QValidator::Invalid )
    {
        labelError( tr( "Only letters, numbers, underscore and hyphen are allowed." ) );
        m_readyHostname = false;
    }
    else
    {
        labelOk( );
        m_readyHostname = true;
    }

    emit hostNameReadyChanged();
    emit checkReady( isReady() );
}

bool
Config::checkPasswordAcceptance( const QString& pw1, const QString& pw2 )
{
    if ( pw1 != pw2 )
    {
        labelError( tr( "Your passwords do not match!" ) );
        return false;
    }
    else
    {
        bool failureIsFatal = m_validatePasswords;
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
                labelError( s, failureIsFatal ? Status::Fatal : Status::Warning );
                failureFound = true;
                if ( failureIsFatal )
                {
                    return false;
                }
            }
        }

        if ( !failureFound )
        {
            labelOk( );
        }

        // Here, if failureFound is true then we've found **warnings**,
        // which is ok to continue but the user should know.
        return true;
    }
}

void
Config::onPasswordTextChanged( const QString& textRef, const QString& textRefV )
{
    m_userPassword = textRef;
    m_userVerifiedPassword = textRefV;

    m_readyPassword = checkPasswordAcceptance(m_userPassword,
                                               m_userVerifiedPassword);

    emit passwordReadyChanged();
    emit checkReady( isReady() );
}

void
Config::onRootPasswordTextChanged( const QString& textRef, const QString& textRefV )
{
    m_rootPassword = textRef;
    m_rootVerifiedPassword = textRefV;

    m_readyRootPassword = checkPasswordAcceptance( m_rootPassword,
                                                   m_rootVerifiedPassword);

    emit rootPasswordReadyChanged();
    emit checkReady( isReady() );
}


void
Config::setPasswordCheckboxVisible( bool visible )
{
    m_validatePasswordsVisible = visible;
    emit validatePasswordsVisibleChanged();
}

void
Config::setValidatePasswordDefault( bool checked )
{
    if(checked == m_validatePasswords)
        return;

    m_validatePasswords = checked;
    emit validatePasswordsChanged();

    onPasswordTextChanged( m_userPassword, m_userVerifiedPassword );
    onRootPasswordTextChanged( m_rootPassword, m_rootVerifiedPassword );

    emit checkReady( isReady() );
}

void
Config::setAutologinDefault( bool checked )
{
    m_autologin = checked;
    emit autologinChanged();
    emit checkReady( isReady() );
}

void
Config::setReusePasswordDefault( bool checked )
{
    if(checked == m_reusePassword)
        return;

    m_reusePassword = checked;
    emit reusePasswordChanged();
    emit checkReady( isReady() );
}

void
Config::addPasswordCheck( const QString& key, const QVariant& value )
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
            m_passwordChecks.push_back( PasswordCheck(
                []() { return QCoreApplication::translate( "PWQ", "Password is empty" ); },
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



