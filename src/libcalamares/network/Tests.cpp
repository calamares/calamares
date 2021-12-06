/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Tests.h"

#include "Manager.h"
#include "utils/Logger.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( NetworkTests )

NetworkTests::NetworkTests() {}

NetworkTests::~NetworkTests() {}

void
NetworkTests::initTestCase()
{
}

void
NetworkTests::testInstance()
{
    auto& nam = CalamaresUtils::Network::Manager::instance();
    QVERIFY( !nam.hasInternet() );
    QCOMPARE( nam.getCheckInternetUrls().count(), 0 );
}

void
NetworkTests::testPing()
{
    using namespace CalamaresUtils::Network;
    Logger::setupLogLevel( Logger::LOGVERBOSE );
    auto& nam = Manager::instance();

    // On FreeBSD, the SSL handling depends on the presence of root keys
    // (from the ca_nss port) which may not be available. So HTTPS requests
    // may fail with SSLVerificationError; this breaks the tests even if
    // the point is to just check whether ping() works.
    //
    // So fall back to pinging example.com if the normal ping fails.
    auto canPing_www_kde_org
        = nam.synchronousPing( QUrl( "https://www.kde.org" ), RequestOptions( RequestOptions::FollowRedirect ) );
    cDebug() << "Ping:" << canPing_www_kde_org;
    if ( canPing_www_kde_org.status == RequestStatus::HttpError )
    {
        cDebug() << Logger::SubEntry << "Some HTTP failure, try example.com instead.";
        auto canPing_example_com
            = nam.synchronousPing( QUrl( "http://example.com" ), RequestOptions( RequestOptions::FollowRedirect ) );
        QVERIFY( canPing_example_com );
    }
    else
    {
        QVERIFY( canPing_www_kde_org );
    }
}

void
NetworkTests::testCheckUrl()
{
    using namespace CalamaresUtils::Network;
    Logger::setupLogLevel( Logger::LOGVERBOSE );
    auto& nam = Manager::instance();

    {
        QUrl u( "http://example.com" );
        QVERIFY( u.isValid() );
        nam.setCheckHasInternetUrl( u );
        QVERIFY( nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 1 );  // Valid URL
    }
    {
        QUrl u( "http://nonexistent.example.com" );
        QVERIFY( u.isValid() );
        nam.setCheckHasInternetUrl( u );
        QVERIFY( !nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 1 );  // Valid URL even if it doesn't resolve
    }
    {
        QUrl u;
        QVERIFY( !u.isValid() );
        nam.setCheckHasInternetUrl( u );
        QVERIFY( !nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 0 );  // Invalid URL tried
    }
}

void
NetworkTests::testCheckMultiUrl()
{
    using namespace CalamaresUtils::Network;
    Logger::setupLogLevel( Logger::LOGVERBOSE );
    auto& nam = Manager::instance();

    {
        QUrl u0( "http://example.com" );
        QUrl u1( "https://kde.org" );
        QVERIFY( u0.isValid() );
        QVERIFY( u1.isValid() );
        nam.setCheckHasInternetUrl( { u0, u1 } );
        QVERIFY( nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 2 );
    }
    {
        QUrl u0( "http://nonexistent.example.com" );
        QUrl u1( "http://bogus.example.com" );
        QVERIFY( u0.isValid() );
        QVERIFY( u1.isValid() );
        nam.setCheckHasInternetUrl( { u0, u1 } );
        QVERIFY( !nam.checkHasInternet() );
        QVERIFY( !nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 2 );  // Both are valid URLs
        nam.addCheckHasInternetUrl( QUrl( "http://example.com" ) );
        QVERIFY( nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 3 );
    }
    {
        QUrl u0( "http://nonexistent.example.com" );
        QUrl u1;
        QVERIFY( u0.isValid() );
        QVERIFY( !u1.isValid() );
        nam.setCheckHasInternetUrl( { u0, u1 } );
        QVERIFY( !nam.checkHasInternet() );
        QVERIFY( !nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 1 );  // Only valid URL added
        nam.addCheckHasInternetUrl( QUrl( "http://example.com" ) );
        QVERIFY( nam.checkHasInternet() );
        QCOMPARE( nam.getCheckInternetUrls().count(), 2 );
    }
    {
        QUrl u0( "http://nonexistent.example.com" );
        QUrl u1;
        QVERIFY( u0.isValid() );
        QVERIFY( !u1.isValid() );
        nam.setCheckHasInternetUrl( { u1, u1, u1, u1 } );
        QCOMPARE( nam.getCheckInternetUrls().count(), 0 );
        nam.setCheckHasInternetUrl( { u1, u1, u0, u1 } );
        QCOMPARE( nam.getCheckInternetUrls().count(), 1 );
    }
}
