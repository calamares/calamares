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

const NamedEnumTable< Config::InstallChoice >&
Config::installChoiceNames()
{
    static const NamedEnumTable< InstallChoice > names { { QStringLiteral( "none" ), InstallChoice::NoChoice },
                                                         { QStringLiteral( "nochoice" ), InstallChoice::NoChoice },
                                                         { QStringLiteral( "alongside" ), InstallChoice::Alongside },
                                                         { QStringLiteral( "erase" ), InstallChoice::Erase },
                                                         { QStringLiteral( "replace" ), InstallChoice::Replace },
                                                         { QStringLiteral( "manual" ), InstallChoice::Manual } };
    return names;
}

const NamedEnumTable< Config::SwapChoice >&
Config::swapChoiceNames()
{
    static const NamedEnumTable< SwapChoice > names { { QStringLiteral( "none" ), SwapChoice::NoSwap },
                                                      { QStringLiteral( "small" ), SwapChoice::SmallSwap },
                                                      { QStringLiteral( "suspend" ), SwapChoice::FullSwap },
                                                      { QStringLiteral( "reuse" ), SwapChoice::ReuseSwap },
                                                      { QStringLiteral( "file" ), SwapChoice::SwapFile } };

    return names;
}

Config::SwapChoice
pickOne( const Config::SwapChoiceSet& s )
{
    if ( s.count() == 0 )
    {
        return Config::SwapChoice::NoSwap;
    }
    if ( s.count() == 1 )
    {
        return *( s.begin() );
    }
    if ( s.contains( Config::SwapChoice::NoSwap ) )
    {
        return Config::SwapChoice::NoSwap;
    }
    // Here, count > 1 but NoSwap is not a member.
    return *( s.begin() );
}


static Config::SwapChoiceSet
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

    Config::SwapChoiceSet choices;  // Available swap choices
    if ( configurationMap.contains( "userSwapChoices" ) )
    {
        // We've already warned about overlapping settings with the
        // legacy *ensureSuspendToDisk* and *neverCreateSwap*.
        QStringList l = configurationMap[ "userSwapChoices" ].toStringList();

        for ( const auto& item : l )
        {
            bool ok = false;
            auto v = Config::swapChoiceNames().find( item, ok );
            if ( ok )
            {
                choices.insert( v );
            }
        }

        if ( choices.isEmpty() )
        {
            cWarning() << "Partition-module configuration for *userSwapChoices* is empty:" << l;
            choices.insert( Config::SwapChoice::FullSwap );
        }

        // suspend if it's one of the possible choices; suppress swap only if it's
        // the **only** choice available.
        ensureSuspendToDisk = choices.contains( Config::SwapChoice::FullSwap );
        neverCreateSwap = ( choices.count() == 1 ) && choices.contains( Config::SwapChoice::NoSwap );
    }
    else
    {
        // Convert the legacy settings into a single setting for now.
        if ( neverCreateSwap )
        {
            choices.insert( Config::SwapChoice::NoSwap );
        }
        else if ( ensureSuspendToDisk )
        {
            choices.insert( Config::SwapChoice::FullSwap );
        }
        else
        {
            choices.insert( Config::SwapChoice::SmallSwap );
        }
    }

    // Not all are supported right now // FIXME
    static const char unsupportedSetting[] = "Partition-module does not support *userSwapChoices* setting";

#define COMPLAIN_UNSUPPORTED( x ) \
    if ( choices.contains( x ) ) \
    { \
        bool bogus = false; \
        cWarning() << unsupportedSetting << Config::swapChoiceNames().find( x, bogus ); \
        choices.remove( x ); \
    }

    COMPLAIN_UNSUPPORTED( Config::SwapChoice::ReuseSwap )
#undef COMPLAIN_UNSUPPORTED

    return choices;
}

void
updateGlobalStorage( Config::InstallChoice installChoice, Config::SwapChoice swapChoice )
{
    auto* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( gs )
    {
        QVariantMap m;
        m.insert( "install", Config::installChoiceNames().find( installChoice ) );
        m.insert( "swap", Config::swapChoiceNames().find( swapChoice ) );
        gs->insert( "partitionChoices", m );
    }
}

void
Config::setInstallChoice( int c )
{
    if ( ( c < InstallChoice::NoChoice ) || ( c > InstallChoice::Manual ) )
    {
        cWarning() << "Invalid install choice (int)" << c;
        c = InstallChoice::NoChoice;
    }
    setInstallChoice( static_cast< InstallChoice >( c ) );
}

void
Config::setInstallChoice( InstallChoice c )
{
    if ( c != m_installChoice )
    {
        m_installChoice = c;
        emit installChoiceChanged( c );
        ::updateGlobalStorage( c, m_swapChoice );
    }
}

void
Config::setSwapChoice( int c )
{
    if ( ( c < SwapChoice::NoSwap ) || ( c > SwapChoice::SwapFile ) )
    {
        cWarning() << "Invalid swap choice (int)" << c;
        c = SwapChoice::NoSwap;
    }
    setSwapChoice( static_cast< SwapChoice >( c ) );
}

void
Config::setSwapChoice( Config::SwapChoice c )
{
    if ( c != m_swapChoice )
    {
        m_swapChoice = c;
        emit swapChoiceChanged( c );
        ::updateGlobalStorage( m_installChoice, c );
    }
}

bool
Config::allowManualPartitioning() const
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    return gs->value( "allowManualPartitioning" ).toBool();
}


void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    // Settings that overlap with the Welcome module
    m_requiredStorageGiB = CalamaresUtils::getDouble( configurationMap, "requiredStorage", -1.0 );
    m_swapChoices = getSwapChoices( configurationMap );

    bool nameFound = false;  // In the name table (ignored, falls back to first entry in table)
    m_initialInstallChoice = installChoiceNames().find(
        CalamaresUtils::getString( configurationMap, "initialPartitioningChoice" ), nameFound );
    setInstallChoice( m_initialInstallChoice );

    m_initialSwapChoice
        = swapChoiceNames().find( CalamaresUtils::getString( configurationMap, "initialSwapChoice" ), nameFound );
    if ( !m_swapChoices.contains( m_initialSwapChoice ) )
    {
        cWarning() << "Configuration for *initialSwapChoice* is not one of the *userSwapChoices*";
        m_initialSwapChoice = pickOne( m_swapChoices );
    }
    setSwapChoice( m_initialSwapChoice );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    gs->insert( "allowManualPartitioning",
                CalamaresUtils::getBool( configurationMap, "allowManualPartitioning", true ) );

    if ( configurationMap.contains( "requiredPartitionTableType" )
         && configurationMap.value( "requiredPartitionTableType" ).type() == QVariant::List )
    {
        m_requiredPartitionTableType.clear();
        m_requiredPartitionTableType.append( configurationMap.value( "requiredPartitionTableType" ).toStringList() );
    }
    else if ( configurationMap.contains( "requiredPartitionTableType" )
              && configurationMap.value( "requiredPartitionTableType" ).type() == QVariant::String )
    {
        m_requiredPartitionTableType.clear();
        m_requiredPartitionTableType.append( configurationMap.value( "requiredPartitionTableType" ).toString() );
    }
    gs->insert( "requiredPartitionTableType", m_requiredPartitionTableType );
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
