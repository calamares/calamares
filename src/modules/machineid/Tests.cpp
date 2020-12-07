/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "MachineIdJob.h"
#include "Workers.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QDir>
#include <QFile>
#include <QtTest/QtTest>

// Internals of Workers.cpp
extern int getUrandomPoolSize();

class MachineIdTests : public QObject
{
    Q_OBJECT
public:
    MachineIdTests() {}
    ~MachineIdTests() override {}

private Q_SLOTS:
    void initTestCase();
    void testConfigEntropyFiles();

    void testCopyFile();

    void testPoolSize();

    void testJob();
};

void
MachineIdTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
MachineIdTests::testConfigEntropyFiles()
{
    static QString urandom_entropy( "/var/lib/urandom/random-seed" );
    // No config at all
    {
        QVariantMap m;
        MachineIdJob j;
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames(), QStringList() );
    }
    // No entropy, deprecated setting
    {
        QVariantMap m;
        MachineIdJob j;
        m.insert( "entropy", false );
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames(), QStringList() );
    }
    // Entropy, deprecated setting
    {
        QVariantMap m;
        MachineIdJob j;
        m.insert( "entropy", true );
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames(), QStringList { urandom_entropy } );
    }
    // Duplicate entry, with deprecated setting
    {
        QVariantMap m;
        MachineIdJob j;
        m.insert( "entropy", true );
        m.insert( "entropy-files", QStringList { urandom_entropy } );
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames(), QStringList { urandom_entropy } );

        m.clear();
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames(), QStringList() );

        // This would be weird
        m.insert( "entropy", false );
        m.insert( "entropy-files", QStringList { urandom_entropy } );
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames(), QStringList { urandom_entropy } );
    }
    // No deprecated setting
    {
        QString tmp_entropy( "/tmp/entropy" );
        QVariantMap m;
        MachineIdJob j;
        m.insert( "entropy-files", QStringList { urandom_entropy, tmp_entropy } );
        j.setConfigurationMap( m );
        QVERIFY( !j.entropyFileNames().isEmpty() );
        QCOMPARE( j.entropyFileNames(), QStringList() << urandom_entropy << tmp_entropy );
    }
}


void
MachineIdTests::testCopyFile()
{
    QTemporaryDir tempRoot( QDir::tempPath() + QStringLiteral( "/test-root-XXXXXX" ) );
    cDebug() << "Temporary files as" << QDir::tempPath();
    cDebug() << "Temp dir file at  " << tempRoot.path();
    QVERIFY( !tempRoot.path().isEmpty() );

    // This will pretend to be the host system
    QTemporaryDir tempISOdir( QDir::tempPath() + QStringLiteral( "/test-live-XXXXXX" ) );
    QVERIFY( QDir( tempRoot.path() ).mkpath( tempRoot.path() + tempISOdir.path() ) );

    QFile source( tempRoot.filePath( "example" ) );
    QVERIFY( !source.exists() );
    source.open( QIODevice::WriteOnly );
    source.write( "Derp" );
    source.close();
    QCOMPARE( source.size(), 4 );
    QVERIFY( source.exists() );

    // This should fail since "example" isn't standard in our test directory
    auto r0 = MachineId::copyFile( tempRoot.path(), "example" );
    QVERIFY( !r0 );

    const QString sampleFile = QStringLiteral( "CMakeCache.txt" );
    if ( QFile::exists( sampleFile ) )
    {
        auto r1 = MachineId::copyFile( tempRoot.path(), sampleFile );
        // Also fail, because it's not an absolute path
        QVERIFY( !r1 );

        QVERIFY( QFile::copy( sampleFile, tempISOdir.path() + '/' + sampleFile ) );
        auto r2 = MachineId::copyFile( tempRoot.path(), tempISOdir.path() + '/' + sampleFile );
        QVERIFY( r2 );
    }
}

void
MachineIdTests::testPoolSize()
{
#ifdef Q_OS_FREEBSD
    // It hardly makes sense, but also the /proc entry is missing
    QCOMPARE( getUrandomPoolSize(), 512 );
#else
    // Based on a sample size of 1, Netrunner
    QCOMPARE( getUrandomPoolSize(), 4096 );
#endif
}

void
MachineIdTests::testJob()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    QTemporaryDir tempRoot( QDir::tempPath() + QStringLiteral( "/test-job-XXXXXX" ) );
    // Only clean up if the tests succeed
    tempRoot.setAutoRemove( false );
    cDebug() << "Temporary files as" << QDir::tempPath();

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
    gs->insert( "rootMountPoint", tempRoot.path() );

    // Prepare part of the target filesystem
    {
        QVERIFY( system->createTargetDirs( "/etc" ) );
        auto r = system->createTargetFile( "/etc/machine-id", "Hello" );
        QVERIFY( !r.failed() );
        QVERIFY( r );
        QVERIFY( !r.path().isEmpty() );
    }

    MachineIdJob job( nullptr );
    QVERIFY( !job.prettyName().isEmpty() );

    QVariantMap config;
    config.insert( "dbus", true );
    job.setConfigurationMap( config );

    {
        auto r = job.exec();
        QVERIFY( !r );  // It's supposed to fail, because no dbus-uuidgen executable exists
        QVERIFY( QFile::exists( tempRoot.filePath( "var/lib/dbus" ) ) );  // but the target dir exists
    }

    config.insert( "dbus-symlink", true );
    job.setConfigurationMap( config );
    {
        auto r = job.exec();
        QVERIFY( !r );  // It's supposed to fail, because no dbus-uuidgen executable exists
        QVERIFY( QFile::exists( tempRoot.filePath( "var/lib/dbus" ) ) );  // but the target dir exists

        // These all (would) fail, because the chroot isn't viable
#if 0
        QVERIFY( QFile::exists( "/tmp/var/lib/dbus/machine-id" ) );

        QFileInfo fi( "/tmp/var/lib/dbus/machine-id" );
        QVERIFY( fi.exists() );
        QVERIFY( fi.isSymLink() );
        QCOMPARE( fi.size(), 5 );
#endif
    }

    {
        QString tmp_entropy2( "/pineapple.random" );
        QString tmp_entropy( "/tmp/entropy" );
        QVariantMap m;
        MachineIdJob j;
        m.insert( "entropy-files", QStringList { tmp_entropy2, tmp_entropy } );
        m.insert( "entropy", true );
        j.setConfigurationMap( m );
        QCOMPARE( j.entropyFileNames().count(), 3 );  // Because of the standard entropy entry

        // Check all three are created
        auto r = j.exec();
        QVERIFY( r );
        for ( const auto& fileName : j.entropyFileNames() )
        {
            cDebug() << "Verifying existence of" << fileName;
            QVERIFY( QFile::exists( tempRoot.filePath( fileName.mid( 1 ) ) ) );
        }
    }

    tempRoot.setAutoRemove( true );  // All tests succeeded
}

QTEST_GUILESS_MAIN( MachineIdTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
