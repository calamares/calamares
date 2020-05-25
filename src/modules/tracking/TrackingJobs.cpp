/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "TrackingJobs.h"

#include "Config.h"

#include "network/Manager.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QSemaphore>
#include <QTimer>

#include <chrono>

TrackingInstallJob::TrackingInstallJob( const QString& url )
    : m_url( url )
{
}

TrackingInstallJob::~TrackingInstallJob() { }

QString
TrackingInstallJob::prettyName() const
{
    return tr( "Installation feedback" );
}

QString
TrackingInstallJob::prettyDescription() const
{
    return prettyName();
}

QString
TrackingInstallJob::prettyStatusMessage() const
{
    return tr( "Sending installation feedback." );
}

Calamares::JobResult
TrackingInstallJob::exec()
{
    using CalamaresUtils::Network::Manager;
    using CalamaresUtils::Network::RequestOptions;
    using CalamaresUtils::Network::RequestStatus;

    auto result = Manager::instance().synchronousPing(
        QUrl( m_url ),
        RequestOptions( RequestOptions::FollowRedirect | RequestOptions::FakeUserAgent,
                        RequestOptions::milliseconds( 5000 ) ) );
    if ( result.status == RequestStatus::Timeout )
    {
        cWarning() << "install-tracking request timed out.";
        return Calamares::JobResult::error( tr( "Internal error in install-tracking." ),
                                            tr( "HTTP request timed out." ) );
    }
    return Calamares::JobResult::ok();
}

void
TrackingInstallJob::addJob( Calamares::JobList& list, InstallTrackingConfig* config )
{
    if ( config->isEnabled() )
    {
        QString installUrl = config->installTrackingUrl();
        const auto* s = CalamaresUtils::System::instance();

        QString memory, disk;
        memory.setNum( s->getTotalMemoryB().first );
        disk.setNum( s->getTotalDiskB() );

        installUrl.replace( "$CPU", s->getCpuDescription() ).replace( "$MEMORY", memory ).replace( "$DISK", disk );

        cDebug() << Logger::SubEntry << "install-tracking URL" << installUrl;

        list.append( Calamares::job_ptr( new TrackingInstallJob( installUrl ) ) );
    }
}

void
TrackingMachineJob::addJob( Calamares::JobList& list, MachineTrackingConfig* config )
{
    if ( config->isEnabled() )
    {
        const auto style = config->machineTrackingStyle();
        if ( style == "neon" )
        {
            list.append( Calamares::job_ptr( new TrackingMachineNeonJob() ) );
        }
        else
        {
            cWarning() << "Unsupported machine tracking style" << style;
        }
    }
}


QString
TrackingMachineNeonJob::prettyName() const
{
    return tr( "Machine feedback" );
}

QString
TrackingMachineNeonJob::prettyDescription() const
{
    return prettyName();
}

QString
TrackingMachineNeonJob::prettyStatusMessage() const
{
    return tr( "Configuring machine feedback." );
}

Calamares::JobResult
TrackingMachineNeonJob::exec()
{
    static const auto script = QStringLiteral(
        R"x(
MACHINE_ID=`cat /etc/machine-id`
sed -i "s,URI =.*,URI = http://releases.neon.kde.org/meta-release/${MACHINE_ID}," /etc/update-manager/meta-release
sed -i "s,URI_LTS =.*,URI_LTS = http://releases.neon.kde.org/meta-release-lts/${MACHINE_ID}," /etc/update-manager/meta-release
true
)x" );
    int r = CalamaresUtils::System::instance()->targetEnvCall( "/bin/sh",
                                                               QString(),  // Working dir
                                                               script,
                                                               std::chrono::seconds( 1 ) );

    if ( r == 0 )
    {
        return Calamares::JobResult::ok();
    }
    else if ( r > 0 )
    {
        return Calamares::JobResult::error(
            tr( "Error in machine feedback configuration." ),
            tr( "Could not configure machine feedback correctly, script error %1." ).arg( r ) );
    }
    else
    {
        return Calamares::JobResult::error(
            tr( "Error in machine feedback configuration." ),
            tr( "Could not configure machine feedback correctly, Calamares error %1." ).arg( r ) );
    }
}

void
TrackingUserJob::addJob( Calamares::JobList& list, UserTrackingConfig* config )
{
    if ( config->isEnabled() )
    {
        const auto style = config->userTrackingStyle();
        if ( style == "kuserfeedback" )
        {
            list.append( Calamares::job_ptr( new TrackingKUserFeedbackJob() ) );
        }
        else
        {
            cWarning() << "Unsupported user tracking style" << style;
        }
    }
}

QString
TrackingKUserFeedbackJob::prettyName() const
{
    return tr( "KDE user feedback" );
}

QString
TrackingKUserFeedbackJob::prettyDescription() const
{
    return prettyName();
}

QString
TrackingKUserFeedbackJob::prettyStatusMessage() const
{
    return tr( "Configuring KDE user feedback." );
}

Calamares::JobResult
TrackingKUserFeedbackJob::exec()
{
    // This is the contents of a config file to turn on some kind
    // of KUserFeedback tracking; the level (16) is chosen for minimal
    // but not zero tracking.
    static const char config[] = R"x([Global]
FeedbackLevel=16
)x";

    for ( const QString& area : QStringList { "PlasmaUserFeedback" } )
    {
        // TODO: get the configured user name
        QString path = QStringLiteral( "/home/%1/.config/%2" ).arg( QString(), area );
        cDebug() << "Configuring KUserFeedback" << path;

        int r = CalamaresUtils::System::instance()->createTargetFile( path, config );
        if ( r > 0 )
        {
            return Calamares::JobResult::error(
                tr( "Error in KDE user feedback configuration." ),
                tr( "Could not configure KDE user feedback correctly, script error %1." ).arg( r ) );
        }
        else if ( r < 0 )
        {
            return Calamares::JobResult::error(
                tr( "Error in KDE user feedback configuration." ),
                tr( "Could not configure KDE user feedback correctly, Calamares error %1." ).arg( r ) );
        }
    }

    return Calamares::JobResult::ok();
}
