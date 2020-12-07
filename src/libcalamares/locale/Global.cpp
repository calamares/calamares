/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#include "Global.h"

#include "GlobalStorage.h"
#include "utils/Logger.h"

namespace CalamaresUtils
{
namespace Locale
{

static const char gsKey[] = "localeConf";

template < typename T >
void
insertGS( const QMap< QString, T >& values, QVariantMap& localeConf )
{
    for ( auto it = values.constBegin(); it != values.constEnd(); ++it )
    {
        localeConf.insert( it.key(), it.value() );
    }
}

void
insertGS( Calamares::GlobalStorage& gs, const QMap< QString, QString >& values, InsertMode mode )
{
    QVariantMap localeConf = mode == InsertMode::Overwrite ? QVariantMap() : gs.value( gsKey ).toMap();
    insertGS( values, localeConf );
    gs.insert( gsKey, localeConf );
}

void
insertGS( Calamares::GlobalStorage& gs, const QVariantMap& values, InsertMode mode )
{
    QVariantMap localeConf = mode == InsertMode::Overwrite ? QVariantMap() : gs.value( gsKey ).toMap();
    insertGS( values, localeConf );
    gs.insert( gsKey, localeConf );
}

void
insertGS( Calamares::GlobalStorage& gs, const QString& key, const QString& value )
{
    QVariantMap localeConf = gs.value( gsKey ).toMap();
    localeConf.insert( key, value );
    gs.insert( gsKey, localeConf );
}

void
removeGS( Calamares::GlobalStorage& gs, const QString& key )
{
    if ( gs.contains( gsKey ) )
    {
        QVariantMap localeConf = gs.value( gsKey ).toMap();
        if ( localeConf.contains( key ) )
        {
            localeConf.remove( key );
            gs.insert( gsKey, localeConf );
        }
    }
}

void
clearGS( Calamares::GlobalStorage& gs )
{
    gs.remove( gsKey );
}


}  // namespace Locale
}  // namespace CalamaresUtils
