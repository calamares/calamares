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

TrackingInstallJob::~TrackingInstallJob()
{
}

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
