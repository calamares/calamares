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

    // This is a lousy test, too: the implementation reads /proc/cpuinfo
    // and that's the only way we could use, too, to find what the "right"
    // answer is.
    QStringList x86cpunames{ QStringLiteral( "Intel" ), QStringLiteral( "AMD" ) };
    QStringList armcpunames{ QStringLiteral( "ARM" ) };
    const QString cpu = hostCPU();
    QVERIFY( x86cpunames.contains( cpu ) || armcpunames.contains( cpu ) );

    // Try to detect family in a different way
    QFile modalias( "/sys/devices/system/cpu/modalias" );
    if ( modalias.open( QIODevice::ReadOnly ) )
    {
        QString cpumodalias = modalias.readLine();
        if ( cpumodalias.contains( "type:x86" ) )
        {
            QVERIFY( x86cpunames.contains( cpu ) );
        }
        else if ( cpumodalias.contains( "type:aarch64" ) )
        {
            QVERIFY( armcpunames.contains( cpu ) );
        }
        else
        {
            QCOMPARE( cpu, QString( "Unknown CPU modalias '%1'" ).arg(cpumodalias) );
        }
    }
}


QTEST_GUILESS_MAIN( HostInfoTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
