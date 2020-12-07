/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Tests.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

#include <QFileInfo>
#include <QStringList>

extern void fixPermissions( const QDir& d );

QTEST_GUILESS_MAIN( InitcpioTests )

InitcpioTests::InitcpioTests() {}

InitcpioTests::~InitcpioTests() {}

void
InitcpioTests::initTestCase()
{
}

void
InitcpioTests::testFixPermissions()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Fixing up /boot";
    fixPermissions( QDir( "/boot" ) );
    cDebug() << "Fixing up /nonexistent";
    fixPermissions( QDir( "/nonexistent/nonexistent" ) );
    QVERIFY( true );
}
