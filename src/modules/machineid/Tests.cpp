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
    virtual ~MachineIdTests() {}

private Q_SLOTS:
    void initTestCase();

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
        QVERIFY( system->createTargetDirs("/etc") );
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
        QCOMPARE( fi.size(), 5);
#endif
    }
    tempRoot.setAutoRemove( true );  // All tests succeeded
}

QTEST_GUILESS_MAIN( MachineIdTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
