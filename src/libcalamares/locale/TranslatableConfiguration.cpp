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

#include "TranslatableConfiguration.h"

#include "LabelModel.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

namespace CalamaresUtils
{
namespace Locale
{
TranslatedString::TranslatedString( const QString& string )
{
    m_strings[ QString() ] = string;
}

TranslatedString::TranslatedString( const QVariantMap& map, const QString& key, const char* context )
    : m_context( context )
{
    // Get the un-decorated value for the key
    QString value = CalamaresUtils::getString( map, key );
    m_strings[ QString() ] = value;

    for ( auto it = map.constBegin(); it != map.constEnd(); ++it )
    {
        QString subkey = it.key();
        if ( subkey == key )
        {
            // Already obtained, above
        }
        else if ( subkey.startsWith( key ) )
        {
            QRegularExpressionMatch match;
            if ( subkey.indexOf( QRegularExpression( "\\[([a-zA-Z_@]*)\\]" ), 0, &match ) > 0 )
            {
                QString language = match.captured( 1 );
                m_strings[ language ] = it.value().toString();
            }
        }
    }
}

QString
TranslatedString::get() const
{
    return get( QLocale() );
}

QString
TranslatedString::get( const QLocale& locale ) const
{
    QString localeName = locale.name();
    // Special case, sr@latin doesn't have the @latin reflected in the name
    if ( locale.language() == QLocale::Language::Serbian && locale.script() == QLocale::Script::LatinScript )
    {
        localeName = QStringLiteral( "sr@latin" );
    }

    if ( m_strings.contains( localeName ) )
    {
        return m_strings[ localeName ];
    }
    int index = localeName.indexOf( '@' );
    if ( index > 0 )
    {
        localeName.truncate( index );
        if ( m_strings.contains( localeName ) )
        {
            return m_strings[ localeName ];
        }
    }

    index = localeName.indexOf( '_' );
    if ( index > 0 )
    {
        localeName.truncate( index );
        if ( m_strings.contains( localeName ) )
        {
            return m_strings[ localeName ];
        }
    }

    // If we're given a context to work with, also try the same string in
    // the regular translation framework.
    const QString& s = m_strings[ QString() ];
    if ( m_context )
    {
        return QCoreApplication::translate( m_context, s.toLatin1().constData() );
    }
    else
    {
        return s;
    }
}


}  // namespace Locale
}  // namespace CalamaresUtils
