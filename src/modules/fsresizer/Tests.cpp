/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

FSResizerTests::FSResizerTests() {}

FSResizerTests::~FSResizerTests() {}

void
FSResizerTests::initTestCase()
{
}

void
FSResizerTests::testConfigurationRobust()
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

void
FSResizerTests::testConfigurationValues()
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
    QCOMPARE( j.name(), QString( "/" ) );
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
    QCOMPARE( j.name(), QString( "/" ) );
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
    QCOMPARE( j.name(), QString( "/dev/m00" ) );
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
    QCOMPARE( j.name(), QString( "/" ) );
    QCOMPARE( j.size().unit(), SizeUnit::MiB );
    QCOMPARE( j.minimumSize().unit(), SizeUnit::None );
    QCOMPARE( j.size().value(), 71 );
    QCOMPARE( j.minimumSize().value(), 0 );
}
