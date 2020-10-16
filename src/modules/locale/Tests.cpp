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

#include <set>

QTEST_MAIN( LocaleTests )


LocaleTests::LocaleTests() {}

LocaleTests::~LocaleTests() {}

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

    QEXPECT_FAIL( "", "TZ Images not yet all fixed", Continue );
    QCOMPARE( overlapcount, 0 );
}

bool
operator<( const QPoint& l, const QPoint& r )
{
    if ( l.x() < r.x() )
    {
        return true;
    }
    if ( l.x() > r.x() )
    {
        return false;
    }
    return l.y() < r.y();
}

void
listAll( const QPoint& p, const CalamaresUtils::Locale::CStringPairList& zones )
{
    using namespace CalamaresUtils::Locale;
    for ( const auto* pz : zones )
    {
        const TZZone* zone = dynamic_cast< const TZZone* >( pz );
        if ( p == TimeZoneImageList::getLocationPosition( zone->longitude(), zone->latitude() ) )
        {
            cError() << Logger::SubEntry << zone->zone();
        }
    }
}

void
LocaleTests::testTZLocations()
{
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

        std::set< QPoint > occupied;

        const auto zones = region->zones();
        QVERIFY( zones.count() > 0 );
        for ( const auto* pz : zones )
        {
            const TZZone* zone = dynamic_cast< const TZZone* >( pz );
            QVERIFY( zone );

            auto pos = TimeZoneImageList::getLocationPosition( zone->longitude(), zone->latitude() );
            if ( occupied.find( pos ) != occupied.end() )
            {
                cError() << "Zone" << zone->zone() << "occupies same spot as ..";
                listAll( pos, zones );
                overlapcount++;
            }
            occupied.insert( pos );
        }
    }

    QEXPECT_FAIL( "", "TZ Images contain pixel-overlaps", Continue );
    QCOMPARE( overlapcount, 0 );
}

const CalamaresUtils::Locale::TZZone*
findZone( const QString& name )
{
    using namespace CalamaresUtils::Locale;
    const CStringPairList& regions = TZRegion::fromZoneTab();

    for ( const auto* pr : regions )
    {
        const TZRegion* region = dynamic_cast< const TZRegion* >( pr );
        if ( !region )
        {
            continue;
        }
        const auto zones = region->zones();
        for ( const auto* pz : zones )
        {
            const TZZone* zone = dynamic_cast< const TZZone* >( pz );
            if ( !zone )
            {
                continue;
            }

            if ( zone->zone() == name )
            {
                return zone;
            }
        }
    }
    return nullptr;
}

void
LocaleTests::testSpecificLocations()
{
    const auto* gibraltar = findZone( "Gibraltar" );
    const auto* ceuta = findZone( "Ceuta" );
    QVERIFY( gibraltar );
    QVERIFY( ceuta );

    auto gpos = TimeZoneImageList::getLocationPosition( gibraltar->longitude(), gibraltar->latitude() );
    auto cpos = TimeZoneImageList::getLocationPosition( ceuta->longitude(), ceuta->latitude() );
    QEXPECT_FAIL( "", "Gibraltar and Ceuta are really close", Continue );
    QVERIFY( gpos != cpos );
    QVERIFY( gibraltar->latitude() > ceuta->latitude() );
    QEXPECT_FAIL( "", "Gibraltar and Ceuta are really close", Continue );
    QVERIFY( gpos.y() < cpos.y() );  // Gibraltar is north of Ceuta
}
