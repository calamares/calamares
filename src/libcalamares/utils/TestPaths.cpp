/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "CalamaresUtilsSystem.h"
#include "Entropy.h"
#include "Logger.h"
#include "UMask.h"
#include "Yaml.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QTemporaryFile>

#include <QtTest/QtTest>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

class TestPaths : public QObject
{
    Q_OBJECT
public:
    TestPaths() {};
    virtual ~TestPaths() {};

private Q_SLOTS:
    void initTestCase();

    void testTargetPath();

private:
    CalamaresUtils::System* m_system;  // Points to singleton instance, not owned
};

void
TestPaths::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    // Ensure we have a system object, expect it to be a "bogus" one
    CalamaresUtils::System* system = CalamaresUtils::System::instance();
    QVERIFY( system );
    QVERIFY( system->doChroot() );

    // Ensure we have a system-wide GlobalStorage with /tmp as root
    if ( !Calamares::JobQueue::instance() )
    {
        (void)new Calamares::JobQueue();
    }
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );
    gs->insert( "rootMountPoint", "/tmp" );

    m_system = system;
}


void
TestPaths::testTargetPath()
{
    // Paths mapped normally
    QCOMPARE( m_system->targetPath( "/etc/calamares" ), QStringLiteral( "/tmp/etc/calamares" ) );
    QCOMPARE( m_system->targetPath( "//etc//calamares" ), QStringLiteral( "/tmp/etc/calamares" ) );  // extra /
    QCOMPARE( m_system->targetPath( "etc/calamares" ), QString() );  // NOT ABSOLUTE
}

QTEST_GUILESS_MAIN( TestPaths )

#include "utils/moc-warnings.h"

#include "TestPaths.moc"
