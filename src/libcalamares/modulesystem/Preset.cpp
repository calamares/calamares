/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Preset.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

static void
loadPresets( Calamares::ModuleSystem::Presets& preset,
             const QVariantMap& configurationMap,
             std::function< bool( const QString& ) > pred )
{
    cDebug() << "Creating presets" << preset.capacity();
    for ( auto it = configurationMap.cbegin(); it != configurationMap.cend(); ++it )
    {
        if ( !it.key().isEmpty() && pred( it.key() ) )
        {
            QVariantMap m = it.value().toMap();
            QString value = CalamaresUtils::getString( m, "value" );
            bool editable = CalamaresUtils::getBool( m, "editable", true );

            preset.append( Calamares::ModuleSystem::PresetField { it.key(), value, editable } );

            cDebug() << Logger::SubEntry << "Preset for" << it.key() << "applied editable?" << editable;
        }
    }
}

Calamares::ModuleSystem::Presets::Presets( const QVariantMap& configurationMap )


{
    reserve( configurationMap.count() );
    loadPresets( *this, configurationMap, []( const QString& ) { return true; } );
}

Calamares::ModuleSystem::Presets::Presets( const QVariantMap& configurationMap, const QStringList& recognizedKeys )
{
    reserve( recognizedKeys.size() );
    loadPresets(
        *this, configurationMap, [&recognizedKeys]( const QString& s ) { return recognizedKeys.contains( s ); } );
}
