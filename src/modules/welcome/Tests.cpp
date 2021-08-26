/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "Branding.h"
#include "Settings.h"
#include "network/Manager.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

class WelcomeTests : public QObject
{
    Q_OBJECT
public:
    WelcomeTests();
    ~WelcomeTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testOneUrl();
    void testUrls_data();
    void testUrls();
};

WelcomeTests::WelcomeTests() {}

void
WelcomeTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Welcome test started.";

    // Ensure we have a system object, expect it to be a "bogus" one
    CalamaresUtils::System* system = CalamaresUtils::System::instance();
    QVERIFY( system );
    cDebug() << Logger::SubEntry << "System @" << Logger::Pointer( system );

    const auto* settings = Calamares::Settings::instance();
    if ( !settings )
    {
        (void)new Calamares::Settings( true );
    }
}

void
WelcomeTests::testOneUrl()
{
    Config c;

    // BUILD_AS_TEST is the source-directory path
    QString filename = QStringLiteral( "1a-checkinternet.conf" );
    QFile fi( QString( "%1/tests/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );
    QVERIFY( map.count() > 0 );
    QVERIFY( map.contains( "requirements" ) );

    c.setConfigurationMap( map );
    QCOMPARE( CalamaresUtils::Network::Manager::instance().getCheckInternetUrls().count(), 1 );
}

void
WelcomeTests::testUrls_data()
{
    QTest::addColumn< QString >( "filename" );
    QTest::addColumn< int >( "result" );

    QTest::newRow( "one  " ) << QString( "1a-checkinternet.conf" ) << 1;
    QTest::newRow( "none " ) << QString( "1b-checkinternet.conf" ) << 0;
    QTest::newRow( "blank" ) << QString( "1c-checkinternet.conf" ) << 0;
    QTest::newRow( "bogus" ) << QString( "1d-checkinternet.conf" ) << 0;
    QTest::newRow( "[]   " ) << QString( "1e-checkinternet.conf" ) << 0;
    QTest::newRow( "-3   " ) << QString( "1f-checkinternet.conf" ) << 3;
    QTest::newRow( "[3]  " ) << QString( "1g-checkinternet.conf" ) << 3;
    QTest::newRow( "some " ) << QString( "1h-checkinternet.conf" ) << 3;
}

void
WelcomeTests::testUrls()
{
    QFETCH( QString, filename );
    QFETCH( int, result );

    Config c;

    // BUILD_AS_TEST is the source-directory path
    QFile fi( QString( "%1/tests/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );

    c.setConfigurationMap( map );
    QCOMPARE( CalamaresUtils::Network::Manager::instance().getCheckInternetUrls().count(), result );
}

QTEST_GUILESS_MAIN( WelcomeTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
