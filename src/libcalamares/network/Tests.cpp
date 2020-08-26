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
