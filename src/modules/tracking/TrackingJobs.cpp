/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde..org>
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

#include "utils/Logger.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSemaphore>
#include <QTimer>

TrackingInstallJob::TrackingInstallJob( const QString& url )
    : m_url( url )
    , m_networkManager( nullptr )
{
}

TrackingInstallJob::~TrackingInstallJob()
{
    delete m_networkManager;
}

QString TrackingInstallJob::prettyName() const
{
    return tr( "Install-tracking" );
}

QString TrackingInstallJob::prettyDescription() const
{
    return tr( "Install-tracking" );
}

QString TrackingInstallJob::prettyStatusMessage() const
{
    return tr( "Sending install-tracking information." );
}

Calamares::JobResult TrackingInstallJob::exec()
{
    m_networkManager = new QNetworkAccessManager();

    QNetworkRequest request;
    request.setUrl( QUrl( m_url ) );
    // Follows all redirects except unsafe ones (https to http).
    request.setAttribute( QNetworkRequest::FollowRedirectsAttribute, true );
    // Not everybody likes the default User Agent used by this class (looking at you,
    // sourceforge.net), so let's set a more descriptive one.
    request.setRawHeader( "User-Agent", "Mozilla/5.0 (compatible; Calamares)" );

    QTimer timeout;
    timeout.setSingleShot(true);

    QEventLoop loop;

    connect( m_networkManager, &QNetworkAccessManager::finished,
             this, &TrackingInstallJob::dataIsHere );
    connect( m_networkManager, &QNetworkAccessManager::finished,
             &loop, &QEventLoop::quit );
    connect( &timeout, &QTimer::timeout,
             &loop, &QEventLoop::quit );

    m_networkManager->get( request );  // The semaphore is released when data is received
    timeout.start( 5000 /* ms */ );

    loop.exec();

    if ( !timeout.isActive() )
    {
        cDebug() << "WARNING: install-tracking request timed out.";
        return Calamares::JobResult::error( tr( "Internal error in install-tracking." ),
                                            tr( "HTTP request timed out." ) );
    }
    timeout.stop();

    return Calamares::JobResult::ok();
}

void TrackingInstallJob::dataIsHere( QNetworkReply* reply )
{
    cDebug() << "Install-tracking request OK";
    reply->deleteLater();
}

QString TrackingMachineNeonJob::prettyName() const
{
    return tr( "Machine feedback" );
}

QString TrackingMachineNeonJob::prettyDescription() const
{
    return prettyName();
}

QString TrackingMachineNeonJob::prettyStatusMessage() const
{
    return tr( "Configuring machine feedback." );
}

Calamares::JobResult TrackingMachineNeonJob::exec()
{
    return Calamares::JobResult::error( tr( "Error in machine feedback configuration." ),
                                        tr( "Could not configure machine feedback correctly." ) );
}
