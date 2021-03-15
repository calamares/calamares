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
#include "utils/Logger.h"
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
    else
    {
        cWarning() << "Checking isEditable, but no presets are configured.";
    }
    return true;
}

Config::ApplyPresets::ApplyPresets( Calamares::ModuleSystem::Config& c, const QVariantMap& configurationMap )
    : m_c( c )
    , m_bogus( true )
    , m_map( CalamaresUtils::getSubMap( configurationMap, "presets", m_bogus ) )
{
    c.m_unlocked = true;
    if ( !c.d->m_presets )
    {
        c.d->m_presets = std::make_unique< Presets >();
    }
}

Config::ApplyPresets::~ApplyPresets()
{
    m_c.m_unlocked = false;

    // Check that there's no **settings** (from the configuration map)
    // that have not been consumed by apply() -- if they are there,
    // that means the configuration map specifies things that the
    // Config object does not expect.
    bool haveWarned = false;
    for ( const auto& k : m_map.keys() )
    {
        if ( !m_c.d->m_presets->find( k ).isValid() )
        {
            if ( !haveWarned )
            {
                cWarning() << "Preset configuration contains unused keys";
                haveWarned = true;
            }
            cDebug() << Logger::SubEntry << "Unused key" << k;
        }
    }
}

Config::ApplyPresets&
Config::ApplyPresets::apply( const char* fieldName )
{
    const auto prop = m_c.property( fieldName );
    if ( !prop.isValid() )
    {
        cWarning() << "Applying invalid property" << fieldName;
        return *this;
    }

    const QString key( fieldName );
    if ( key.isEmpty() )
    {
        cWarning() << "Applying empty field";
        return *this;
    }

    if ( m_c.d->m_presets->find( key ).isValid() )
    {
        cWarning() << "Applying duplicate property" << fieldName;
        return *this;
    }

    if ( m_map.contains( key ) )
    {
        // Key has an explicit setting
        QVariantMap m = CalamaresUtils::getSubMap( m_map, key, m_bogus );
        QVariant value = m[ "value" ];
        bool editable = CalamaresUtils::getBool( m, "editable", true );

        if ( value.isValid() )
        {
            m_c.setProperty( fieldName, value );
        }
        m_c.d->m_presets->append( PresetField { key, value, editable } );
    }
    else
    {
        // There is no setting, but since we apply() this field,
        // we do know about it; put in a preset so that looking
        // it up won't complani.
        m_c.d->m_presets->append( PresetField { key, QVariant(), true } );
    }
    return *this;
}

}  // namespace ModuleSystem
}  // namespace Calamares
