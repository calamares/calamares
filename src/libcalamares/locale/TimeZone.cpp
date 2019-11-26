/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "TimeZone.h"

#include <cstring>

namespace CalamaresUtils
{
namespace Locale
{


CStringPair::CStringPair( CStringPair&& t )
{
    // My pointers are initialized to nullptr
    std::swap( m_human, t.m_human );
    std::swap( m_key, t.m_key );
}

CStringPair::CStringPair( const CStringPair& t )
    : m_human( t.m_human ? strdup( t.m_human ) : nullptr )
    , m_key( t.m_key ? strdup( t.m_key ) : nullptr )
{
}

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

CStringPair::CStringPair( const char* s1 )
    : m_human( s1 ? munge( s1 ) : nullptr )
    , m_key( s1 ? strdup( s1 ) : nullptr )
{
}


CStringPair::~CStringPair()
{
    free( m_human );
    free( m_key );
}

}  // namespace Locale
}  // namespace CalamaresUtils
