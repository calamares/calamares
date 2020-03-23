/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "ResizeFSJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

#include <QFileInfo>
#include <QStringList>

using SizeUnit = CalamaresUtils::Partition::SizeUnit;

QTEST_GUILESS_MAIN( FSResizerTests )

FSResizerTests::FSResizerTests()
{
}

FSResizerTests::~FSResizerTests()
{
}

void
FSResizerTests::initTestCase()
{
}

void FSResizerTests::testConfigurationRobust()
{
    ResizeFSJob j;

    // Empty config
    j.setConfigurationMap( QVariantMap() );
    QVERIFY( j.name().isEmpty() );
    QCOMPARE( j.size().unit(), SizeUnit::None );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::None );

    // Config is missing fs and dev, so it isn't valid
    YAML::Node doc0 = YAML::Load( R"(---
size: 100%
atleast: 600MiB
)" );
    j.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc0 ) );
    QVERIFY( j.name().isEmpty() );
    QCOMPARE( j.size().unit(), SizeUnit::None );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::None );
    QCOMPARE( j.size().value(), 0 );
    QCOMPARE( j.minimumSize().value(), 0 );
}

void FSResizerTests::testConfigurationValues()
{
    ResizeFSJob j;

    // Check both
    YAML::Node doc0 = YAML::Load( R"(---
fs: /
size: 100%
atleast: 600MiB
)" );
    j.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc0 ) );
    QVERIFY( !j.name().isEmpty() );
    QCOMPARE( j.name(), QString("/") );
    QCOMPARE( j.size().unit(), SizeUnit::Percent );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::MiB );
    QCOMPARE( j.size().value(), 100 );
    QCOMPARE( j.minimumSize().value(), 600 );

    // Silly config has bad atleast value
    doc0 = YAML::Load( R"(---
fs: /
dev: /dev/m00
size: 72  MiB
atleast: 127 %
)" );
    j.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc0 ) );
    QVERIFY( !j.name().isEmpty() );
    QCOMPARE( j.name(), QString("/") );
    QCOMPARE( j.size().unit(), SizeUnit::MiB );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::None );
    QCOMPARE( j.size().value(), 72 );
    QCOMPARE( j.minimumSize().value(), 0 );

    // Silly config has bad atleast value
    doc0 = YAML::Load( R"(---
dev: /dev/m00
size: 72  MiB
atleast: 127 %
)" );
    j.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc0 ) );
    QVERIFY( !j.name().isEmpty() );
    QCOMPARE( j.name(), QString("/dev/m00") );
    QCOMPARE( j.size().unit(), SizeUnit::MiB );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::None );
    QCOMPARE( j.size().value(), 72 );
    QCOMPARE( j.minimumSize().value(), 0 );

    // Normal config
    doc0 = YAML::Load( R"(---
fs: /
# dev: /dev/m00
size: 71MiB
# atleast: 127%
)" );
    j.setConfigurationMap( CalamaresUtils::yamlMapToVariant( doc0 ) );
    QVERIFY( !j.name().isEmpty() );
    QCOMPARE( j.name(), QString("/") );
    QCOMPARE( j.size().unit(), SizeUnit::MiB );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::None );
    QCOMPARE( j.size().value(), 71 );
    QCOMPARE( j.minimumSize().value(), 0 );
}
