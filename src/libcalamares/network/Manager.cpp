/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Manager.h"

#include "compat/Mutex.h"
#include "utils/Logger.h"

#include <QEventLoop>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
#include <QTimer>

#include <algorithm>

/** @brief Does a request asynchronously, returns the (pending) reply
 *
 * The extra options for the request are taken from @p options,
 * including the timeout setting. A timeout will cause the reply
 * to abort. The reply is **not** scheduled for deletion.
 *
 * On failure, returns nullptr (e.g. bad URL, timeout).
 */
static QNetworkReply*
asynchronousRun( QNetworkAccessManager* nam, const QUrl& url, const Calamares::Network::RequestOptions& options )
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
static QPair< Calamares::Network::RequestStatus, QNetworkReply* >
synchronousRun( QNetworkAccessManager* nam, const QUrl& url, const Calamares::Network::RequestOptions& options )
{
    auto* reply = asynchronousRun( nam, url, options );
    if ( !reply )
    {
        cDebug() << "Could not create request for" << url;
        return qMakePair( Calamares::Network::RequestStatus::Failed, nullptr );
    }

    QEventLoop loop;
    QObject::connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();
    reply->deleteLater();
    if ( reply->isRunning() )
    {
        cDebug() << "Timeout on request for" << url;
        return qMakePair( Calamares::Network::RequestStatus::Timeout, nullptr );
    }
    else if ( reply->error() != QNetworkReply::NoError )
    {
        cDebug() << "HTTP error" << reply->error() << "on request for" << url;
        return qMakePair( Calamares::Network::RequestStatus::HttpError, nullptr );
    }
    else
    {
        return qMakePair( Calamares::Network::RequestStatus::Ok, reply );
    }
}

static Calamares::Network::RequestStatus
synchronousPing( QNetworkAccessManager* nam, const QUrl& url, const Calamares::Network::RequestOptions& options )
{
    if ( !url.isValid() )
    {
        return Calamares::Network::RequestStatus::Failed;
    }

    auto reply = synchronousRun( nam, url, options );
    if ( reply.first )
    {
        return reply.second->bytesAvailable() ? Calamares::Network::RequestStatus::Ok
                                              : Calamares::Network::RequestStatus::Empty;
    }
    else
    {
        return reply.first;
    }
}

/** @brief Mutex protecting the singleton Private instance */
static QMutex*
namMutex()
{
    static QMutex namMutex;
    return &namMutex;
}

namespace Calamares
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

/**
 * @class
 *
 * The Private class is intended as a @b singleton and it
 * holds a QNetworkManager per thread (for network access
 * from that thread), and also caches have-internet data
 * to share across Manager instances.
 */
class Manager::Private : public QObject
{
    Q_OBJECT
private:
    std::unique_ptr< QNetworkAccessManager > m_nam;

    using ThreadNam = QPair< QThread*, QNetworkAccessManager* >;
    QVector< ThreadNam > m_perThreadNams;

    Private();

    QVector< QUrl > m_hasInternetUrls;
    bool m_hasInternet = false;
    int m_lastCheckedUrlIndex = -1;

public slots:
    void cleanupNam();

public:
    bool hasInternet() const;
    bool checkHasInternet();
    void setCheckHasInternetUrl( const QUrl& url );
    void setCheckHasInternetUrl( const QVector< QUrl >& urls );
    void addCheckHasInternetUrl( const QUrl& url );
    QVector< QUrl > getCheckInternetUrls() const;

    /** @brief Returns the NAM for this thread */
    QNetworkAccessManager* nam();

    static Private* instance();
};

Manager::Private::Private()
    : m_nam( std::make_unique< QNetworkAccessManager >() )
    , m_hasInternet( false )
{
    m_perThreadNams.reserve( 20 );
    m_perThreadNams.append( qMakePair( QThread::currentThread(), m_nam.get() ) );
}

bool
Manager::Private::hasInternet() const
{
    Calamares::MutexLocker lock( namMutex() );
    return m_hasInternet;
}

