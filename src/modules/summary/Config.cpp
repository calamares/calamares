/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020, Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "SummaryModel.h"

#include "Branding.h"
#include "Settings.h"
#include "ViewManager.h"
#include "utils/Gui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "viewpages/ExecutionViewStep.h"

Config::Config( QObject* parent )
    : QObject( parent )
    , m_summary( new SummaryModel( this ) )

{
    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate );
    retranslate();
}

void
Config::retranslate()
{
    m_title = tr( "Summary", "@label" );

    if ( Calamares::Settings::instance()->isSetupMode() )
    {
        m_message = tr( "This is an overview of what will happen once you start "
                        "the setup procedure." );
    }
    else
    {
        m_message = tr( "This is an overview of what will happen once you start "
                        "the install procedure." );
    }
    Q_EMIT titleChanged( m_title );
    Q_EMIT messageChanged( m_message );
}

Calamares::ViewStepList
Config::stepsForSummary( const Calamares::ViewStep* upToHere )
{
    Calamares::ViewStepList steps;
    for ( Calamares::ViewStep* step : Calamares::ViewManager::instance()->viewSteps() )
    {
        // *Assume* that if there's an exec step in the sequence,
        // we don't need a summary for steps before it. This works in
        // practice if there's a summary step before each exec --
        // and in practice, there's only one of each.
        if ( qobject_cast< Calamares::ExecutionViewStep* >( step ) )
        {
            steps.clear();
            continue;
        }

        // Having reached the parent view-step of the Config object,
        // we know we're providing a summary of steps up until this
        // view step, so we now have steps since the previous exec, up
        // to this summary.
        if ( upToHere == step )
        {
            break;
        }

        steps.append( step );
    }
    return steps;
}


void
Config::collectSummaries( const Calamares::ViewStep* upToHere, Widgets withWidgets )
{
    m_summary->setSummaryList( stepsForSummary( upToHere ), withWidgets == Widgets::Enabled );
}

void
Config::clearSummaries()
{
    m_summary->setSummaryList( {}, false );
}
