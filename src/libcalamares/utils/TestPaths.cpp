/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, 2020, Adriaan de Groot <groot@kde.org>
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

#include <QDir>
// #include <QTemporaryFile>

#include <QtTest/QtTest>

// #include <fcntl.h>
// #include <sys/stat.h>
// #include <unistd.h>

class TestPaths : public QObject
{
    Q_OBJECT
public:
    TestPaths() {}
    virtual ~TestPaths() {}

private Q_SLOTS:
    void initTestCase();
    void init();
    void cleanupTestCase();

    void testTargetPath();
    void testCreateTarget();
    void testCreateTargetBasedirs();

private:
    CalamaresUtils::System* m_system = nullptr;  // Points to singleton instance, not owned
    Calamares::GlobalStorage* m_gs = nullptr;
};

static const char testFile[] = "/calamares-testcreate";
static const char absFile[] = "/tmp/calamares-testcreate";  // With rootMountPoint prepended

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
        cDebug() << "Creating new JobQueue";
        (void)new Calamares::JobQueue();
    }
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );

    m_system = system;
    m_gs = gs;
}

void
TestPaths::cleanupTestCase()
{
    QFile::remove( absFile );
}

void
TestPaths::init()
{
    cDebug() << "Setting rootMountPoint";
    m_gs->insert( "rootMountPoint", "/tmp" );
}


void
TestPaths::testTargetPath()
{
    // Paths mapped normally
    QCOMPARE( m_system->targetPath( "/etc/calamares" ), QStringLiteral( "/tmp/etc/calamares" ) );
    QCOMPARE( m_system->targetPath( "//etc//calamares" ),
              QStringLiteral( "/tmp//etc//calamares" ) );  // extra / are not cleaned up
    QCOMPARE( m_system->targetPath( "etc/calamares" ), QStringLiteral( "/tmp/etc/calamares" ) );  // relative to root

    // Weird Paths
    QCOMPARE( m_system->targetPath( QString() ), QStringLiteral( "/tmp/" ) );

    // Now break GS
    m_gs->remove( "rootMountPoint" );
    QCOMPARE( m_system->targetPath( QString() ), QString() );  // Without root, no path
}


void
TestPaths::testCreateTarget()
{
    QCOMPARE( m_system->createTargetFile( testFile, "Hello" ), QString( absFile ) );  // Success

    QFileInfo fi( absFile );
    QVERIFY( fi.exists() );
    QCOMPARE( fi.size(), 5 );

    m_system->removeTargetFile( testFile );
    QFileInfo fi2( absFile );  // fi caches information
    QVERIFY( !fi2.exists() );
}

struct DirRemover
{
    DirRemover( const QString& base, const QString& dir )
        : m_base( base )
        , m_dir( dir )
    {
    }
    ~DirRemover() { QDir( m_base ).rmpath( m_dir ); }

    bool exists() const { return QDir( m_base ).exists( m_dir ); }

    QString m_base, m_dir;
};

void
TestPaths::testCreateTargetBasedirs()
{
    {
        DirRemover dirrm( "/tmp", "var/lib/dbus" );
        QVERIFY( m_system->createTargetDirs( "/" ) );
        QVERIFY( m_system->createTargetDirs( "/var/lib/dbus" ) );
        QVERIFY( QFile( "/tmp/var/lib/dbus" ).exists() );
        QVERIFY( dirrm.exists() );
    }
    QVERIFY( !QFile( "/tmp/var/lib/dbus" ).exists() );

    // QFileInfo.dir() behaves even when things don't exist
    QCOMPARE( QFileInfo( "/tmp/var/lib/dbus/bogus" ).dir().path(), QStringLiteral( "/tmp/var/lib/dbus" ) );
}

QTEST_GUILESS_MAIN( TestPaths )

#include "utils/moc-warnings.h"

#include "TestPaths.moc"
