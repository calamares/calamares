/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "GeoIPTests.h"

#include "GeoIPFixed.h"
#include "GeoIPJSON.h"
#ifdef QT_XML_LIB
#include "GeoIPXML.h"
#endif
#include "Handler.h"

#include "network/Manager.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( GeoIPTests )

using namespace Calamares::GeoIP;

GeoIPTests::GeoIPTests() {}

GeoIPTests::~GeoIPTests() {}

void
GeoIPTests::initTestCase()
{
}

static const char json_data_attribute[] = "{\"time_zone\":\"Europe/Amsterdam\"}";

void
GeoIPTests::testJSON()
{
    GeoIPJSON handler;
    auto tz = handler.processReply( json_data_attribute );

    QCOMPARE( tz.region(), QStringLiteral( "Europe" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "Amsterdam" ) );

    // JSON is quite tolerant
    tz = handler.processReply( "time_zone: \"Europe/Brussels\"" );
    QCOMPARE( tz.zone(), QStringLiteral( "Brussels" ) );

    tz = handler.processReply( "time_zone: America/New_York\n" );
    QCOMPARE( tz.region(), QStringLiteral( "America" ) );
}

void
GeoIPTests::testJSONalt()
{
    GeoIPJSON handler( "zona_de_hora" );

    auto tz = handler.processReply( json_data_attribute );
    QCOMPARE( tz.region(), QString() );  // Not found

    tz = handler.processReply( "tarifa: 12\nzona_de_hora: Europe/Madrid" );
    QCOMPARE( tz.region(), QStringLiteral( "Europe" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "Madrid" ) );
}

void
GeoIPTests::testJSONbad()
{
    static const char data[] = "time_zone: 1";

    GeoIPJSON handler;
    auto tz = handler.processReply( data );

    tz = handler.processReply( data );
    QCOMPARE( tz.region(), QString() );

    tz = handler.processReply( "" );
    QCOMPARE( tz.region(), QString() );

    tz = handler.processReply( "<html><body>404 Forbidden</body></html>" );
    QCOMPARE( tz.region(), QString() );

    tz = handler.processReply( "{ time zone = 'America/LosAngeles'}" );
    QCOMPARE( tz.region(), QString() );
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
#ifdef QT_XML_LIB
    GeoIPXML handler;
    auto tz = handler.processReply( xml_data_ubiquity );

    QCOMPARE( tz.region(), QStringLiteral( "Europe" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "Amsterdam" ) );
#endif
}

void
GeoIPTests::testXML2()
{
#ifdef QT_XML_LIB
    static const char data[]
        = "<Response><TimeZone>America/North Dakota/Beulah</TimeZone></Response>";  // With a space!

    GeoIPXML handler;
    auto tz = handler.processReply( data );

    QCOMPARE( tz.region(), QStringLiteral( "America" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "North_Dakota/Beulah" ) );  // Without space
#endif
}

void
GeoIPTests::testXMLalt()
{
#ifdef QT_XML_LIB
    GeoIPXML handler( "ZT" );

    auto tz = handler.processReply( "<A><B/><C><ZT>Moon/Dark_side</ZT></C></A>" );
    QCOMPARE( tz.region(), QStringLiteral( "Moon" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "Dark_side" ) );
#endif
}

void
GeoIPTests::testXMLbad()
{
#ifdef QT_XML_LIB
    GeoIPXML handler;
    auto tz = handler.processReply( "{time_zone: \"Europe/Paris\"}" );
    QCOMPARE( tz.region(), QString() );

    tz = handler.processReply( "<Response></Response>" );
    QCOMPARE( tz.region(), QString() );

    tz = handler.processReply( "fnord<html/>" );
    QCOMPARE( tz.region(), QString() );
#endif
}

void
GeoIPTests::testSplitTZ()
{
    using namespace Calamares::GeoIP;
    auto tz = splitTZString( QStringLiteral( "Moon/Dark_side" ) );
    QCOMPARE( tz.region(), QStringLiteral( "Moon" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "Dark_side" ) );

    // Some providers return weirdly escaped data
    tz = splitTZString( QStringLiteral( "America\\/NewYork" ) );
    QCOMPARE( tz.region(), QStringLiteral( "America" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "NewYork" ) );  // That's not actually the zone name

    // Check that bogus data fails
    tz = splitTZString( QString() );
    QCOMPARE( tz.region(), QString() );

    tz = splitTZString( QStringLiteral( "America.NewYork" ) );
    QCOMPARE( tz.region(), QString() );

    // Check that three-level is split properly and space is replaced
    tz = splitTZString( QStringLiteral( "America/North Dakota/Beulah" ) );
    QCOMPARE( tz.region(), QStringLiteral( "America" ) );
    QCOMPARE( tz.zone(), QStringLiteral( "North_Dakota/Beulah" ) );
}

