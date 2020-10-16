/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
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
