/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
