/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "jobs/AutoMountManagementJob.h"

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
    cDebug() << "Got automount info" << Logger::Pointer( original.get() );

    AutoMountManagementJob j( false );
    QVERIFY( j.exec() );
    QVERIFY( j.exec() );
    QVERIFY( j.exec() );

    CalamaresUtils::Partition::automountRestore( original );
}


QTEST_GUILESS_MAIN( AutoMountJobTests )

#include "utils/moc-warnings.h"

#include "AutoMountTests.moc"
