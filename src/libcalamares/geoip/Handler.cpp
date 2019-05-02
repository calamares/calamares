/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "Handler.h"

#include "GeoIPJSON.h"
#if defined(QT_XML_LIB)
#include "GeoIPXML.h"
#endif

#include "utils/Logger.h"

#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace CalamaresUtils::GeoIP
{

Handler::Handler()
    : m_interface( nullptr )
{
}

Handler::Handler( const QString& implementation, const QString& url, const QString& selector )
    : m_interface( nullptr )
    , m_url( url )
{
    if ( implementation.compare( "json", Qt::CaseInsensitive ) == 0 )
    {
        m_interface = new GeoIPJSON( selector );
    }
#if defined(QT_XML_LIB)
    else if ( implementation.compare( "xml", Qt::CaseInsensitive ) == 0 )
    {
        m_interface = new GeoIPXML( selector );
    }
#endif
    else
    {
        cWarning() << "GeoIP Style" << implementation << "is not recognized.";
    }
}

Handler::~Handler()
{
    delete m_interface;
}

bool
Handler::isValid() const
{
    return m_interface;
}

static QByteArray
synchronous_get( const QString& urlstring )
{
    QUrl url( urlstring );
    QNetworkAccessManager manager;
    QEventLoop loop;

    QObject::connect( &manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit );

    QNetworkRequest request( url );
    QNetworkReply* reply = manager.get( request );
    loop.exec();
    reply->deleteLater();
    return reply->readAll();
}


RegionZonePair
Handler::query() const
{
    if ( !isValid() )
        return RegionZonePair();

    return m_interface->processReply( synchronous_get( m_url ) );
}

}  // namespace
