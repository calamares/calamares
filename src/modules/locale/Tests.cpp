/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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


#include "Tests.h"
#include "LocaleConfiguration.h"
#include "timezonewidget/TimeZoneImage.h"

#include "locale/TimeZone.h"

#include <QtTest/QtTest>

QTEST_MAIN( LocaleTests )


LocaleTests::LocaleTests() { }

LocaleTests::~LocaleTests() { }

void
LocaleTests::initTestCase()
{
}

void
LocaleTests::testEmptyLocaleConfiguration()
{
    LocaleConfiguration lc;

    QVERIFY( lc.isEmpty() );
    QCOMPARE( lc.toBcp47(), QString() );
}

void
LocaleTests::testDefaultLocaleConfiguration()
{
    LocaleConfiguration lc( "en_US.UTF-8" );
    QVERIFY( !lc.isEmpty() );
    QCOMPARE( lc.language(), QStringLiteral( "en_US.UTF-8" ) );
    QCOMPARE( lc.toBcp47(), QStringLiteral( "en" ) );

    LocaleConfiguration lc2( "de_DE.UTF-8" );
    QVERIFY( !lc2.isEmpty() );
    QCOMPARE( lc2.language(), QStringLiteral( "de_DE.UTF-8" ) );
    QCOMPARE( lc2.toBcp47(), QStringLiteral( "de" ) );
}

void
LocaleTests::testSplitLocaleConfiguration()
{
    LocaleConfiguration lc( "en_US.UTF-8", "de_DE.UTF-8" );
    QVERIFY( !lc.isEmpty() );
    QCOMPARE( lc.language(), QStringLiteral( "en_US.UTF-8" ) );
    QCOMPARE( lc.toBcp47(), QStringLiteral( "en" ) );
    QCOMPARE( lc.lc_numeric, QStringLiteral( "de_DE.UTF-8" ) );

    LocaleConfiguration lc2( "de_DE.UTF-8", "da_DK.UTF-8" );
    QVERIFY( !lc2.isEmpty() );
    QCOMPARE( lc2.language(), QStringLiteral( "de_DE.UTF-8" ) );
    QCOMPARE( lc2.toBcp47(), QStringLiteral( "de" ) );
    QCOMPARE( lc2.lc_numeric, QStringLiteral( "da_DK.UTF-8" ) );

    LocaleConfiguration lc3( "da_DK.UTF-8", "de_DE.UTF-8" );
    QVERIFY( !lc3.isEmpty() );
    QCOMPARE( lc3.toBcp47(), QStringLiteral( "da" ) );
    QCOMPARE( lc3.lc_numeric, QStringLiteral( "de_DE.UTF-8" ) );
}

void
LocaleTests::testTZImages()
{
    // This test messes around with log-levels a lot so
    // that it produces useful output (e.g. listing the problems,
    // not every check it ever does).
    Logger::setupLogLevel( Logger::LOGDEBUG );

    // Number of zone images
    //
    //
    auto images = TimeZoneImageList::fromDirectory( SOURCE_DIR );
    QCOMPARE( images.count(), images.zoneCount );

    // All image sizes consistent
    //
    //
    const QSize windowSize( 780, 340 );
    {
        QImage background( SOURCE_DIR "/bg.png" );
        QVERIFY( !background.isNull() );
        QCOMPARE( background.size(), windowSize );
    }
    for ( const auto& image : images )
    {
        QCOMPARE( image.size(), windowSize );
    }

    // Check zones are uniquely-claimed
    //
    //
    using namespace CalamaresUtils::Locale;
    const CStringPairList& regions = TZRegion::fromZoneTab();

    int overlapcount = 0;
    for ( const auto* pr : regions )
    {
        const TZRegion* region = dynamic_cast< const TZRegion* >( pr );
        QVERIFY( region );

        Logger::setupLogLevel( Logger::LOGDEBUG );
        cDebug() << "Region" << region->region() << "zones #" << region->zones().count();
        Logger::setupLogLevel( Logger::LOGERROR );

        const auto zones = region->zones();
        QVERIFY( zones.count() > 0 );
        for ( const auto* pz : zones )
        {
            const TZZone* zone = dynamic_cast< const TZZone* >( pz );
            QVERIFY( zone );

            int overlap = 0;
            auto pos = images.getLocationPosition( zone->longitude(), zone->latitude() );
            QVERIFY( images.index( pos, overlap ) >= 0 );
            QVERIFY( overlap > 0 );  // At least one image contains the spot
            if ( overlap > 1 )
            {
                Logger::setupLogLevel( Logger::LOGDEBUG );
                cDebug() << Logger::SubEntry << "Zone" << zone->zone() << pos;
                (void)images.index( pos, overlap );
                Logger::setupLogLevel( Logger::LOGERROR );
                overlapcount++;
            }
        }
    }

    QEXPECT_FAIL("", "TZ Images not yet all fixed", Continue);
    QCOMPARE( overlapcount, 0 );
}
