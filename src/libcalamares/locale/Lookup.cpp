/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Lookup.h"

#include "CountryData_p.cpp"

namespace CalamaresUtils
{
namespace Locale
{

struct TwoChar
{
    TwoChar( const QString& code )
        : cc1( 0 )
        , cc2( 0 )
    {
        if ( code.length() == 2 )
        {
            cc1 = code[ 0 ].toLatin1();
            cc2 = code[ 1 ].toLatin1();
        }
    }

    char cc1;
    char cc2;
};

static const CountryData*
lookup( TwoChar c )
{
    if ( !c.cc1 )
    {
        return nullptr;
    }

    const CountryData* p
        = std::find_if( country_data_table,
                        country_data_table + country_data_size,
                        [ c = c ]( const CountryData& d ) { return ( d.cc1 == c.cc1 ) && ( d.cc2 == c.cc2 ); } );
    if ( p == country_data_table + country_data_size )
    {
        return nullptr;
    }
    return p;
}

QLocale::Country
countryForCode( const QString& code )
{
    const CountryData* p = lookup( TwoChar( code ) );
    return p ? p->c : QLocale::Country::AnyCountry;
}

QLocale::Language
languageForCountry( const QString& code )
{
    const CountryData* p = lookup( TwoChar( code ) );
    return p ? p->l : QLocale::Language::AnyLanguage;
}

QPair< QLocale::Country, QLocale::Language >
countryData( const QString& code )
{
    const CountryData* p = lookup( TwoChar( code ) );
    return p ? qMakePair( p->c, p->l ) : qMakePair( QLocale::Country::AnyCountry, QLocale::Language::AnyLanguage );
}

QLocale
countryLocale( const QString& code )
{
    auto p = countryData( code );
    return QLocale( p.second, p.first );
}

QLocale::Language
languageForCountry( QLocale::Country country )
{
    const CountryData* p = std::find_if( country_data_table,
                                         country_data_table + country_data_size,
                                         [ c = country ]( const CountryData& d ) { return d.c == c; } );
    if ( p == country_data_table + country_data_size )
    {
        return QLocale::Language::AnyLanguage;
    }
    return p->l;
}

}  // namespace Locale
}  // namespace CalamaresUtils
