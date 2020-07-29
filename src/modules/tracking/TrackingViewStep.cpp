/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "TrackingViewStep.h"

#include "Config.h"
#include "TrackingJobs.h"
#include "TrackingPage.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QDesktopServices>
#include <QVariantMap>

CALAMARES_PLUGIN_FACTORY_DEFINITION( TrackingViewStepFactory, registerPlugin< TrackingViewStep >(); )

TrackingViewStep::TrackingViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_config( new Config( this ) )
    , m_widget( new TrackingPage( m_config ) )
{
    emit nextStatusChanged( false );
}


TrackingViewStep::~TrackingViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
TrackingViewStep::prettyName() const
{
    return tr( "Feedback" );
}


QWidget*
TrackingViewStep::widget()
{
    return m_widget;
}


bool
TrackingViewStep::isNextEnabled() const
{
    return true;
}


bool
TrackingViewStep::isBackEnabled() const
{
    return true;
}


bool
TrackingViewStep::isAtBeginning() const
{
    return true;
}


bool
TrackingViewStep::isAtEnd() const
{
    return true;
}


void
TrackingViewStep::onLeave()
{
    cDebug() << "Install tracking:" << m_config->installTracking()->isEnabled();
    cDebug() << Logger::SubEntry << "Machine tracking:" << m_config->machineTracking()->isEnabled();
    cDebug() << Logger::SubEntry << "   User tracking:" << m_config->userTracking()->isEnabled();
}


Calamares::JobList
TrackingViewStep::jobs() const
{
    cDebug() << "Creating tracking jobs ..";

    Calamares::JobList l;
    addJob( l, m_config->installTracking() );
    addJob( l, m_config->machineTracking() );
    addJob( l, m_config->userTracking() );
    cDebug() << Logger::SubEntry << l.count() << "jobs queued.";
    return l;
}


void
TrackingViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
}
