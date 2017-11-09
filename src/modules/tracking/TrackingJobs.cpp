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

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSemaphore>

TrackingInstallJob::TrackingInstallJob( const QString& url )
    : m_url( url )
    , m_networkManager( new QNetworkAccessManager( this ) )
    , m_semaphore( new QSemaphore( 1 ) )
{
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
    QNetworkRequest request;
    request.setUrl( QUrl( m_url ) );
    // Follows all redirects except unsafe ones (https to http).
    request.setAttribute( QNetworkRequest::FollowRedirectsAttribute, true );
    // Not everybody likes the default User Agent used by this class (looking at you,
    // sourceforge.net), so let's set a more descriptive one.
    request.setRawHeader( "User-Agent", "Mozilla/5.0 (compatible; Calamares)" );

    connect( m_networkManager, &QNetworkAccessManager::finished,
             this, &TrackingInstallJob::dataIsHere );

    if ( !m_semaphore->tryAcquire( 1, 500 /* ms */ ) )
    {
        // Something's wrong ..
        cDebug() << "WARNING: could not set up semaphore for install-tracking.";
        return Calamares::JobResult::error( tr( "Internal error in install-tracking." ),
                                            tr( "Could not get semaphore for install-tracking." ) );
    }
    m_networkManager->get( request );  // The semaphore is released when data is received
    if ( !m_semaphore->tryAcquire( 1, 5000 /* ms */ ) )
    {
        cDebug() << "WARNING: install-tracking request timed out.";
        return Calamares::JobResult::error( tr( "Internal error in install-tracking." ),
                                            tr( "HTTP request timed out." ) );
    }

    return Calamares::JobResult::ok();
}

void TrackingInstallJob::dataIsHere( QNetworkReply* reply )
{
    if ( m_semaphore )
        m_semaphore->release( 1 );
    reply->deleteLater();
}
