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

#include "utils/Logger.h"

#include <QEventLoop>
#include <QMutex>
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
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

class Manager::Private : public QObject
{
    Q_OBJECT
private:
    std::unique_ptr< QNetworkAccessManager > m_nam;

    using ThreadNam = QPair< QThread*, QNetworkAccessManager* >;
    QVector< ThreadNam > m_perThreadNams;

public slots:
    void cleanupNam();

public:
    QUrl m_hasInternetUrl;
    bool m_hasInternet;

    Private();

    QNetworkAccessManager* nam();
};

Manager::Private::Private()
    : m_nam( std::make_unique< QNetworkAccessManager >() )
    , m_hasInternet( false )
{
    m_perThreadNams.reserve( 20 );
    m_perThreadNams.append( qMakePair( QThread::currentThread(), m_nam.get() ) );
}

static QMutex*
namMutex()
{
    static QMutex namMutex;
    return &namMutex;
}

QNetworkAccessManager*
Manager::Private::nam()
{
    QMutexLocker lock( namMutex() );

    auto* thread = QThread::currentThread();
    int index = 0;
    for ( const auto& n : m_perThreadNams )
    {
        if ( n.first == thread )
        {
            return n.second;
        }
        ++index;
    }

    // Need a new NAM for this thread
    QNetworkAccessManager* nam = new QNetworkAccessManager();
    m_perThreadNams.append( qMakePair( thread, nam ) );
    QObject::connect( thread, &QThread::finished, this, &Manager::Private::cleanupNam );

    return nam;
}

void
Manager::Private::cleanupNam()
{
    QMutexLocker lock( namMutex() );

    auto* thread = QThread::currentThread();
    bool cleanupFound = false;
    int cleanupIndex = 0;
    for ( const auto& n : m_perThreadNams )
    {
        if ( n.first == thread )
        {
            cleanupFound = true;
            delete n.second;
            break;
        }
        ++cleanupIndex;
    }
    if ( cleanupFound )
    {
        m_perThreadNams.remove( cleanupIndex );
    }
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
    bool hasInternet = d->nam()->networkAccessible() == QNetworkAccessManager::Accessible;

    if ( !hasInternet && ( d->nam()->networkAccessible() == QNetworkAccessManager::UnknownAccessibility ) )
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

/** @brief Does a request asynchronously, returns the (pending) reply
 *
 * The extra options for the request are taken from @p options,
 * including the timeout setting. A timeout will cause the reply
 * to abort. The reply is **not** scheduled for deletion.
 *
 * On failure, returns nullptr (e.g. bad URL, timeout).
 */
static QNetworkReply*
asynchronousRun( QNetworkAccessManager* nam, const QUrl& url, const RequestOptions& options )
{
    QNetworkRequest request = QNetworkRequest( url );
    options.applyToRequest( &request );

    QNetworkReply* reply = nam->get( request );
    QTimer* timer = nullptr;

    // Bail out early if the request is bad
    if ( reply->error() )
    {
        reply->deleteLater();
        return nullptr;
    }

    if ( options.hasTimeout() )
    {
        timer = new QTimer( reply );
        timer->setSingleShot( true );
        QObject::connect( timer, &QTimer::timeout, reply, &QNetworkReply::abort );
        timer->start( options.timeout() );
    }

    return reply;
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
synchronousRun( QNetworkAccessManager* nam, const QUrl& url, const RequestOptions& options )
{
    auto* reply = asynchronousRun( nam, url, options );
    if ( !reply )
    {
        return qMakePair( RequestStatus( RequestStatus::Failed ), nullptr );
    }

    QEventLoop loop;
    QObject::connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();
    reply->deleteLater();
    if ( reply->isRunning() )
    {
        return qMakePair( RequestStatus( RequestStatus::Timeout ), nullptr );
    }
    else if ( reply->error() != QNetworkReply::NoError )
    {
        return qMakePair( RequestStatus( RequestStatus::Timeout ), nullptr );
    }
    else
    {
        return qMakePair( RequestStatus( RequestStatus::Ok ), reply );
    }
}

RequestStatus
Manager::synchronousPing( const QUrl& url, const RequestOptions& options )
{
    if ( !url.isValid() )
    {
        return RequestStatus::Failed;
    }

    auto reply = synchronousRun( d->nam(), url, options );
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

    auto reply = synchronousRun( d->nam(), url, options );
    return reply.first ? reply.second->readAll() : QByteArray();
}

QNetworkReply*
Manager::asynchronousGet( const QUrl& url, const CalamaresUtils::Network::RequestOptions& options )
{
    return asynchronousRun( d->nam(), url, options );
}


}  // namespace Network
}  // namespace CalamaresUtils

#include "utils/moc-warnings.h"

#include "Manager.moc"