bool
Manager::Private::checkHasInternet()
{
    // Locks separately
    auto* threadNAM = nam();

    Calamares::MutexLocker lock( namMutex() );

    if ( m_hasInternetUrls.empty() )
    {
        return false;
    }
    // It's possible that access was switched off (see below, if the check
    // fails) so we want to turn it back on first. Otherwise all the
    // checks will fail **anyway**, defeating the point of the checks.
    if ( m_lastCheckedUrlIndex < 0 )
    {
        m_lastCheckedUrlIndex = 0;
    }
    int attempts = 0;
    do
    {
        // Start by pinging the same one as last time
        m_hasInternet = ::synchronousPing( threadNAM, m_hasInternetUrls.at( m_lastCheckedUrlIndex ), RequestOptions() );
        // if it's not responding, **then** move on to the next one,
        // and wrap around if needed
        if ( !m_hasInternet )
        {
            if ( ++( m_lastCheckedUrlIndex ) >= m_hasInternetUrls.size() )
            {
                m_lastCheckedUrlIndex = 0;
            }
        }
        // keep track of how often we've tried, because there's no point in
        // going around more than once.
        attempts++;
    } while ( !m_hasInternet && ( attempts < m_hasInternetUrls.size() ) );

    return m_hasInternet;
}

void
Manager::Private::setCheckHasInternetUrl( const QUrl& url )
{
    Calamares::MutexLocker lock( namMutex() );

    m_lastCheckedUrlIndex = -1;
    m_hasInternetUrls.clear();
    if ( url.isValid() )
    {
        m_hasInternetUrls.append( url );
    }
}

void
Manager::Private::setCheckHasInternetUrl( const QVector< QUrl >& urls )
{
    Calamares::MutexLocker lock( namMutex() );

    m_lastCheckedUrlIndex = -1;
    m_hasInternetUrls = urls;
    auto it = std::remove_if(
        m_hasInternetUrls.begin(), m_hasInternetUrls.end(), []( const QUrl& u ) { return !u.isValid(); } );
    if ( it != m_hasInternetUrls.end() )
    {
        m_hasInternetUrls.erase( it, m_hasInternetUrls.end() );
    }
}

void
Manager::Private::addCheckHasInternetUrl( const QUrl& url )
{
    if ( url.isValid() )
    {
        Calamares::MutexLocker lock( namMutex() );
        m_hasInternetUrls.append( url );
    }
}

QVector< QUrl >
Manager::Private::getCheckInternetUrls() const
{
    Calamares::MutexLocker lock( namMutex() );
    return m_hasInternetUrls;
}

QNetworkAccessManager*
Manager::Private::nam()
{
    Calamares::MutexLocker lock( namMutex() );

    auto* thread = QThread::currentThread();
    for ( const auto& n : m_perThreadNams )
    {
        if ( n.first == thread )
        {
            return n.second;
        }
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
    Calamares::MutexLocker lock( namMutex() );

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

Manager::Private*
Manager::Private::instance()
{
    static auto* p = new Manager::Private;
    return p;
}

Manager::Manager() {}

Manager::~Manager() {}

bool
Manager::hasInternet()
{
    return Private::instance()->hasInternet();
}

bool
Manager::checkHasInternet()
{
    const auto v = Private::instance()->checkHasInternet();
    emit hasInternetChanged( v );
    return v;
}

void
Manager::setCheckHasInternetUrl( const QUrl& url )
{
    Private::instance()->setCheckHasInternetUrl( url );
}

void
Manager::setCheckHasInternetUrl( const QVector< QUrl >& urls )
{
    Private::instance()->setCheckHasInternetUrl( urls );
}

void
Manager::addCheckHasInternetUrl( const QUrl& url )
{
    Private::instance()->addCheckHasInternetUrl( url );
}

QVector< QUrl >
Manager::getCheckInternetUrls()
{
    return Private::instance()->getCheckInternetUrls();
}

RequestStatus
Manager::synchronousPing( const QUrl& url, const RequestOptions& options )
{
    return ::synchronousPing( Private::instance()->nam(), url, options );
}

QByteArray
Manager::synchronousGet( const QUrl& url, const RequestOptions& options )
{
    if ( !url.isValid() )
    {
        return QByteArray();
    }

    auto reply = synchronousRun( Private::instance()->nam(), url, options );
    return reply.first ? reply.second->readAll() : QByteArray();
}

QNetworkReply*
Manager::asynchronousGet( const QUrl& url, const Calamares::Network::RequestOptions& options )
{
    return asynchronousRun( Private::instance()->nam(), url, options );
}

QDebug&
operator<<( QDebug& s, const Calamares::Network::RequestStatus& e )
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
}  // namespace Calamares

#include "utils/moc-warnings.h"

#include "Manager.moc"
