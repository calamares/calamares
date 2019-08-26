/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "Manager.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

namespace CalamaresUtils
{
namespace Network
{
void
RequestOptions::applyToRequest( QNetworkRequest* request ) const
{
    if ( m_flags & Flag::FollowRedirect )
    {
        // Follows all redirects except unsafe ones (https to http).
        request->setAttribute( QNetworkRequest::FollowRedirectsAttribute, true );
    }

    if ( m_flags & Flag::FakeUserAgent )
    {
        // Not everybody likes the default User Agent used by this class (looking at you,
        // sourceforge.net), so let's set a more descriptive one.
        request->setRawHeader( "User-Agent", "Mozilla/5.0 (compatible; Calamares)" );
    }
}

struct Manager::Private
{
    std::unique_ptr< QNetworkAccessManager > m_nam;
    QUrl m_hasInternetUrl;
    bool m_hasInternet;

    Private();
};

Manager::Private::Private()
    : m_nam( std::make_unique< QNetworkAccessManager >() )
    , m_hasInternet( false )
{
}

Manager::Manager()
    : d( std::make_unique< Private >() )
{
}

Manager::~Manager() {}

Manager&
Manager::instance()
{
    static auto* s_manager = new Manager();
    return *s_manager;
}

bool
Manager::hasInternet()
{
    return d->m_hasInternet;
}

bool
Manager::checkHasInternet()
{
    bool hasInternet = d->m_nam->networkAccessible() == QNetworkAccessManager::Accessible;

    if ( !hasInternet && ( d->m_nam->networkAccessible() == QNetworkAccessManager::UnknownAccessibility ) )
    {
        hasInternet = synchronousPing( d->m_hasInternetUrl );
    }
    d->m_hasInternet = hasInternet;
    return hasInternet;
}

void
Manager::setCheckHasInternetUrl( const QUrl& url )
{
    d->m_hasInternetUrl = url;
}

/** @brief Does a request synchronously, returns the request itself
 *
 * The extra options for the request are taken from @p options,
 * including the timeout setting.
 *
 * On failure, returns nullptr (e.g. bad URL, timeout). The request
 * is marked for later automatic deletion, so don't store the pointer.
 */
static QPair< RequestStatus, QNetworkReply* >
synchronousRun( const std::unique_ptr< QNetworkAccessManager >& nam, const QUrl& url, const RequestOptions& options )
{
    QNetworkRequest request = QNetworkRequest( url );
    QNetworkReply* reply = nam->get( request );
    QEventLoop loop;
    QTimer timer;

    // Bail out early if the request is bad
    if ( reply->error() )
    {
        reply->deleteLater();
        return qMakePair( RequestStatus( RequestStatus::Failed ), nullptr );
    }

    options.applyToRequest( &request );
    if ( options.hasTimeout() )
    {
        timer.setSingleShot( true );
        QObject::connect( &timer, &QTimer::timeout, &loop, &QEventLoop::quit );
        timer.start( options.timeout() );
    }

    QObject::connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();
    if ( options.hasTimeout() && !timer.isActive() )
    {
        reply->deleteLater();
        return qMakePair( RequestStatus( RequestStatus::Timeout ), nullptr );
    }

    reply->deleteLater();
    return qMakePair( RequestStatus( RequestStatus::Ok ), reply );
}

RequestStatus
Manager::synchronousPing( const QUrl& url, const RequestOptions& options )
{
    if ( !url.isValid() )
    {
        return RequestStatus::Failed;
    }

    auto reply = synchronousRun( d->m_nam, url, options );
    if ( reply.first )
    {
        return reply.second->bytesAvailable() ? RequestStatus::Ok : RequestStatus::Empty;
    }
    else
    {
        return reply.first;
    }
}

QByteArray
Manager::synchronousGet( const QUrl& url, const RequestOptions& options )
{
    if ( !url.isValid() )
    {
        return QByteArray();
    }

    auto reply = synchronousRun( d->m_nam, url, options );
    return reply.first ? reply.second->readAll() : QByteArray();
}

}  // namespace Network
}  // namespace CalamaresUtils
