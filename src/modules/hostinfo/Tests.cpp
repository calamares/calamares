/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~HostInfoTests() override {}

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
    QStringList x86cpunames { QStringLiteral( "Intel" ), QStringLiteral( "AMD" ) };
    QStringList armcpunames { QStringLiteral( "ARM" ) };
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
            QCOMPARE( cpu, QString( "Unknown CPU modalias '%1'" ).arg( cpumodalias ) );
        }
    }
}


QTEST_GUILESS_MAIN( HostInfoTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
