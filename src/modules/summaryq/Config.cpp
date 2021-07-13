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
#include "SummaryQmlViewStep.h"

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
    return { { Qt::DisplayRole, "title" }, { Qt::UserRole, "message" } };
}

QVariant
SummaryModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    const auto item = m_summary.at( index.row() );
    return role == Qt::DisplayRole ? item.title : item.message;
}

int
SummaryModel::rowCount( const QModelIndex& ) const
{
    return m_summary.count();
}

void
SummaryModel::setSummary( const Calamares::ViewStepList& steps, bool withWidgets )
{
    Q_EMIT beginResetModel();
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
    Q_EMIT endResetModel();
}

Config::Config( QObject* parent )
    : QObject( parent )
    , m_thisViewStep( static_cast< SummaryQmlViewStep* >( parent ) )
    , m_summary( new SummaryModel( this ) )

{
    CALAMARES_RETRANSLATE_SLOT( &Config::retranslate );
    retranslate();
}

void
Config::retranslate()
{
    m_title = m_thisViewStep->prettyName();

    if ( Calamares::Settings::instance()->isSetupMode() )
    {
        m_message = ( tr( "This is an overview of what will happen once you start "
                          "the setup procedure." ) );
    }
    else
    {
        m_message = ( tr( "This is an overview of what will happen once you start "
                          "the install procedure." ) );
    }
    Q_EMIT titleChanged();
    Q_EMIT messageChanged();
}

void
Config::componentComplete()
{
    refresh();
}

void
Config::refresh()
{
    m_summary->setSummary( stepsForSummary( Calamares::ViewManager::instance()->viewSteps() ) );
}

void
Config::init()
{
    refresh();
}

Calamares::ViewStepList
Config::stepsForSummary( const Calamares::ViewStepList& allSteps ) const
{
    Calamares::ViewStepList steps;
    for ( Calamares::ViewStep* step : allSteps )
    {
        if ( qobject_cast< Calamares::ExecutionViewStep* >( step ) )
        {
            steps.clear();
            continue;
        }

        if ( m_thisViewStep == step )
        {
            break;
        }

        steps.append( step );
    }

    return steps;
}
