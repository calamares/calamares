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

#include <memory>

namespace CalamaresUtils::GeoIP
{

Handler::Handler()
    : m_type( Type::None )
{
}

Handler::Handler( const QString& implementation, const QString& url, const QString& selector )
    : m_type( Type::None )
    , m_url( url )
{
    if ( implementation.compare( "json", Qt::CaseInsensitive ) == 0 )
    {

        m_type = Type::JSON;
    }
#if defined(QT_XML_LIB)
    else if ( implementation.compare( "xml", Qt::CaseInsensitive ) == 0 )
    {
        m_type = Type::XML;
    }
#endif
    else
    {
        cWarning() << "GeoIP Style" << implementation << "is not recognized.";
    }
}

Handler::~Handler()
{
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

static std::unique_ptr< Interface >
create_interface( Handler::Type t, const QString& selector )
{
    switch( t )
    {
        case Handler::Type::None:
            return nullptr;
        case Handler::Type::JSON:
            return std::make_unique< GeoIPJSON >( selector );
        case Handler::Type::XML:
#if defined(QT_XML_LIB)
            return std::make_unique< GeoIPXML >( selector );
#else
            return nullptr;
#endif
        default:  // there are no others
            return nullptr;
    }
}

static RegionZonePair
do_query( Handler::Type type, const QString& url, const QString& selector )
{
    const auto interface = create_interface( type, selector );
    if ( !interface )
        return RegionZonePair();

    return interface->processReply( synchronous_get( url ) );
}

RegionZonePair
Handler::get() const
{
    if ( !isValid() )
        return RegionZonePair();
    return do_query( m_type, m_url, m_selector );
}


QFuture< RegionZonePair >
Handler::query() const
{
    Handler::Type type = m_type;
    QString url = m_url;
    QString selector = m_selector;

    return QtConcurrent::run( [=]
        {
            return do_query( type, url, selector );
        } );
}

}  // namespace
