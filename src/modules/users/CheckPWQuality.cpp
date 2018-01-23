/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "CheckPWQuality.h"

#include "utils/Logger.h"

#include <QWidget>

PasswordCheck::PasswordCheck()
    : m_message()
    , m_accept( []( const QString& s ){ return true; } )
{
}

PasswordCheck::PasswordCheck( const QString& m, AcceptFunc a )
    : m_message( [m](){ return m; } )
    , m_accept( a )
{
}

PasswordCheck::PasswordCheck( MessageFunc m, AcceptFunc a )
    : m_message( m )
    , m_accept( a )
{
}

// Try to trick Transifex into accepting these strings
#define tr parent->tr

DEFINE_CHECK_FUNC(minLength)
{
    int minLength = -1;
    if ( value.canConvert( QVariant::Int ) )
        minLength = value.toInt();
    if ( minLength > 0 )
    {
        cDebug() << " .. minLength set to" << minLength;
        checks.push_back(
            PasswordCheck(
                [parent]()
                {
                    return tr( "Password is too short" );
                },
                [minLength]( const QString& s )
                {
                    return s.length() >= minLength;
                }
            ) );
    }
}

DEFINE_CHECK_FUNC(maxLength)
{
    int maxLength = -1;
    if ( value.canConvert( QVariant::Int ) )
        maxLength = value.toInt();
    if ( maxLength > 0 )
    {
        cDebug() << " .. maxLength set to" << maxLength;
        checks.push_back(
            PasswordCheck(
                [parent]()
                {
                    return tr( "Password is too long" );
                }, [maxLength]( const QString& s )
                {
                    return s.length() <= maxLength;
                }
            ) );
    }
}

#ifdef HAVE_LIBPWQUALITY
DEFINE_CHECK_FUNC(libpwquality)
{
    if ( !value.canConvert( QVariant::List ) )
    {
        cDebug() << "WARNING: libpwquality settings is not a list";
        return;
    }

    QVariantList l = value.toList();
    unsigned int requirement_count = 0;
    for ( const auto& v : l )
    {
        cDebug() << " .. " << v.type() << v;
        // TODO: pass strings on to libpwquality
    }
}
#endif
