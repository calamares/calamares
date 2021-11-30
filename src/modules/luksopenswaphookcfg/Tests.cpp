/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "utils/Logger.h"

#include <QtTest/QtTest>

// LOSH = LUKS Open Swap Hook (Job)

class LOSHTests : public QObject
{
    Q_OBJECT
public:
    LOSHTests();
    ~LOSHTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testTrue();
};

LOSHTests::LOSHTests() {}

void
LOSHTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "LOSH test started.";
}

#include "utils/moc-warnings.h"

#include "Tests.moc"
