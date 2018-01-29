/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "utils/CommandList.h"
#include "utils/YamlUtils.h"

#include <yaml-cpp/yaml.h>

#include <QtTest/QtTest>

#include <QFileInfo>
#include <QStringList>

QTEST_GUILESS_MAIN( ShellProcessTests )

using CommandList = CalamaresUtils::CommandList;

ShellProcessTests::ShellProcessTests()
{
}

ShellProcessTests::~ShellProcessTests()
{
}

void
ShellProcessTests::initTestCase()
{
}

void
ShellProcessTests::testProcessListSampleConfig()
{
    YAML::Node doc;

    QStringList dirs { "src/modules/shellprocess", "." };
    for ( const auto& dir : dirs )
    {
        QString filename = dir + "/shellprocess.conf";
        if ( QFileInfo::exists( filename ) )
        {
            doc = YAML::LoadFile( filename.toStdString() );
            break;
        }
    }

    CommandList cl(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 3 );
    QCOMPARE( cl.at(0).timeout(), -1 );
    QCOMPARE( cl.at(2).timeout(), 3600 );  // slowloris
}

void ShellProcessTests::testProcessListFromList()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    - "ls /tmp"
    - "ls /nonexistent"
    - "/bin/false"
)" );
    CommandList cl(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 3 );

    // Contains 1 bad element
    doc = YAML::Load( R"(---
script:
    - "ls /tmp"
    - false
    - "ls /nonexistent"
)" );
    CommandList cl1(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( !cl1.isEmpty() );
    QCOMPARE( cl1.count(), 2 );  // One element ignored
}

void ShellProcessTests::testProcessListFromString()
{
    YAML::Node doc = YAML::Load( R"(---
script: "ls /tmp"
)" );
    CommandList cl(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 1 );
    QCOMPARE( cl.at(0).timeout(), 10 );
    QCOMPARE( cl.at(0).command(), QStringLiteral( "ls /tmp" ) );

    // Not a string
    doc = YAML::Load( R"(---
script: false
)" );
    CommandList cl1(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( cl1.isEmpty() );
    QCOMPARE( cl1.count(), 0 );

}

void ShellProcessTests::testProcessFromObject()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    command: "ls /tmp"
    timeout: 20
)" );
    CommandList cl(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 1 );
    QCOMPARE( cl.at(0).timeout(), 20 );
    QCOMPARE( cl.at(0).command(), QStringLiteral( "ls /tmp" ) );
}

void ShellProcessTests::testProcessListFromObject()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    - command: "ls /tmp"
      timeout: 12
    - "-/bin/false"
)" );
    CommandList cl(
        CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 2 );
    QCOMPARE( cl.at(0).timeout(), 12 );
    QCOMPARE( cl.at(0).command(), QStringLiteral( "ls /tmp" ) );
    QCOMPARE( cl.at(1).timeout(), -1 );  // not set
}
