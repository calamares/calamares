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
#include "utils/CalamaresUtilsSystem.h"

#include "TrackingJobs.h"
#include "TrackingPage.h"
#include "TrackingViewStep.h"

#include <QDesktopServices>
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


void TrackingViewStep::onLeave()
{
    cDebug() << "Install tracking:" <<
        (tracking( TrackingType::InstallTracking ).userEnabled = m_widget->getTrackingOption( TrackingType::InstallTracking ));
    cDebug() << "Machine tracking:" <<
        (tracking( TrackingType::MachineTracking ).userEnabled = m_widget->getTrackingOption( TrackingType::MachineTracking ));
    cDebug() << "   User tracking:" <<
        (tracking( TrackingType::UserTracking ).userEnabled = m_widget->getTrackingOption( TrackingType::UserTracking ));
}


Calamares::JobList
TrackingViewStep::jobs() const
{
    Calamares::JobList l;

    cDebug() << "Creating tracking jobs ..";
    if ( m_installTracking.enabled() )
    {
        QString installUrl = m_installTrackingUrl;
        const auto s = CalamaresUtils::System::instance();

        QString memory, disk;
        memory.setNum( s->getTotalMemoryB().first );
        disk.setNum( s->getTotalDiskB() );

        installUrl
            .replace( "$CPU", s->getCpuDescription() )
            .replace( "$MEMORY",  memory )
            .replace( "$DISK", disk );

        cDebug() << "  .. install-tracking URL" << installUrl;

        l.append( Calamares::job_ptr( new TrackingInstallJob( installUrl ) ) );
    }
    return l;
}


QVariantMap TrackingViewStep::setTrackingOption(const QVariantMap& configurationMap, const QString& key, TrackingType t)
{
    cDebug() << "Tracking configuration" << key;

    bool settingEnabled = false;
    bool userEnabled = false;

    bool success = false;
    auto config = CalamaresUtils::getSubMap( configurationMap, key, success );

    if ( success )
    {
        settingEnabled = CalamaresUtils::getBool( config, "enabled", false );
        userEnabled = settingEnabled && CalamaresUtils::getBool( config, "default", false );
    }
    cDebug() << "  .. settable=" << settingEnabled << "default=" << userEnabled;

    TrackingEnabled& trackingConfiguration = tracking( t );
    trackingConfiguration.settingEnabled = settingEnabled;
    trackingConfiguration.userEnabled = userEnabled;

    m_widget->setTrackingOption(t, settingEnabled, userEnabled);
    m_widget->setTrackingPolicy(t, CalamaresUtils::getString( config, "policy" ) );

    return config;
}


void
TrackingViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    QVariantMap config;

    config = setTrackingOption( configurationMap, "install", TrackingType::InstallTracking );
    m_installTrackingUrl = CalamaresUtils::getString( config, "url" );

    setTrackingOption( configurationMap, "machine", TrackingType::MachineTracking );
    setTrackingOption( configurationMap, "user", TrackingType::UserTracking );
}
