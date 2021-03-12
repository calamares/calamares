/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "Preset.h"
#include "utils/Variant.h"

namespace Calamares
{
namespace ModuleSystem
{


class Config::Private
{
public:
    std::unique_ptr< Presets > m_presets;
};


Config::Config( QObject* parent )
    : QObject( parent )
    , d( std::make_unique< Private >() )
{
}

Config::~Config() {}

void
Config::loadPresets( const QVariantMap& configurationMap )
{
    const QString key( "presets" );
    if ( !configurationMap.contains( key ) )
    {
        d->m_presets.reset();
        return;
    }
    bool bogus = true;
    d->m_presets = std::make_unique< Presets >( CalamaresUtils::getSubMap( configurationMap, key, bogus ) );
}

void
Config::loadPresets( const QVariantMap& configurationMap, const QStringList& recognizedKeys )
{
    const QString key( "presets" );
    if ( !configurationMap.contains( key ) )
    {
        d->m_presets.reset();
        return;
    }
    bool bogus = true;
    d->m_presets
        = std::make_unique< Presets >( CalamaresUtils::getSubMap( configurationMap, key, bogus ), recognizedKeys );
}

bool
Config::isEditable( const QString& fieldName ) const
{
    if ( m_unlocked )
    {
        return true;
    }
    if ( d && d->m_presets )
    {
        return d->m_presets->isEditable( fieldName );
    }
    return true;
}


}  // namespace ModuleSystem
}  // namespace Calamares
