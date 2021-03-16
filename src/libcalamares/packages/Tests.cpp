/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "utils/Logger.h"

#include "GlobalStorage.h"

#include <QtTest/QtTest>

class PackagesTests : public QObject
{
    Q_OBJECT
public:
    PackagesTests() {}
    ~PackagesTests() override {}
private Q_SLOTS:
    void initTestCase();

    void testEmpty();
};

void
PackagesTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
PackagesTests::testEmpty()
{
}


QTEST_GUILESS_MAIN( PackagesTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
