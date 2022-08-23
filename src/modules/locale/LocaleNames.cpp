/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "LocaleNames.h"

#include "utils/Logger.h"

#include <QRegularExpression>

LocaleNameParts
LocaleNameParts::fromName( const QString& name )
{
    auto requireAndRemoveLeadingChar = []( QChar c, QString s )
    {
        if ( s.startsWith( c ) )
        {
            return s.remove( 0, 1 );
        }
        else
        {
            return QString();
        }
    };

    auto parts = QRegularExpression( "^([a-zA-Z]+)(_[a-zA-Z]+)?(\\.[-a-zA-Z0-9]+)?(@[a-zA-Z]+)?" ).match( name );
    const QString calamaresLanguage = parts.captured( 1 );
    const QString calamaresCountry = requireAndRemoveLeadingChar( '_', parts.captured( 2 ) );
    const QString calamaresEncoding = requireAndRemoveLeadingChar( '.', parts.captured( 3 ) );
    const QString calamaresRegion = requireAndRemoveLeadingChar( '@', parts.captured( 4 ) );

    if ( calamaresLanguage.isEmpty() )
    {
        return LocaleNameParts {};
    }
    else
    {
        return LocaleNameParts { calamaresLanguage, calamaresCountry, calamaresRegion, calamaresEncoding };
    }
}

QString
LocaleNameParts::name() const
{
    // We don't want QStringView to a temporary; force conversion
    auto insertLeadingChar = []( QChar c, QString s ) -> QString
    {
        if ( s.isEmpty() )
        {
            return QString();
        }
        else
        {
            return c + s;
        }
    };

    if ( !isValid() )
    {
        return QString();
    }
    else
    {
        return language + insertLeadingChar( '_', country ) + insertLeadingChar( '.', encoding )
            + insertLeadingChar( '@', region );
    }
}


int
LocaleNameParts::similarity( const LocaleNameParts& other ) const
{
    if ( !isValid() || !other.isValid() )
    {
        return 0;
    }
    if ( language != other.language )
    {
        return 0;
    }
    const auto matched_region = ( region == other.region ? 30 : 0 );
    const auto matched_country = ( country == other.country ? ( country.isEmpty() ? 10 : 20 ) : 0 );
    const auto no_other_country_given = ( ( country != other.country && other.country.isEmpty() ) ? 10 : 0 );
    return 50 + matched_region + matched_country + no_other_country_given;
}
