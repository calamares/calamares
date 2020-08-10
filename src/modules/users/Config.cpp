/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
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

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/String.h"
#include "utils/Variant.h"

#include <QCoreApplication>
#include <QFile>
#include <QRegExp>

static const QRegExp USERNAME_RX( "^[a-z_][a-z0-9_-]*[$]?$" );
static constexpr const int USERNAME_MAX_LENGTH = 31;

static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
static constexpr const int HOSTNAME_MIN_LENGTH = 2;
static constexpr const int HOSTNAME_MAX_LENGTH = 63;

const NamedEnumTable< HostNameAction >&
hostNameActionNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< HostNameAction > names {
        { QStringLiteral( "none" ), HostNameAction::None },
        { QStringLiteral( "etcfile" ), HostNameAction::EtcHostname },
        { QStringLiteral( "hostnamed" ), HostNameAction::SystemdHostname }
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

Config::Config( QObject* parent )
    : QObject( parent )
{
}

Config::~Config() {}

void
Config::setUserShell( const QString& shell )
{
    if ( !shell.isEmpty() && !shell.startsWith( '/' ) )
    {
        cWarning() << "User shell" << shell << "is not an absolute path.";
        return;
    }
    // The shell is put into GS because the CreateUser job expects it there
    Calamares::JobQueue::instance()->globalStorage()->insert( "userShell", shell );
}

static inline void
insertInGlobalStorage( const QString& key, const QString& group )
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs || group.isEmpty() )
    {
        return;
    }
    gs->insert( key, group );
}

void
Config::setAutologinGroup( const QString& group )
{
    insertInGlobalStorage( QStringLiteral( "autologinGroup" ), group );
    emit autologinGroupChanged( group );
}

void
Config::setSudoersGroup( const QString& group )
{
    insertInGlobalStorage( QStringLiteral( "sudoersGroup" ), group );
    emit sudoersGroupChanged( group );
}


void
Config::setLoginName( const QString& login )
{
    if ( login != m_loginName )
    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( login.isEmpty() )
        {
            gs->remove( "username" );
        }
        else
        {
            gs->insert( "username", login );
        }

        m_customLoginName = !login.isEmpty();
        m_loginName = login;
        emit loginNameChanged( login );
        emit loginNameStatusChanged( loginNameStatus() );
    }
}

const QStringList&
Config::forbiddenLoginNames()
{
    static QStringList forbidden { "root" };
    return forbidden;
}

QString
Config::loginNameStatus() const
{
    // An empty login is "ok", even if it isn't really
    if ( m_loginName.isEmpty() )
    {
        return QString();
    }

    if ( m_loginName.length() > USERNAME_MAX_LENGTH )
    {
        return tr( "Your username is too long." );
    }
    for ( const QString& badName : forbiddenLoginNames() )
    {
        if ( 0 == QString::compare( badName, m_loginName, Qt::CaseSensitive ) )
        {
            return tr( "'%1' is not allowed as username." ).arg( badName );
        }
    }

    QRegExp validateFirstLetter( "^[a-z_]" );
    if ( validateFirstLetter.indexIn( m_loginName ) != 0 )
    {
        return tr( "Your username must start with a lowercase letter or underscore." );
    }
    if ( !USERNAME_RX.exactMatch( m_loginName ) )
    {
        return tr( "Only lowercase letters, numbers, underscore and hyphen are allowed." );
    }

    return QString();
}

void
Config::setHostName( const QString& host )
{
    if ( host != m_hostName )
    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( host.isEmpty() )
        {
            gs->remove( "hostname" );
        }
        else
        {
            gs->insert( "hostname", host );
        }

        m_customHostName = !host.isEmpty();
        m_hostName = host;
        emit hostNameChanged( host );
        emit hostNameStatusChanged( hostNameStatus() );
    }
}

const QStringList&
Config::forbiddenHostNames()
{
    static QStringList forbidden { "localhost" };
    return forbidden;
}

QString
Config::hostNameStatus() const
{
    // An empty hostname is "ok", even if it isn't really
    if ( m_hostName.isEmpty() )
    {
        return QString();
    }

    if ( m_hostName.length() < HOSTNAME_MIN_LENGTH )
    {
        return tr( "Your hostname is too short." );
    }
    if ( m_hostName.length() > HOSTNAME_MAX_LENGTH )
    {
        return tr( "Your hostname is too long." );
    }
    for ( const QString& badName : forbiddenHostNames() )
    {
        if ( 0 == QString::compare( badName, m_hostName, Qt::CaseSensitive ) )
        {
            return tr( "'%1' is not allowed as hostname." ).arg( badName );
        }
    }

    if ( !HOSTNAME_RX.exactMatch( m_hostName ) )
    {
        return tr( "Only letters, numbers, underscore and hyphen are allowed." );
    }

    return QString();
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
            dmiProduct = QStringLiteral( "pc" );
        }
        tried = true;
    }
    return dmiProduct;
}

