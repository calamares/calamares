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

#include "Branding.h"
#include "Settings.h"
#include "ViewManager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "viewpages/ExecutionViewStep.h"

SummaryModel::SummaryModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

QHash< int, QByteArray >
SummaryModel::roleNames() const
{
    // Not including WidgetRole here because that wouldn't make sense
    // in a QML context which is where the roleNames are important.
    return { { TitleRole, "title" }, { MessageRole, "message" } };
}

QVariant
SummaryModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    auto& item = m_summary.at( index.row() );
    switch ( role )
    {
    case TitleRole:
        return item.title;
    case MessageRole:
        return item.message;
    case WidgetRole:
        return item.widget ? QVariant::fromValue( item.widget ) : QVariant();
    default:
        return QVariant();
    }
}

int
SummaryModel::rowCount( const QModelIndex& ) const
{
    return m_summary.count();
}

void
SummaryModel::setSummaryList( const Calamares::ViewStepList& steps, bool withWidgets )
{
    beginResetModel();
    m_summary.clear();

    for ( Calamares::ViewStep* step : steps )
    {
        QString text = step->prettyStatus();
        QWidget* widget = withWidgets ? step->createSummaryWidget() : nullptr;

        if ( text.isEmpty() && !widget )
        {
            continue;
        }

        m_summary << StepSummary { step->prettyName(), text, widget };
    }
    endResetModel();
}

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
    m_title = tr( "Summary" );

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
