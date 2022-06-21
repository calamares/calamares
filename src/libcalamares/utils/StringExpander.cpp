/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "StringExpander.h"
#include "Logger.h"

namespace Calamares
{
namespace String
{

struct DictionaryExpander::Private
{
    QHash< QString, QString > dictionary;
    QStringList missing;
};

DictionaryExpander::DictionaryExpander()
    : KWordMacroExpander( '$' )
    , d( std::make_unique< Private >() )
{
}

DictionaryExpander::DictionaryExpander( Calamares::String::DictionaryExpander&& other )
    : KWordMacroExpander( other.escapeChar() )
    , d( std::move( other.d ) )
{
}


DictionaryExpander::~DictionaryExpander() {}


void
DictionaryExpander::insert( const QString& key, const QString& value )
{
    d->dictionary.insert( key, value );
}

void
DictionaryExpander::clearErrors()
{
    d->missing.clear();
}

bool
DictionaryExpander::hasErrors() const
{
    return !d->missing.isEmpty();
}

QStringList
DictionaryExpander::errorNames() const
{
    return d->missing;
}

QString
DictionaryExpander::expand( QString s )
{
    clearErrors();
    expandMacros( s );
    return s;
}

bool
DictionaryExpander::expandMacro( const QString& str, QStringList& ret )
{
    if ( d->dictionary.contains( str ) )
    {
        ret << d->dictionary[ str ];
        return true;
    }
    else
    {
        d->missing << str;
        return false;
    }
}

}  // namespace String
}  // namespace Calamares
