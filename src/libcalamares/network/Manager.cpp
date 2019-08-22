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

namespace CalamaresUtils
{
namespace Network
{
struct Manager::Private
{
    std::unique_ptr< QNetworkAccessManager > m_nam;
    QUrl m_hasInternetUrl;
    bool m_hasInternet;

    Private();
};
}  // namespace Network
}  // namespace CalamaresUtils
CalamaresUtils::Network::Manager::Private::Private()
    : m_nam( std::make_unique< QNetworkAccessManager >() )
    , m_hasInternet( false )
{
}

CalamaresUtils::Network::Manager::Manager()
    : d( std::make_unique< Private >() )
{
}

CalamaresUtils::Network::Manager::~Manager() {}

CalamaresUtils::Network::Manager&
CalamaresUtils::Network::Manager::instance()
{
    static auto* s_manager = new CalamaresUtils::Network::Manager();
    return *s_manager;
}

bool
CalamaresUtils::Network::Manager::hasInternet()
{
    return d->m_hasInternet;
}

bool
CalamaresUtils::Network::Manager::checkHasInternet()
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
CalamaresUtils::Network::Manager::setCheckHasInternetUrl( const QUrl& url )
{
    d->m_hasInternetUrl = url;
}

bool
CalamaresUtils::Network::Manager::synchronousPing( const QUrl& url )
{
    if ( !url.isValid() )
    {
        return false;
    }

    QNetworkRequest req = QNetworkRequest( url );
    QNetworkReply* reply = d->m_nam->get( req );
    QEventLoop loop;
    connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();
    reply->deleteLater();
    return reply->bytesAvailable();
}

QByteArray
CalamaresUtils::Network::Manager::synchronousGet( const QUrl& url )
{
    if ( !url.isValid() )
    {
        return QByteArray();
    }

    QNetworkRequest request( url );
    QNetworkReply* reply = d->m_nam->get( request );
    QEventLoop loop;
    connect( reply, &QNetworkReply::finished, &loop, &QEventLoop::quit );
    loop.exec();
    reply->deleteLater();
    return reply->readAll();
}
