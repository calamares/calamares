/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "jobs/AutoMountManagementJob.h"

#include "JobQueue.h"
#include "utils/Logger.h"

#include <QObject>
#include <QtTest/QtTest>

class AutoMountJobTests : public QObject
{
    Q_OBJECT
public:
    AutoMountJobTests();

private Q_SLOTS:
    void testRunThrice();
    void testRunQueue();
};

AutoMountJobTests::AutoMountJobTests() {}

/* This doesn't really test anything, since automount management
 * is supposed to be opaque: the job always returns true. What
 * is interesting is the debug output, where the job informs
 * about the pointer it holds.
 *
 * That should output 0, then non-zero, then 0 again.
 *
 */
void
AutoMountJobTests::testRunThrice()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    auto original = CalamaresUtils::Partition::automountDisable( true );
    cDebug() << "Got automount info" << Logger::Pointer( original );

    AutoMountManagementJob j( false );
    QVERIFY( j.exec() );
    QVERIFY( j.exec() );
    QVERIFY( j.exec() );

    CalamaresUtils::Partition::automountRestore( original );
}

void
AutoMountJobTests::testRunQueue()
{
    Calamares::JobQueue q;
    Calamares::job_ptr jp( new AutoMountManagementJob( false ) );
    QSignalSpy progress( &q, &Calamares::JobQueue::progress );
    QSignalSpy finish( &q, &Calamares::JobQueue::finished );
    QSignalSpy fail( &q, &Calamares::JobQueue::failed );

    Logger::setupLogLevel( Logger::LOGVERBOSE );
    cDebug() << "Got automount job" << jp;

    QVERIFY( !q.isRunning() );
    q.enqueue( 2, { jp, jp } );
    QVERIFY( !q.isRunning() );

    QEventLoop loop;
    QTimer::singleShot( std::chrono::milliseconds( 100 ), [ &q ]() { q.start(); } );
    QTimer::singleShot( std::chrono::milliseconds( 5000 ), [ &loop ]() { loop.quit(); } );
    connect( &q, &Calamares::JobQueue::finished, &loop, &QEventLoop::quit );
    loop.exec();

    QCOMPARE( fail.count(), 0 );
    QCOMPARE( finish.count(), 1 );
    // 5 progress: 0% and 100% for each *job* and then 100% overall
    QCOMPARE( progress.count(), 5 );
}


QTEST_GUILESS_MAIN( AutoMountJobTests )

#include "utils/moc-warnings.h"

#include "AutoMountTests.moc"