#define CHECK_GET( t, selector, url ) \
    { \
        auto tz = GeoIP##t( selector ).processReply( Calamares::Network::Manager().synchronousGet( QUrl( url ) ) ); \
        qDebug() << tz; \
        QCOMPARE( default_tz, tz ); \
        auto tz2 = Calamares::GeoIP::Handler( "" #t, url, selector ).get(); \
        qDebug() << tz2; \
        QCOMPARE( default_tz, tz2 ); \
    }

void
GeoIPTests::testGet()
{
    if ( !QProcessEnvironment::systemEnvironment().contains( QStringLiteral( "TEST_HTTP_GET" ) ) )
    {
        qDebug() << "Skipping HTTP GET tests, set TEST_HTTP_GET environment variable to enable";
        return;
    }

    GeoIPJSON default_handler;
    // Call the KDE service the definitive source.
    auto default_tz = default_handler.processReply(
        Calamares::Network::Manager().synchronousGet( QUrl( "https://geoip.kde.org/v1/calamares" ) ) );

    // This is bogus, because the test isn't always run by me
    // QCOMPARE( default_tz.region(), QStringLiteral("Europe") );
    // QCOMPARE( default_tz.zone(), QStringLiteral("Amsterdam") );
    QVERIFY( !default_tz.region().isEmpty() );
    QVERIFY( !default_tz.zone().isEmpty() );

    // Each expansion of CHECK_GET does a synchronous GET, then checks that
    // the TZ data is the same as the default_tz; this is fragile if the
    // services don't agree on the location of where the test is run.
    CHECK_GET( JSON, QString(), "https://geoip.kde.org/v1/calamares" )  // Check it's consistent
    CHECK_GET( JSON, QStringLiteral( "timezone" ), "https://ipapi.co/json" )  // Different JSON
    CHECK_GET( JSON, QStringLiteral( "timezone" ), "http://ip-api.com/json" )

    CHECK_GET( JSON, QStringLiteral( "Location.TimeZone" ), "https://geoip.kde.org/debug" )  // 2-level JSON

#ifdef QT_XML_LIB
    CHECK_GET( XML, QString(), "http://geoip.ubuntu.com/lookup" )  // Ubiquity's XML format
    CHECK_GET( XML, QString(), "https://geoip.kde.org/v1/ubiquity" )  // Temporary KDE service
#endif
}

void
GeoIPTests::testFixed()
{
    {
        GeoIPFixed f;
        auto tz = f.processReply( QByteArray() );
        QCOMPARE( tz.region(), QStringLiteral( "Europe" ) );
        QCOMPARE( tz.zone(), QStringLiteral( "Amsterdam" ) );

        QCOMPARE( f.processReply( xml_data_ubiquity ), tz );
        QCOMPARE( f.processReply( QByteArray( "derp" ) ), tz );
    }
    {
        GeoIPFixed f( QStringLiteral( "America/Vancouver" ) );
        auto tz = f.processReply( QByteArray() );
        QCOMPARE( tz.region(), QStringLiteral( "America" ) );
        QCOMPARE( tz.zone(), QStringLiteral( "Vancouver" ) );

        QCOMPARE( f.processReply( xml_data_ubiquity ), tz );
        QCOMPARE( f.processReply( QByteArray( "derp" ) ), tz );
    }
    {
        GeoIPFixed f( QStringLiteral( "America/North Dakota/Beulah" ) );
        auto tz = f.processReply( QByteArray() );
        QCOMPARE( tz.region(), QStringLiteral( "America" ) );
        QCOMPARE( tz.zone(), QStringLiteral( "North_Dakota/Beulah" ) );

        QCOMPARE( f.processReply( xml_data_ubiquity ), tz );
        QCOMPARE( f.processReply( QByteArray( "derp" ) ), tz );
    }
}
