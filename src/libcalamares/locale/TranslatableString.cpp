/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
