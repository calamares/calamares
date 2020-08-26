/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

Config::Config( QObject* parent )
    : QObject( parent )
{
}

static PartitionActions::Choices::SwapChoiceSet
getSwapChoices( const QVariantMap& configurationMap )
{
    // SWAP SETTINGS
    //
    // This is a bit convoluted because there's legacy settings to handle as well
    // as the new-style list of choices, with mapping back-and-forth.
    if ( configurationMap.contains( "userSwapChoices" )
         && ( configurationMap.contains( "ensureSuspendToDisk" ) || configurationMap.contains( "neverCreateSwap" ) ) )
    {
        cError() << "Partition-module configuration mixes old- and new-style swap settings.";
    }

    if ( configurationMap.contains( "ensureSuspendToDisk" ) )
    {
        cWarning() << "Partition-module setting *ensureSuspendToDisk* is deprecated.";
    }
    bool ensureSuspendToDisk = CalamaresUtils::getBool( configurationMap, "ensureSuspendToDisk", true );

    if ( configurationMap.contains( "neverCreateSwap" ) )
    {
        cWarning() << "Partition-module setting *neverCreateSwap* is deprecated.";
    }
    bool neverCreateSwap = CalamaresUtils::getBool( configurationMap, "neverCreateSwap", false );

    PartitionActions::Choices::SwapChoiceSet choices;  // Available swap choices
    if ( configurationMap.contains( "userSwapChoices" ) )
    {
        // We've already warned about overlapping settings with the
        // legacy *ensureSuspendToDisk* and *neverCreateSwap*.
        QStringList l = configurationMap[ "userSwapChoices" ].toStringList();

        for ( const auto& item : l )
        {
            bool ok = false;
            auto v = PartitionActions::Choices::swapChoiceNames().find( item, ok );
            if ( ok )
            {
                choices.insert( v );
            }
        }

        if ( choices.isEmpty() )
        {
            cWarning() << "Partition-module configuration for *userSwapChoices* is empty:" << l;
            choices.insert( PartitionActions::Choices::SwapChoice::FullSwap );
        }

        // suspend if it's one of the possible choices; suppress swap only if it's
        // the **only** choice available.
        ensureSuspendToDisk = choices.contains( PartitionActions::Choices::SwapChoice::FullSwap );
        neverCreateSwap = ( choices.count() == 1 ) && choices.contains( PartitionActions::Choices::SwapChoice::NoSwap );
    }
    else
    {
        // Convert the legacy settings into a single setting for now.
        if ( neverCreateSwap )
        {
            choices.insert( PartitionActions::Choices::SwapChoice::NoSwap );
        }
        else if ( ensureSuspendToDisk )
        {
            choices.insert( PartitionActions::Choices::SwapChoice::FullSwap );
        }
        else
        {
            choices.insert( PartitionActions::Choices::SwapChoice::SmallSwap );
        }
    }

    // Not all are supported right now // FIXME
    static const char unsupportedSetting[] = "Partition-module does not support *userSwapChoices* setting";

#define COMPLAIN_UNSUPPORTED( x ) \
    if ( choices.contains( x ) ) \
    { \
        bool bogus = false; \
        cWarning() << unsupportedSetting << PartitionActions::Choices::swapChoiceNames().find( x, bogus ); \
        choices.remove( x ); \
    }

    COMPLAIN_UNSUPPORTED( PartitionActions::Choices::SwapChoice::SwapFile )
    COMPLAIN_UNSUPPORTED( PartitionActions::Choices::SwapChoice::ReuseSwap )
#undef COMPLAIN_UNSUPPORTED

    return choices;
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    // Settings that overlap with the Welcome module
    m_requiredStorageGiB = CalamaresUtils::getDouble( configurationMap, "requiredStorage", -1.0 );
    m_swapChoices = getSwapChoices( configurationMap );

    bool nameFound = false;  // In the name table (ignored, falls back to first entry in table)
    m_initialInstallChoice = PartitionActions::Choices::installChoiceNames().find(
        CalamaresUtils::getString( configurationMap, "initialPartitioningChoice" ), nameFound );
}

void
Config::updateGlobalStorage() const
{
    // If there's no setting (e.g. from the welcome page) for required storage
    // then use ours, if it was set.
    auto* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( m_requiredStorageGiB >= 0.0 && gs && !gs->contains( "requiredStorageGiB" ) )
    {
        gs->insert( "requiredStorageGiB", m_requiredStorageGiB );
    }
}
