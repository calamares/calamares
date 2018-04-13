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

#include "GeoIPFreeGeoIP.h"
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

void
GeoIPTests::testJSON()
{
    static const char data[] =
        "{\"time_zone\":\"Europe/Amsterdam\"}";

    FreeGeoIP handler;
    auto tz = handler.processReply( data );

    QCOMPARE( tz.first, QLatin1String( "Europe" ) );
    QCOMPARE( tz.second, QLatin1String( "Amsterdam" ) );

    // JSON is quite tolerant
    tz = handler.processReply( "time_zone: \"Europe/Brussels\"" );
    QCOMPARE( tz.second, QLatin1String( "Brussels" ) );

    tz = handler.processReply( "time_zone: America/New_York\n" );
    QCOMPARE( tz.first, "America" );
}

void
GeoIPTests::testJSONbad()
{
    static const char data[] = "time_zone: 1";

    FreeGeoIP handler;
    auto tz = handler.processReply( data );

    tz = handler.processReply( data );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "<html><body>404 Forbidden</body></html>" );
    QCOMPARE( tz.first, QString() );
}


void
GeoIPTests::testXML()
{
    static const char data[] =
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

#ifdef HAVE_XML
    XMLGeoIP handler;
    auto tz = handler.processReply( data );

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
    XMLGeoIP handler;
    auto tz = handler.processReply( data );

    QCOMPARE( tz.first, QLatin1String( "America" ) );
    QCOMPARE( tz.second, QLatin1String( "North Dakota/Beulah" ) );
#endif
}

void
GeoIPTests::testXMLbad()
{
#ifdef HAVE_XML
    XMLGeoIP handler;
    auto tz = handler.processReply( "{time_zone: \"Europe/Paris\"}" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "<Response></Response>" );
    QCOMPARE( tz.first, QString() );

    tz = handler.processReply( "fnord<html/>" );
    QCOMPARE( tz.first, QString() );
#endif
}
