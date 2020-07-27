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
setGS( const QString& key, const QString& group )
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
    setGS( QStringLiteral( "autologinGroup" ), group );
    emit autologinGroupChanged( group );
}

void
Config::setSudoersGroup( const QString& group )
{
    setGS( QStringLiteral( "sudoersGroup" ), group );
    emit sudoersGroupChanged( group );
}


void
Config::setLoginName( const QString& login )
{
    if ( login != m_loginName )
    {
        m_customLoginName = !login.isEmpty();
        m_loginName = login;
        emit loginNameChanged( login );
    }
}

void
Config::setHostName( const QString& host )
{
    if ( host != m_hostName )
    {
        m_customHostName = !host.isEmpty();
        m_hostName = host;
        emit hostNameChanged( host );
    }
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

static QString
makeLoginNameSuggestion( const QStringList& parts )
{
    static const QRegExp USERNAME_RX( "^[a-z_][a-z0-9_-]*[$]?$" );
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
            }
        }
        if ( !m_customHostName )
        {
            QString hostname = makeHostnameSuggestion( cleanParts );
            if ( !hostname.isEmpty() && hostname != m_hostName )
            {
                m_hostName = hostname;
                emit hostNameChanged( hostname );
            }
        }
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
}
