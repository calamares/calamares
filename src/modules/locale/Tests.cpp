/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"
#include "LocaleConfiguration.h"
#include "timezonewidget/TimeZoneImage.h"

#include "locale/TimeZone.h"
#include "utils/Logger.h"

#include <QtTest/QtTest>

#include <set>

class LocaleTests : public QObject
{
    Q_OBJECT
public:
    LocaleTests();
    ~LocaleTests() override;

private Q_SLOTS:
    void initTestCase();
    // Check the sample config file is processed correctly
    void testEmptyLocaleConfiguration();
    void testDefaultLocaleConfiguration();
    void testSplitLocaleConfiguration();

    // Check the TZ images for consistency
    void testTZSanity();
    void testTZImages();  // No overlaps in images
    void testTZLocations();  // No overlaps in locations
    void testSpecificLocations();

    // Check the Config loading
    void testConfigInitialization();
    void testLanguageDetection_data();
    void testLanguageDetection();
    void testLanguageDetectionValencia();
};

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
LocaleTests::testTZSanity()
{
    // Data source for all TZ info
    QVERIFY( QFile( "/usr/share/zoneinfo/zone.tab" ).exists() );

    // Contains a sensible number of total zones
    const CalamaresUtils::Locale::ZonesModel zones;
    QVERIFY( zones.rowCount( QModelIndex() ) > 100 );
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
    const ZonesModel m;

    int overlapcount = 0;
    for ( auto it = m.begin(); it; ++it )
    {
        QString region = m.data( m.index( it.index() ), ZonesModel::RegionRole ).toString();
        QString zoneName = m.data( m.index( it.index() ), ZonesModel::KeyRole ).toString();
        QVERIFY( !region.isEmpty() );
        QVERIFY( !zoneName.isEmpty() );
        const auto* zone = m.find( region, zoneName );
        const auto* iterzone = *it;

        QVERIFY( iterzone );
        QVERIFY( zone );
        QCOMPARE( zone, iterzone );
        QCOMPARE( zone->zone(), zoneName );
        QCOMPARE( zone->region(), region );

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
listAll( const QPoint& p, const CalamaresUtils::Locale::ZonesModel& zones )
{
    using namespace CalamaresUtils::Locale;
    for ( auto it = zones.begin(); it; ++it )
    {
        const auto* zone = *it;
        if ( !zone )
        {
            cError() << Logger::SubEntry << "NULL zone";
            return;
        }
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
    ZonesModel zones;

    QVERIFY( zones.rowCount( QModelIndex() ) > 100 );

    int overlapcount = 0;
    std::set< QPoint > occupied;
    for ( auto it = zones.begin(); it; ++it )
    {
        const auto* zone = *it;
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

    QEXPECT_FAIL( "", "TZ Images contain pixel-overlaps", Continue );
    QCOMPARE( overlapcount, 0 );
}

void
LocaleTests::testSpecificLocations()
{
    CalamaresUtils::Locale::ZonesModel zones;
    const auto* gibraltar = zones.find( "Europe", "Gibraltar" );
    const auto* ceuta = zones.find( "Africa", "Ceuta" );
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

void
LocaleTests::testConfigInitialization()
{
    Config c;

    QVERIFY( !c.currentLocation() );
    QVERIFY( !c.currentLocationStatus().isEmpty() );
}

void
LocaleTests::testLanguageDetection_data()
{
    QTest::addColumn< QString >( "locale" );
    QTest::addColumn< QString >( "country" );
    QTest::addColumn< QString >( "expected" );

    QTest::newRow( "english (US)" ) << QStringLiteral( "en" ) << QStringLiteral( "US" )
                                    << QStringLiteral( "en_US.UTF-8" );
    QTest::newRow( "english (CA)" ) << QStringLiteral( "en" ) << QStringLiteral( "CA" )
                                    << QStringLiteral( "en" );  // because it's first in the list
    QTest::newRow( "english (GB)" ) << QStringLiteral( "en" ) << QStringLiteral( "GB" )
                                    << QStringLiteral( "en_GB.UTF-8" );
    QTest::newRow( "english (NL)" ) << QStringLiteral( "en" ) << QStringLiteral( "NL" ) << QStringLiteral( "en" );

    QTest::newRow( "portuguese (PT)" ) << QStringLiteral( "pt" ) << QStringLiteral( "PT" )
                                       << QStringLiteral( "pt_PT.UTF-8" );
    QTest::newRow( "portuguese (NL)" ) << QStringLiteral( "pt" ) << QStringLiteral( "NL" )
                                       << QStringLiteral( "pt_BR.UTF-8" );  // first
    QTest::newRow( "portuguese (BR)" ) << QStringLiteral( "pt" ) << QStringLiteral( "BR" )
                                       << QStringLiteral( "pt_BR.UTF-8" );

    QTest::newRow( "catalan ()" ) << QStringLiteral( "ca" ) << QStringLiteral( "" )
                                  << QStringLiteral( "ca_AD.UTF-8" );  // no country given? Matches first
    QTest::newRow( "catalan (ES)" ) << QStringLiteral( "ca" ) << QStringLiteral( "ES" )
                                    << QStringLiteral( "ca_ES.UTF-8" );
    QTest::newRow( "catalan (NL)" ) << QStringLiteral( "ca" ) << QStringLiteral( "NL" )
                                    << QStringLiteral( "ca_AD.UTF-8" );
    QTest::newRow( "catalan (@valencia)" ) << QStringLiteral( "ca@valencia" ) << QStringLiteral( "ES" )
                                           << QStringLiteral( "ca_ES@valencia" );  // Prefers regional variant
    QTest::newRow( "catalan (@valencia_NL)" )
        << QStringLiteral( "ca@valencia" ) << QStringLiteral( "NL" ) << QStringLiteral( "ca_ES@valencia" );
}


/*
 * This list of available locales was created by grepping `/etc/locale.gen`
 * on an EndeavourOS ISO image for a handful of representative locales.
 */
static const QStringList availableLocales {
    "nl_AW",       "nl_BE.UTF-8", "nl_NL.UTF-8",    "en",          "en_AU.UTF-8", "en_US.UTF-8", "en_GB.UTF-8",
    "ca_AD.UTF-8", "ca_ES.UTF-8", "ca_ES@valencia", "sr_ME",       "sr_RS",       "sr_RS@latin", "pt_BR.UTF-8",
    "pt_PT.UTF-8", "es_AR.UTF-8", "es_ES.UTF-8",    "es_MX.UTF-8",
};

void
LocaleTests::testLanguageDetection()
{
    QFETCH( QString, locale );
    QFETCH( QString, country );
    QFETCH( QString, expected );

    auto r = LocaleConfiguration::fromLanguageAndLocation( locale, availableLocales, country );
    QCOMPARE( r.language(), expected );
}

void
LocaleTests::testLanguageDetectionValencia()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    {
        auto r = LocaleConfiguration::fromLanguageAndLocation(
            QStringLiteral( "nl" ), availableLocales, QStringLiteral( "NL" ) );
        QCOMPARE( r.language(), "nl_NL.UTF-8" );
    }
    {
        auto r = LocaleConfiguration::fromLanguageAndLocation(
            QStringLiteral( "ca@valencia" ), availableLocales, QStringLiteral( "NL" ) );
        QCOMPARE( r.language(), "ca_ES@valencia" );
    }
    {
        auto r = LocaleConfiguration::fromLanguageAndLocation(
            QStringLiteral( "sr" ), availableLocales, QStringLiteral( "NL" ) );
        QCOMPARE( r.language(), "sr_ME" );  // Because that one is first in the list
    }
    {
        auto r = LocaleConfiguration::fromLanguageAndLocation(
            QStringLiteral( "sr@latin" ), availableLocales, QStringLiteral( "NL" ) );
        QCOMPARE( r.language(), "sr_RS@latin" );
    }
}


#include "utils/moc-warnings.h"

#include "Tests.moc"
