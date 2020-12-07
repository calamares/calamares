/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "CalamaresUtilsSystem.h"
#include "Entropy.h"
#include "Logger.h"
#include "UMask.h"
#include "Yaml.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QDir>
#include <QtTest/QtTest>

class TestPaths : public QObject
{
    Q_OBJECT
public:
    TestPaths() {}
    ~TestPaths() override {}

private Q_SLOTS:
    void initTestCase();
    void init();
    void cleanupTestCase();

    void testCreationResult();
    void testTargetPath();
    void testCreateTarget();
    void testCreateTargetExists();
    void testCreateTargetOverwrite();
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
TestPaths::testCreationResult()
{
    using Code = CalamaresUtils::CreationResult::Code;

    for ( auto c : { Code::OK, Code::AlreadyExists, Code::Failed, Code::Invalid } )
    {
        auto r = CalamaresUtils::CreationResult( c );
        QVERIFY( r.path().isEmpty() );
        QCOMPARE( r.path(), QString() );
        // Get a warning from Clang if we're not covering everything
        switch ( r.code() )
        {
        case Code::OK:
            QVERIFY( !r.failed() );
            QVERIFY( r );
            break;
        case Code::AlreadyExists:
            QVERIFY( !r.failed() );
            QVERIFY( !r );
            break;
        case Code::Failed:
        case Code::Invalid:
            QVERIFY( r.failed() );
            QVERIFY( !r );
            break;
        }
    }

    QString path( "/etc/os-release" );
    auto r = CalamaresUtils::CreationResult( path );
    QVERIFY( !r.failed() );
    QVERIFY( r );
    QCOMPARE( r.code(), Code::OK );
    QCOMPARE( r.path(), path );
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
    auto r = m_system->createTargetFile( testFile, "Hello" );
    QVERIFY( !r.failed() );
    QVERIFY( r );
    QCOMPARE( r.path(), QString( absFile ) );  // Success

    QFileInfo fi( absFile );
    QVERIFY( fi.exists() );
    QCOMPARE( fi.size(), 5 );

    m_system->removeTargetFile( testFile );
    QFileInfo fi2( absFile );  // fi caches information
    QVERIFY( !fi2.exists() );
}

struct GSRollback
{
    GSRollback( const QString& key )
        : m_key( key )
        , m_value( Calamares::JobQueue::instance()->globalStorage()->value( key ) )
    {
    }
    ~GSRollback() { Calamares::JobQueue::instance()->globalStorage()->insert( m_key, m_value ); }
    QString m_key;
    QVariant m_value;
};


void
TestPaths::testCreateTargetExists()
{
    static const char ltestFile[] = "cala-test-world";
    GSRollback g( QStringLiteral( "rootMountPoint" ) );

    QTemporaryDir d;
    d.setAutoRemove( true );
    Calamares::JobQueue::instance()->globalStorage()->insert( QStringLiteral( "rootMountPoint" ), d.path() );

    QVERIFY( QFileInfo( d.path() ).exists() );
    auto r = m_system->createTargetFile( ltestFile, "Hello" );
    QVERIFY( r );
    QVERIFY( r.path().endsWith( QString( ltestFile ) ) );
    QCOMPARE( QFileInfo( d.filePath( QString( ltestFile ) ) ).size(), 5 );

    r = m_system->createTargetFile( ltestFile, "Goodbye" );
    QVERIFY( !r.failed() );  // It didn't fail!
    QVERIFY( !r );  // But not unqualified success, either

    QVERIFY( r.path().isEmpty() );
    QCOMPARE( QFileInfo( d.filePath( QString( ltestFile ) ) ).size(), 5 );  // Unchanged!
}

void
TestPaths::testCreateTargetOverwrite()
{
    static const char ltestFile[] = "cala-test-world";
    GSRollback g( QStringLiteral( "rootMountPoint" ) );

    QTemporaryDir d;
    d.setAutoRemove( true );
    Calamares::JobQueue::instance()->globalStorage()->insert( QStringLiteral( "rootMountPoint" ), d.path() );

    QVERIFY( QFileInfo( d.path() ).exists() );
    auto r = m_system->createTargetFile( ltestFile, "Hello" );
    QVERIFY( r );
    QVERIFY( r.path().endsWith( QString( ltestFile ) ) );
    QCOMPARE( QFileInfo( d.filePath( QString( ltestFile ) ) ).size(), 5 );

    r = m_system->createTargetFile( ltestFile, "Goodbye", CalamaresUtils::System::WriteMode::KeepExisting );
    QVERIFY( !r.failed() );  // It didn't fail!
    QVERIFY( !r );  // But not unqualified success, either

    QVERIFY( r.path().isEmpty() );
    QCOMPARE( QFileInfo( d.filePath( QString( ltestFile ) ) ).size(), 5 );  // Unchanged!

    r = m_system->createTargetFile( ltestFile, "Goodbye", CalamaresUtils::System::WriteMode::Overwrite );
    QVERIFY( !r.failed() );  // It didn't fail!
    QVERIFY( r );  // Total success

    QVERIFY( r.path().endsWith( QString( ltestFile ) ) );
    QCOMPARE( QFileInfo( d.filePath( QString( ltestFile ) ) ).size(), 7 );
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
