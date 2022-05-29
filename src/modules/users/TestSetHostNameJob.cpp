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

#include <unistd.h>

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
    QString m_originalHostName;
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

    if ( m_originalHostName.isEmpty() )
    {
        QFile hostname( QStringLiteral( "/etc/hostname" ) );
        if ( hostname.exists() && hostname.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            m_originalHostName = hostname.readAll().trimmed();
        }
    }
}

void
UsersTests::testEtcHostname()
{
    cDebug() << "Test dir" << m_dir.path();

    QVERIFY( QFile::exists( m_dir.path() ) );
    QVERIFY( !QFile::exists( m_dir.filePath( "etc" ) ) );

    const QString testHostname = QStringLiteral( "tubophone.calamares.io" );
    // Doesn't create intermediate directories
    QVERIFY( !setFileHostname( testHostname ) );

    QVERIFY( CalamaresUtils::System::instance()->createTargetDirs( "/etc" ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc" ) ) );

    // Does write the file
    QVERIFY( setFileHostname( testHostname ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc/hostname" ) ) );

    // 22 for the test string, above, and 1 for the newline
    QCOMPARE( QFileInfo( m_dir.filePath( "etc/hostname" ) ).size(), testHostname.length() + 1 );
}

void
UsersTests::testEtcHosts()
{
    // Assume previous tests did their work
    QVERIFY( QFile::exists( m_dir.path() ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc" ) ) );

    const QString testHostname = QStringLiteral( "tubophone.calamares.io" );
    QVERIFY( writeFileEtcHosts( testHostname ) );
    QVERIFY( QFile::exists( m_dir.filePath( "etc/hosts" ) ) );
    // The skeleton contains %1 which has the hostname substituted in, so we lose two,
    // and the rest of the blabla is 145 (the "standard" part) and 34 (the "for this host" part)
    QCOMPARE( QFileInfo( m_dir.filePath( "etc/hosts" ) ).size(), 145 + 34 + testHostname.length() - 2 );
}

void
UsersTests::testHostnamed()
{
    // Since the service might not be running (e.g. non-systemd systems,
    // FreeBSD, docker, ..) we're not going to fail a test here.
    // There's also the permissions problem to think of. But if we're
    // root, assume it will succeed.
    if ( geteuid() != 0 )
    {
        QEXPECT_FAIL( "", "Hostname changes are access-controlled", Continue );
    }
    QVERIFY( setSystemdHostname( QStringLiteral( "tubophone.calamares.io" ) ) );
    if ( !m_originalHostName.isEmpty() )
    {
        // If the previous test succeeded (to change the hostname to something bogus)
        // then this one should, also; or, if the previous one failed, then this
        // changes to whatever-the-hostname-is, and systemd dbus seems to call that
        // a success, as well (since nothing changes). So no failure-expectation here.
        setSystemdHostname( m_originalHostName );
    }
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
