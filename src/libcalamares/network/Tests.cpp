/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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
    auto canPing_www_kde_org
        = nam.synchronousPing( QUrl( "https://www.kde.org" ), RequestOptions( RequestOptions::FollowRedirect ) );
    QVERIFY( canPing_www_kde_org );
}
