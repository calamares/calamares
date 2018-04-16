/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "GeoIPTests.h"

#include "GeoIPJSON.h"
#ifdef HAVE_XML
#include "GeoIPXML.h"
#endif

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( GeoIPTests )

GeoIPTests::GeoIPTests()
{
}

GeoIPTests::~GeoIPTests()
{
}

void
GeoIPTests::initTestCase()
{
}

static const char json_data_attribute[] =
    "{\"time_zone\":\"Europe/Amsterdam\"}";

void
GeoIPTests::testJSON()
{
    GeoIPJSON handler;
    auto tz = handler.processReply( json_data_attribute );

    QCOMPARE( tz.first, QLatin1String( "Europe" ) );
    QCOMPARE( tz.second, QLatin1String( "Amsterdam" ) );

    // JSON is quite tolerant
    tz = handler.processReply( "time_zone: \"Europe/Brussels\"" );
    QCOMPARE( tz.second, QLatin1String( "Brussels" ) );

    tz = handler.processReply( "time_zone: America/New_York\n" );
    QCOMPARE( tz.first, "America" );
}

void GeoIPTests::testJSONalt()
{
    GeoIPJSON handler( "zona_de_hora" );

    auto tz = handler.processReply( json_data_attribute );
    QCOMPARE( tz.first, QString() );  // Not found

    tz = handler.processReply( "tarifa: 12\nzona_de_hora: Europe/Madrid" );
    QCOMPARE( tz.first, QLatin1String( "Europe" ) );
    QCOMPARE( tz.second, QLatin1String( "Madrid" ) );
}

void
GeoIPTests::testJSONbad()
{
    static const char data[] = "time_zone: 1";

    GeoIPJSON handler;
    auto tz = handler.processReply( data );

    tz = handler.processReply( data );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "<html><body>404 Forbidden</body></html>" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "{ time zone = 'America/LosAngeles'}" );
    QCOMPARE( tz.first, QString() );
}


static const char xml_data_ubiquity[] =
        R"(<Response>
  <Ip>85.150.1.1</Ip>
  <Status>OK</Status>
  <CountryCode>NL</CountryCode>
  <CountryCode3>NLD</CountryCode3>
  <CountryName>Netherlands</CountryName>
  <RegionCode>None</RegionCode>
  <RegionName>None</RegionName>
  <City>None</City>
  <ZipPostalCode/>
  <Latitude>50.0</Latitude>
  <Longitude>4.0</Longitude>
  <AreaCode>0</AreaCode>
  <TimeZone>Europe/Amsterdam</TimeZone>
</Response>)";

void
GeoIPTests::testXML()
{
#ifdef HAVE_XML
    GeoIPXML handler;
    auto tz = handler.processReply( xml_data_ubiquity );

    QCOMPARE( tz.first, QLatin1String( "Europe" ) );
    QCOMPARE( tz.second, QLatin1String( "Amsterdam" ) );
#endif
}

void
GeoIPTests::testXML2()
{
    static const char data[] =
        "<Response><TimeZone>America/North Dakota/Beulah</TimeZone></Response>";

#ifdef HAVE_XML
    GeoIPXML handler;
    auto tz = handler.processReply( data );

    QCOMPARE( tz.first, QLatin1String( "America" ) );
    QCOMPARE( tz.second, QLatin1String( "North Dakota/Beulah" ) );
#endif
}


void GeoIPTests::testXMLalt()
{
#ifdef HAVE_XML
    GeoIPXML handler( "ZT" );

    auto tz = handler.processReply( "<A><B/><C><ZT>Moon/Dark_side</ZT></C></A>" );
    QCOMPARE( tz.first, QLatin1String( "Moon" ) );
    QCOMPARE( tz.second, QLatin1String( "Dark_side" ) );
#endif
}

void
GeoIPTests::testXMLbad()
{
#ifdef HAVE_XML
    GeoIPXML handler;
    auto tz = handler.processReply( "{time_zone: \"Europe/Paris\"}" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "<Response></Response>" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "fnord<html/>" );
    QCOMPARE( tz.first, QString() );
#endif
}

void GeoIPTests::testSplitTZ()
{
    auto tz = GeoIP::splitTZString( QLatin1String("Moon/Dark_side") );
    QCOMPARE( tz.first, QLatin1String("Moon") );
    QCOMPARE( tz.second, QLatin1String("Dark_side") );

    // Some providers return weirdly escaped data
    tz = GeoIP::splitTZString( QLatin1String("America\\/NewYork") );
    QCOMPARE( tz.first, QLatin1String("America") );
    QCOMPARE( tz.second, QLatin1String("NewYork") );  // That's not actually the zone name

    // Check that bogus data fails
    tz = GeoIP::splitTZString( QString() );
    QCOMPARE( tz.first, QString() );

    tz = GeoIP::splitTZString( QLatin1String("America.NewYork") );
    QCOMPARE( tz.first, QString() );

    // Check that three-level is split properly
    tz = GeoIP::splitTZString( QLatin1String("America/North Dakota/Beulah") );
    QCOMPARE( tz.first, QLatin1String("America") );
    QCOMPARE( tz.second, QLatin1String("North Dakota/Beulah") );
}


static QByteArray
synchronous_get( const char* urlstring )
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

#define CHECK_GET(t, selector, url) \
    { \
        auto tz = GeoIP##t( selector ).processReply( synchronous_get( url ) ); \
        QCOMPARE( default_tz, tz ); \
        qDebug() << "Checked" << url; \
    }

void GeoIPTests::testGet()
{
    if ( !QProcessEnvironment::systemEnvironment().contains( QLatin1String("TEST_HTTP_GET") ) )
    {
        qDebug() << "Skipping HTTP GET tests";
        return;
    }

    GeoIPJSON default_handler;
    // Call the KDE service the definitive source, even though this
    // service is temporary and might go away any time.
    auto default_tz = default_handler.processReply( synchronous_get( "http://drax.kde.org:9129/calamares" ) );

    // This is bogus, because the test isn't always run by me
    // QCOMPARE( default_tz.first, QLatin1String("Europe") );
    // QCOMPARE( default_tz.second, QLatin1String("Amsterdam") );
    QVERIFY( !default_tz.first.isEmpty() );
    QVERIFY( !default_tz.second.isEmpty() );

    // Each expansion of CHECK_GET does a synchronous GET, then checks that
    // the TZ data is the same as the default_tz; this is fragile if the
    // services don't agree on the location of where the test is run.
    CHECK_GET( JSON, QString(), "http://drax.kde.org:9129/calamares" )     // Temporary KDE service
    CHECK_GET( JSON, QString(), "http://freegeoip.net/json/" )             // Original FreeGeoIP service
    CHECK_GET( JSON, QLatin1String("timezone"), "https://ipapi.co/json" )  // Different JSON
    CHECK_GET( JSON, QLatin1String("timezone"), "http://ip-api.com/json" )

    CHECK_GET( JSON, QLatin1String("location.time_zone"), "http://geoip.nekudo.com/api/" )  // 2-level JSON

    CHECK_GET( JSON, QLatin1String("Location.TimeZone"), "http://drax.kde.org:9129/" )  // 2-level JSON

#ifdef HAVE_XML
    CHECK_GET( XML, QString(), "http://geoip.ubuntu.com/lookup" )  // Ubiquity's XML format
    CHECK_GET( XML, QString(),  "http://drax.kde.org:9129/ubiquity" )  // Temporary KDE service
#endif
}
