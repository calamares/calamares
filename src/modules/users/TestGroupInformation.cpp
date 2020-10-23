/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CreateUserJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"

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
}

void
GroupTests::testReadGroup()
{
    Calamares::JobQueue::instance()->globalStorage()->insert( "rootMountPoint", "/" );
    // Get the groups in the host system
    QStringList groups = groupsInTargetSystem();
    QVERIFY( groups.count() > 2 );
#ifdef __FreeBSD__
    QVERIFY( groups.contains( QStringLiteral( "wheel" ) ) );
#else
    QVERIFY( groups.contains( QStringLiteral( "root" ) ) );
#endif
    // openSUSE doesn't have "sys"
    // QVERIFY( groups.contains( QStringLiteral( "sys" ) ) );
    QVERIFY( groups.contains( QStringLiteral( "nogroup" ) ) );
    QVERIFY( groups.contains( QStringLiteral( "tty" ) ) );

    for ( const QString& s : groups )
    {
        QVERIFY( !s.isEmpty() );
        QVERIFY( !s.contains( '#' ) );
    }
}

QTEST_GUILESS_MAIN( GroupTests )

#include "utils/moc-warnings.h"

#include "TestGroupInformation.moc"