static QString
makeLoginNameSuggestion( const QStringList& parts )
{
    if ( parts.isEmpty() || parts.first().isEmpty() )
    {
        return QString();
    }

    QString usernameSuggestion = parts.first();
    for ( int i = 1; i < parts.length(); ++i )
    {
        if ( !parts.value( i ).isEmpty() )
        {
            usernameSuggestion.append( parts.value( i ).at( 0 ) );
        }
    }

    return USERNAME_RX.indexIn( usernameSuggestion ) != -1 ? usernameSuggestion : QString();
}

static QString
makeHostnameSuggestion( const QStringList& parts )
{
    static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
    if ( parts.isEmpty() || parts.first().isEmpty() )
    {
        return QString();
    }

    QString productName = guessProductName();
    QString hostnameSuggestion = QStringLiteral( "%1-%2" ).arg( parts.first() ).arg( productName );
    return HOSTNAME_RX.indexIn( hostnameSuggestion ) != -1 ? hostnameSuggestion : QString();
}

void
Config::setFullName( const QString& name )
{
    if ( name.isEmpty() && !m_fullName.isEmpty() )
    {
        if ( !m_customHostName )
        {
            setHostName( name );
        }
        if ( !m_customLoginName )
        {
            setLoginName( name );
        }
        m_fullName = name;
        emit fullNameChanged( name );
    }

    if ( name != m_fullName )
    {
        m_fullName = name;
        emit fullNameChanged( name );

        // Build login and hostname, if needed
        QRegExp rx( "[^a-zA-Z0-9 ]", Qt::CaseInsensitive );
        QString cleanName = CalamaresUtils::removeDiacritics( name ).toLower().replace( rx, " " ).simplified();
        QStringList cleanParts = cleanName.split( ' ' );

        if ( !m_customLoginName )
        {
            QString login = makeLoginNameSuggestion( cleanParts );
            if ( !login.isEmpty() && login != m_loginName )
            {
                m_loginName = login;
                emit loginNameChanged( login );
                emit loginNameStatusChanged( loginNameStatus() );
            }
        }
        if ( !m_customHostName )
        {
            QString hostname = makeHostnameSuggestion( cleanParts );
            if ( !hostname.isEmpty() && hostname != m_hostName )
            {
                m_hostName = hostname;
                emit hostNameChanged( hostname );
                emit hostNameStatusChanged( hostNameStatus() );
            }
        }
    }
}

void
Config::setAutoLogin( bool b )
{
    if ( b != m_doAutoLogin )
    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( b )
        {
            gs->insert( "autologinUser", loginName() );
        }
        else
        {
            gs->remove( "autologinUser" );
        }
        m_doAutoLogin = b;
        emit autoLoginChanged( b );
    }
}

void
Config::setReuseUserPasswordForRoot( bool reuse )
{
    if ( reuse != m_reuseUserPasswordForRoot )
    {
        m_reuseUserPasswordForRoot = reuse;
        emit reuseUserPasswordForRootChanged( reuse );
    }
}

void
Config::setRequireStrongPasswords( bool strong )
{
    if ( strong != m_requireStrongPasswords )
    {
        m_requireStrongPasswords = strong;
        emit requireStrongPasswordsChanged( strong );
    }
}

bool
Config::isPasswordAcceptable( const QString& password, QString& message )
{
    bool failureIsFatal = requireStrongPasswords();

    for ( auto pc : m_passwordChecks )
    {
        QString s = pc.filter( password );

        if ( !s.isEmpty() )
        {
            message = s;
            return !failureIsFatal;
        }
    }

    return true;
}

void
Config::setUserPassword( const QString& s )
{
    m_userPassword = s;
    // TODO: check new password status
    emit userPasswordChanged( s );
}

void
Config::setUserPasswordSecondary( const QString& s )
{
    m_userPasswordSecondary = s;
    // TODO: check new password status
    emit userPasswordSecondaryChanged( s );
}

void
Config::setRootPassword( const QString& s )
{
    if ( writeRootPassword() )
    {
        m_rootPassword = s;
        // TODO: check new password status
        emit rootPasswordChanged( s );
    }
}

void
Config::setRootPasswordSecondary( const QString& s )
{
    if ( writeRootPassword() )
    {
        m_rootPasswordSecondary = s;
        // TODO: check new password status
        emit rootPasswordSecondaryChanged( s );
    }
}

QString Config::rootPassword() const
{
    if ( writeRootPassword() )
    {
        if ( reuseUserPasswordForRoot() )
            return userPassword();
        return m_rootPassword;
    }
    return QString();
}

