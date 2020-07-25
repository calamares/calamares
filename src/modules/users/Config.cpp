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
#include "utils/Variant.h"

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
        m_loginName = login;
        emit loginNameChanged( login );
    }
}

void
Config::setUserName( const QString& name )
{
    if ( name != m_fullName )
    {
        m_fullName = name;
        emit userNameChanged( name );
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
