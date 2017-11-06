/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtils.h"

#include "TrackingViewStep.h"
#include "TrackingPage.h"

#include <QVariantMap>

CALAMARES_PLUGIN_FACTORY_DEFINITION( TrackingViewStepFactory, registerPlugin<TrackingViewStep>(); )

TrackingViewStep::TrackingViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new TrackingPage )
{
    emit nextStatusChanged( false );
}


TrackingViewStep::~TrackingViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
TrackingViewStep::prettyName() const
{
    return tr( "Telemetry" );
}


QWidget*
TrackingViewStep::widget()
{
    return m_widget;
}


void
TrackingViewStep::next()
{
    emit done();
}


void
TrackingViewStep::back()
{}


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


QList< Calamares::job_ptr >
TrackingViewStep::jobs() const
{
    cDebug() << "Tracking jobs ..";
    return QList< Calamares::job_ptr >();
}


static
bool getTrackingEnabled( const QVariantMap& configurationMap, const QString& key, TrackingEnabled& track )
{
    cDebug() << "Tracking configuration" << key;

    // Switch it off by default
    track.settingEnabled = false;
    track.userEnabled = false;

    bool success = false;
    auto config = CalamaresUtils::getSubMap( configurationMap, key, success );

    if ( success )
    {
        track.settingEnabled = CalamaresUtils::getBool( config, "enabled", false );
        track.userEnabled = track.settingEnabled && CalamaresUtils::getBool( config, "default", false );
    }
    cDebug() << "  .. Install tracking: enabled=" <<track.settingEnabled << "default=" << track.userEnabled;

    return track.settingEnabled;
}


void
TrackingViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    getTrackingEnabled( configurationMap, "install", m_installTracking );
    getTrackingEnabled( configurationMap, "machine", m_machineTracking );
    getTrackingEnabled( configurationMap, "user", m_userTracking );
}
