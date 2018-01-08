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

/** @brief Is @p s a valid machine-tracking style. */
static bool isValidStyle( const QString& s )
{
    static QStringList knownStyles { "neon" };
    return knownStyles.contains( s );
}

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
    return tr( "Feedback" );
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
    m_installTracking.userEnabled =  m_widget->getTrackingOption( TrackingType::InstallTracking );
    m_machineTracking.userEnabled =  m_widget->getTrackingOption( TrackingType::MachineTracking );
    m_userTracking.userEnabled =  m_widget->getTrackingOption( TrackingType::UserTracking );
    cDebug() << "Install tracking:" << m_installTracking.enabled();
    cDebug() << "Machine tracking:" << m_machineTracking.enabled();
    cDebug() << "   User tracking:" << m_userTracking.enabled();
}


Calamares::JobList
TrackingViewStep::jobs() const
{
    Calamares::JobList l;

    cDebug() << "Creating tracking jobs ..";
    if ( m_installTracking.enabled() && !m_installTrackingUrl.isEmpty() )
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

    if ( m_machineTracking.enabled() && !m_machineTrackingStyle.isEmpty() )
    {
        Q_ASSERT( isValidStyle( m_machineTrackingStyle ) );
        if ( m_machineTrackingStyle == "neon" )
            l.append( Calamares::job_ptr( new TrackingMachineNeonJob() ) );
    }
    return l;
}


QVariantMap TrackingViewStep::setTrackingOption(const QVariantMap& configurationMap, const QString& key, TrackingType t)
{
    bool settingEnabled = false;

    bool success = false;
    auto config = CalamaresUtils::getSubMap( configurationMap, key, success );

    if ( success )
    {
        settingEnabled = CalamaresUtils::getBool( config, "enabled", false );
    }

    TrackingEnabled& trackingConfiguration = tracking( t );
    trackingConfiguration.settingEnabled = settingEnabled;
    trackingConfiguration.userEnabled = false;

    m_widget->enableTrackingOption(t, settingEnabled);
    m_widget->setTrackingPolicy(t, CalamaresUtils::getString( config, "policy" ) );

    return config;
}

void
TrackingViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    QVariantMap config;

    config = setTrackingOption( configurationMap, "install", TrackingType::InstallTracking );
    m_installTrackingUrl = CalamaresUtils::getString( config, "url" );

    config = setTrackingOption( configurationMap, "machine", TrackingType::MachineTracking );
    auto s = CalamaresUtils::getString( config, "style" );
    if ( isValidStyle( s ) )
        m_machineTrackingStyle = s;

    setTrackingOption( configurationMap, "user", TrackingType::UserTracking );

    m_widget->setGeneralPolicy( CalamaresUtils::getString( configurationMap, "policy" ) );
    m_widget->setTrackingLevel( CalamaresUtils::getString( configurationMap, "default" ) );
}
