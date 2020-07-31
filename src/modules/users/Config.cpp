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

#include <QFile>
#include <QRegExp>

static const QRegExp USERNAME_RX( "^[a-z_][a-z0-9_-]*[$]?$" );
static constexpr const int USERNAME_MAX_LENGTH = 31;

static const QRegExp HOSTNAME_RX( "^[a-zA-Z0-9][-a-zA-Z0-9_]*$" );
static constexpr const int HOSTNAME_MIN_LENGTH = 2;
static constexpr const int HOSTNAME_MAX_LENGTH = 63;

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

    setConfigurationDefaultGroups( configurationMap, m_defaultGroups );
    m_doAutoLogin = CalamaresUtils::getBool( configurationMap, "doAutologin", false );

    m_writeRootPassword = CalamaresUtils::getBool( configurationMap, "setRootPassword", true );
    Calamares::JobQueue::instance()->globalStorage()->insert( "setRootPassword", m_writeRootPassword );
}
