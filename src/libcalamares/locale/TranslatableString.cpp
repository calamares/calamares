/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
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
 *
 */
#include "TranslatableString.h"


/** @brief Massage an identifier into a human-readable form
 *
 * Makes a copy of @p s, caller must free() it.
 */
static char*
munge( const char* s )
{
    char* t = strdup( s );
    if ( !t )
    {
        return nullptr;
    }

    // replace("_"," ") in the Python script
    char* p = t;
    while ( *p )
    {
        if ( ( *p ) == '_' )
        {
            *p = ' ';
        }
        ++p;
    }

    return t;
}

namespace CalamaresUtils
{
namespace Locale
{

TranslatableString::TranslatableString( TranslatableString&& t )
    : m_human( nullptr )
    , m_key()
{
    // My pointers are initialized to nullptr
    std::swap( m_human, t.m_human );
    std::swap( m_key, t.m_key );
}

TranslatableString::TranslatableString( const TranslatableString& t )
    : m_human( t.m_human ? strdup( t.m_human ) : nullptr )
    , m_key( t.m_key )
{
}

TranslatableString::TranslatableString( const char* s1 )
    : m_human( s1 ? munge( s1 ) : nullptr )
    , m_key( s1 ? QString( s1 ) : QString() )
{
}

TranslatableString::TranslatableString( const QString& s )
    : m_human( munge( s.toUtf8().constData() ) )
    , m_key( s )
{
}


TranslatableString::~TranslatableString()
{
    free( m_human );
}

}  // namespace Locale
}  // namespace CalamaresUtils
