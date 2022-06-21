/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

#include <algorithm>

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
        request->setAttribute( QNetworkRequest::RedirectPolicyAttribute, true );
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
    QVector< QUrl > m_hasInternetUrls;
    bool m_hasInternet = false;
    int m_lastCheckedUrlIndex = -1;

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
    if ( d->m_hasInternetUrls.empty() )
    {
        return false;
    }
    // It's possible that access was switched off (see below, if the check
    // fails) so we want to turn it back on first. Otherwise all the
    // checks will fail **anyway**, defeating the point of the checks.
#if ( QT_VERSION < QT_VERSION_CHECK( 5, 15, 0 ) )
    if ( !d->m_hasInternet )
    {
        d->nam()->setNetworkAccessible( QNetworkAccessManager::Accessible );
    }
#endif
    if ( d->m_lastCheckedUrlIndex < 0 )
    {
        d->m_lastCheckedUrlIndex = 0;
    }
    int attempts = 0;
    do
    {
        // Start by pinging the same one as last time
        d->m_hasInternet = synchronousPing( d->m_hasInternetUrls.at( d->m_lastCheckedUrlIndex ) );
        // if it's not responding, **then** move on to the next one,
        // and wrap around if needed
        if ( !d->m_hasInternet )
        {
            if ( ++( d->m_lastCheckedUrlIndex ) >= d->m_hasInternetUrls.size() )
            {
                d->m_lastCheckedUrlIndex = 0;
            }
        }
        // keep track of how often we've tried, because there's no point in
        // going around more than once.
        attempts++;
    } while ( !d->m_hasInternet && ( attempts < d->m_hasInternetUrls.size() ) );


// For earlier Qt versions (< 5.15.0), set the accessibility flag to
// NotAccessible if synchronous ping has failed, so that any module
// using Qt's networkAccessible method to determine whether or not
// internet connection is actually available won't get confused.
#if ( QT_VERSION < QT_VERSION_CHECK( 5, 15, 0 ) )
    if ( !d->m_hasInternet )
    {
        d->nam()->setNetworkAccessible( QNetworkAccessManager::NotAccessible );
    }
#endif

    emit hasInternetChanged( d->m_hasInternet );
    return d->m_hasInternet;
}

void
Manager::setCheckHasInternetUrl( const QUrl& url )
{
    d->m_lastCheckedUrlIndex = -1;
    d->m_hasInternetUrls.clear();
    if ( url.isValid() )
    {
        d->m_hasInternetUrls.append( url );
    }
}

void
Manager::setCheckHasInternetUrl( const QVector< QUrl >& urls )
{
    d->m_lastCheckedUrlIndex = -1;
    d->m_hasInternetUrls = urls;
    auto it = std::remove_if(
        d->m_hasInternetUrls.begin(), d->m_hasInternetUrls.end(), []( const QUrl& u ) { return !u.isValid(); } );
    if ( it != d->m_hasInternetUrls.end() )
    {
        d->m_hasInternetUrls.erase( it, d->m_hasInternetUrls.end() );
    }
}

void
Manager::addCheckHasInternetUrl( const QUrl& url )
{
    if ( url.isValid() )
    {
        d->m_hasInternetUrls.append( url );
    }
}

QVector< QUrl >
Manager::getCheckInternetUrls() const
{
    return d->m_hasInternetUrls;
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
        cWarning() << "Early reply error" << reply->error() << reply->errorString();
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
        cDebug() << "Could not create request for" << url;
        return qMakePair( RequestStatus( RequestStatus::Failed ), nullptr );
    }

    QEventLoop loop;
    QObject::connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();
    reply->deleteLater();
    if ( reply->isRunning() )
    {
        cDebug() << "Timeout on request for" << url;
        return qMakePair( RequestStatus( RequestStatus::Timeout ), nullptr );
    }
    else if ( reply->error() != QNetworkReply::NoError )
    {
        cDebug() << "HTTP error" << reply->error() << "on request for" << url;
        return qMakePair( RequestStatus( RequestStatus::HttpError ), nullptr );
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

QDebug&
operator<<( QDebug& s, const CalamaresUtils::Network::RequestStatus& e )
{
    s << int( e.status ) << bool( e );
    switch ( e.status )
    {
    case RequestStatus::Ok:
        break;
    case RequestStatus::Timeout:
        s << "Timeout";
        break;
    case RequestStatus::Failed:
        s << "Failed";
        break;
    case RequestStatus::HttpError:
        s << "HTTP";
        break;
    case RequestStatus::Empty:
        s << "Empty";
        break;
    }
    return s;
}


}  // namespace Network
}  // namespace CalamaresUtils

#include "utils/moc-warnings.h"

#include "Manager.moc"
