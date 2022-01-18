/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "UmountJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QDir>
#include <QFile>
#include <QtTest/QtTest>

// Internals of UmountJob.cpp

// Actual tests
class UmountTests : public QObject
{
    Q_OBJECT
public:
    UmountTests() {}
    ~UmountTests() override {}

private Q_SLOTS:
    void initTestCase();
    void testTrue();
};

void
UmountTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
UmountTests::testTrue()
{
    QVERIFY( true );
}

QTEST_GUILESS_MAIN( UmountTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
