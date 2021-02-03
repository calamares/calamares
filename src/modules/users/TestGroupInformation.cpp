/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"
#include "CreateUserJob.h"
#include "MiscJobs.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QDir>
#include <QtTest/QtTest>

// Implementation details
extern QStringList groupsInTargetSystem();  // CreateUserJob

class GroupTests : public QObject
{
    Q_OBJECT
public:
    GroupTests();
    ~GroupTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testReadGroup();
    void testCreateGroup();

    void testSudoGroup();
    void testJobCreation();
};

GroupTests::GroupTests() {}

void
GroupTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Users test started.";
    if ( !Calamares::JobQueue::instance() )
    {
        (void)new Calamares::JobQueue();
    }
    Calamares::JobQueue::instance()->globalStorage()->insert( "rootMountPoint", "/" );
}

void
GroupTests::testReadGroup()
{
    // Get the groups in the host system
    QStringList groups = groupsInTargetSystem();
    QVERIFY( groups.count() > 2 );
#ifdef __FreeBSD__
    QVERIFY( groups.contains( QStringLiteral( "wheel" ) ) );
#else
    QVERIFY( groups.contains( QStringLiteral( "root" ) ) );
#endif
    QVERIFY( groups.contains( QStringLiteral( "tty" ) ) );
    // openSUSE doesn't have "sys", KaOS doesn't have "nogroup"
    QVERIFY( groups.contains( QStringLiteral( "sys" ) ) || groups.contains( QStringLiteral( "nogroup" ) ) );

    for ( const QString& s : groups )
    {
        QVERIFY( !s.isEmpty() );
        QVERIFY( !s.contains( '#' ) );
    }
}

void
GroupTests::testCreateGroup()
{
    // BUILD_AS_TEST is the source-directory path
    QFile fi( QString( "%1/tests/5-issue-1523.conf" ).arg( BUILD_AS_TEST ) );
    QVERIFY( fi.exists() );

    bool ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &ok );
    QVERIFY( ok );
    QVERIFY( map.count() > 0 );  // Just that it loaded, one key *defaultGroups*

    Config c;
    c.setConfigurationMap( map );

    QCOMPARE( c.defaultGroups().count(), 4 );
    QVERIFY( c.defaultGroups().contains( QStringLiteral( "adm" ) ) );
    QVERIFY( c.defaultGroups().contains( QStringLiteral( "bar" ) ) );

    Calamares::JobQueue::instance()->globalStorage()->insert( "rootMountPoint", "/" );

    SetupGroupsJob j( &c );
    QVERIFY( !j.exec() );  // running as regular user this should fail
}

void
GroupTests::testSudoGroup()
{
    // Test programmatic changes
    {
        Config c;
        QSignalSpy spy( &c, &Config::sudoersGroupChanged );
        QCOMPARE( c.sudoersGroup(), QString() );
        c.setSudoersGroup( QStringLiteral( "wheel" ) );
        QCOMPARE( c.sudoersGroup(), QStringLiteral( "wheel" ) );
        QCOMPARE( spy.count(), 1 );  // Changed to wheel
        // Do it again, no change
        c.setSudoersGroup( QStringLiteral( "wheel" ) );
        QCOMPARE( c.sudoersGroup(), QStringLiteral( "wheel" ) );
        QCOMPARE( spy.count(), 1 );
        c.setSudoersGroup( QStringLiteral( "roue" ) );
        QCOMPARE( c.sudoersGroup(), QStringLiteral( "roue" ) );
        QCOMPARE( spy.count(), 2 );
    }


    // Test config loading
    {
        Config c;
        QSignalSpy spy( &c, &Config::sudoersGroupChanged );
        QCOMPARE( c.sudoersGroup(), QString() );

        QVariantMap m;
        c.setConfigurationMap( m );
        QCOMPARE( c.sudoersGroup(), QString() );
        QCOMPARE( spy.count(), 0 );  // Unchanged

        const auto key = QStringLiteral( "sudoersGroup" );
        const auto v0 = QStringLiteral( "wheel" );
        const auto v1 = QStringLiteral( "roue" );
        m.insert( key, v0 );
        c.setConfigurationMap( m );
        QCOMPARE( c.sudoersGroup(), v0 );
        QCOMPARE( spy.count(), 1 );
    }
}

/** @brief Are all the expected jobs (and no others) created?
 *
 * - A sudo job is created only when the sudoers group is set;
 * - Groups job
 * - User job
 * - Password job
 * - Root password job
 * - Hostname job are always created.
 */
void
GroupTests::testJobCreation()
{
    const int expectedJobs = 5;
    Config c;
    QVERIFY( !c.isReady() );

    // Needs some setup
    c.setFullName( QStringLiteral( "Goodluck Jonathan" ) );
    c.setLoginName( QStringLiteral( "goodj" ) );
    QVERIFY( c.isReady() );

    QCOMPARE( c.sudoersGroup(), QString() );
    QCOMPARE( c.createJobs().count(), expectedJobs );

    c.setSudoersGroup( QStringLiteral( "wheel" ) );
    QCOMPARE( c.sudoersGroup(), QString( "wheel" ) );
    QCOMPARE( c.createJobs().count(), expectedJobs + 1 );
}


QTEST_GUILESS_MAIN( GroupTests )

#include "utils/moc-warnings.h"

#include "TestGroupInformation.moc"