QString Config::rootPasswordSecondary() const
{
    if ( writeRootPassword() )
    {
        if ( reuseUserPasswordForRoot() )
            return userPasswordSecondary();
        return m_rootPasswordSecondary;
    }
    return QString();
}


STATICTEST void
setConfigurationDefaultGroups( const QVariantMap& map, QStringList& defaultGroups )
{
    // '#' is not a valid group name; use that to distinguish an empty-list
    // in the configuration (which is a legitimate, if unusual, choice)
    // from a bad or missing configuration value.
    defaultGroups = CalamaresUtils::getStringList( map, QStringLiteral( "defaultGroups" ), QStringList { "#" } );
    if ( defaultGroups.contains( QStringLiteral( "#" ) ) )
    {
        cWarning() << "Using fallback groups. Please check *defaultGroups* in users.conf";
        defaultGroups = QStringList { "lp", "video", "network", "storage", "wheel", "audio" };
    }
}

STATICTEST HostNameActions
getHostNameActions( const QVariantMap& configurationMap )
{
    HostNameAction setHostName = HostNameAction::EtcHostname;
    QString hostnameActionString = CalamaresUtils::getString( configurationMap, "setHostname" );
    if ( !hostnameActionString.isEmpty() )
    {
        bool ok = false;
        setHostName = hostNameActionNames().find( hostnameActionString, ok );
        if ( !ok )
        {
            setHostName = HostNameAction::EtcHostname;  // Rather than none
        }
    }

    HostNameAction writeHosts = CalamaresUtils::getBool( configurationMap, "writeHostsFile", true )
        ? HostNameAction::WriteEtcHosts
        : HostNameAction::None;
    return setHostName | writeHosts;
}

/** @brief Process entries in the passwordRequirements config entry
 *
 * Called once for each item in the config entry, which should
 * be a key-value pair. What makes sense as a value depends on
 * the key. Supported keys are documented in users.conf.
 *
 * @return if the check was added, returns @c true
 */
STATICTEST bool
addPasswordCheck( const QString& key, const QVariant& value, PasswordCheckList& passwordChecks )
{
    if ( key == "minLength" )
    {
        add_check_minLength( passwordChecks, value );
    }
    else if ( key == "maxLength" )
    {
        add_check_maxLength( passwordChecks, value );
    }
    else if ( key == "nonempty" )
    {
        if ( value.toBool() )
        {
            passwordChecks.push_back(
                PasswordCheck( []() { return QCoreApplication::translate( "PWQ", "Password is empty" ); },
                               []( const QString& s ) { return !s.isEmpty(); },
                               PasswordCheck::Weight( 1 ) ) );
        }
        else
        {
            cDebug() << "nonempty check is mentioned but set to false";
            return false;
        }
    }
#ifdef CHECK_PWQUALITY
    else if ( key == "libpwquality" )
    {
        add_check_libpwquality( passwordChecks, value );
    }
#endif  // CHECK_PWQUALITY
    else
    {
        cWarning() << "Unknown password-check key" << key;
        return false;
    }
    return true;
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString shell( QLatin1String( "/bin/bash" ) );  // as if it's not set at all
    if ( configurationMap.contains( "userShell" ) )
    {
        shell = CalamaresUtils::getString( configurationMap, "userShell" );
    }
    // Now it might be explicitly set to empty, which is ok
    setUserShell( shell );

    setAutologinGroup( CalamaresUtils::getString( configurationMap, "autologinGroup" ) );
    setSudoersGroup( CalamaresUtils::getString( configurationMap, "sudoersGroup" ) );

    m_hostNameActions = getHostNameActions( configurationMap );

    setConfigurationDefaultGroups( configurationMap, m_defaultGroups );
    m_doAutoLogin = CalamaresUtils::getBool( configurationMap, "doAutologin", false );

    m_writeRootPassword = CalamaresUtils::getBool( configurationMap, "setRootPassword", true );
    Calamares::JobQueue::instance()->globalStorage()->insert( "setRootPassword", m_writeRootPassword );

    m_reuseUserPasswordForRoot = CalamaresUtils::getBool( configurationMap, "doReusePassword", false );

    m_permitWeakPasswords = CalamaresUtils::getBool( configurationMap, "allowWeakPasswords", false );
    m_requireStrongPasswords
        = !m_permitWeakPasswords || !CalamaresUtils::getBool( configurationMap, "allowWeakPasswordsDefault", false );

    // If the value doesn't exist, or isn't a map, this gives an empty map -- no problem
    auto pr_checks( configurationMap.value( "passwordRequirements" ).toMap() );
    for ( decltype( pr_checks )::const_iterator i = pr_checks.constBegin(); i != pr_checks.constEnd(); ++i )
    {
        addPasswordCheck( i.key(), i.value(), m_passwordChecks );
    }
    std::sort( m_passwordChecks.begin(), m_passwordChecks.end() );
}
