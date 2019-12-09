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
#include "HostInfoJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

class HostInfoTests : public QObject
{
    Q_OBJECT
public:
    HostInfoTests() {}
    virtual ~HostInfoTests() {}

private Q_SLOTS:
    void initTestCase();

    void testHostOS();
};

void
HostInfoTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "HostInfo test started.";
}

void
HostInfoTests::testHostOS()
{
#if defined( Q_OS_FREEBSD )
    QString expect( "FreeBSD" );
#elif defined( Q_OS_LINUX )
    QString expect( "Linux" );
#else
    QString expect( "Plan8" );  // Expect failure
#endif

    QCOMPARE( expect, hostOS() );
    QCOMPARE( expect, hostOSName() );  // Might be the same
    QCOMPARE( QStringLiteral( "Intel" ), hostCPU() );  // On all my developer machines
}


QTEST_GUILESS_MAIN( HostInfoTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
