/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
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

InitcpioTests::InitcpioTests()
{
}

InitcpioTests::~InitcpioTests()
{
}

void
InitcpioTests::initTestCase()
{
}

void InitcpioTests::testFixPermissions()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Fixing up /boot";
    fixPermissions( QDir( "/boot" ) );
    cDebug() << "Fixing up /nonexistent";
    fixPermissions( QDir( "/nonexistent/nonexistent" ) );
    QVERIFY( true );
}

