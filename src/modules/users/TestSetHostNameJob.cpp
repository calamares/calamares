/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SetHostNameJob.h"

// Implementation details
extern bool setFileHostname( const QString& );
extern bool writeFileEtcHosts( const QString& );
extern bool setSystemdHostname( const QString& );

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QTemporaryDir>
#include <QtTest/QtTest>

class UsersTests : public QObject
{
    Q_OBJECT
public:
    UsersTests();
    ~UsersTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testEtcHostname();
    void testEtcHosts();
    void testHostnamed();

    void cleanup();

private:
    QTemporaryDir m_dir;
};

UsersTests::UsersTests()
    : m_dir( QStringLiteral( "/tmp/calamares-usertest" ) )
{
}

void
UsersTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Users test started.";
    cDebug() << "Test dir" << m_dir.path();

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
    gs->insert( "rootMountPoint", m_dir.path() );
}

void
UsersTests::testEtcHostname()
{
    cDebug() << "Test dir" << m_dir.path();

    QVERIFY( QFile::exists( m_dir.path() ) );
    QVERIFY( !QFile::exists( m_dir.filePath( "etc" ) ) );

    // Doesn't create intermediate directories
    QVERIFY( !setFileHostname( QStringLiteral( "tubophone.calamares.io" ) ) );

    QVERIFY( CalamaresUtils::System::instance()->createTargetDirs( "/etc" ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc" ) ) );

    // Does write the file
    QVERIFY( setFileHostname( QStringLiteral( "tubophone.calamares.io" ) ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc/hostname" ) ) );

    // 22 for the test string, above, and 1 for the newline
    QCOMPARE( QFileInfo( m_dir.filePath( "etc/hostname" ) ).size(), 22 + 1 );
}

void
UsersTests::testEtcHosts()
{
    // Assume previous tests did their work
    QVERIFY( QFile::exists( m_dir.path() ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc" ) ) );

    QVERIFY( writeFileEtcHosts( QStringLiteral( "tubophone.calamares.io" ) ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc/hosts" ) ) );
    // The skeleton contains %1 which has the hostname substituted in, so we lose two,
    // and the rest of the blabla is 150 (according to Python)
    QCOMPARE( QFileInfo( m_dir.filePath( "etc/hosts" ) ).size(), 150 + 22 - 2 );
}

void
UsersTests::testHostnamed()
{
    // Since the service might not be running (e.g. non-systemd systems,
    // FreeBSD, docker, ..) we're not going to fail a test here.
    // There's also the permissions problem to think of.
    QEXPECT_FAIL( "", "Hostname changes are access-controlled", Continue );
    QVERIFY( setSystemdHostname( "tubophone.calamares.io" ) );
}


void
UsersTests::cleanup()
{
    if ( QTest::currentTestFailed() )
    {
        m_dir.setAutoRemove( false );
    }
}


QTEST_GUILESS_MAIN( UsersTests )

#include "utils/moc-warnings.h"

#include "TestSetHostNameJob.moc"
