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

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

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

void ShellProcessTests::testRootSubstitution()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    - "ls /tmp"
)" );
    QVariant plainScript = CalamaresUtils::yamlMapToVariant( doc ).toMap().value( "script" );
    QVariant rootScript = CalamaresUtils::yamlMapToVariant(
        YAML::Load( R"(---
script:
    - "ls @@ROOT@@"
)" ) ).toMap().value( "script" );
    QVariant userScript = CalamaresUtils::yamlMapToVariant(
        YAML::Load( R"(---
script:
    - mktemp -d @@ROOT@@/calatestXXXXXXXX
    - "chown @@USER@@ @@ROOT@@/calatest*"
    - rm -rf @@ROOT@@/calatest*
)" ) ).toMap().value( "script" );

    if ( !Calamares::JobQueue::instance() )
        (void)new Calamares::JobQueue( nullptr );
    if ( !Calamares::Settings::instance() )
        (void)new Calamares::Settings( QString(), true );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QVERIFY( gs != nullptr );

    qDebug() << "Expect WARNING, ERROR, WARNING";
    // Doesn't use @@ROOT@@, so no failures
    QVERIFY( bool(CommandList(plainScript, false, 10 ).run()) );

    // Doesn't use @@ROOT@@, but does chroot, so fails
    QVERIFY( !bool(CommandList(plainScript, true, 10 ).run()) );

    // Does use @@ROOT@@, which is not set, so fails
    QVERIFY( !bool(CommandList(rootScript, false, 10 ).run()) );
    // .. fails for two reasons
    QVERIFY( !bool(CommandList(rootScript, true, 10 ).run()) );

    gs->insert( "rootMountPoint", "/tmp" );
    // Now that the root is set, two variants work .. still can't
    // chroot, unless the rootMountPoint contains a full system,
    // *and* we're allowed to chroot (ie. running tests as root).
    qDebug() << "Expect no output.";
    QVERIFY( bool(CommandList(plainScript, false, 10 ).run()) );
    QVERIFY( bool(CommandList(rootScript, false, 10 ).run()) );

    qDebug() << "Expect ERROR";
    // But no user set yet
    QVERIFY( !bool(CommandList(userScript, false, 10 ).run()) );

    // Now play dangerous games with shell expansion
    gs->insert( "username", "`id -u`" );
    QVERIFY( bool(CommandList(userScript, false, 10 ).run()) );
}
