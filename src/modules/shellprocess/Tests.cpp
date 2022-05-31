/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
using std::operator""s;


ShellProcessTests::ShellProcessTests() {}

ShellProcessTests::~ShellProcessTests() {}

void
ShellProcessTests::initTestCase()
{
}

void
ShellProcessTests::testProcessListSampleConfig()
{
    YAML::Node doc;

    QString filename = QStringLiteral( "shellprocess.conf" );
    QFile fi( QString( "%1/%2" ).arg( BUILD_AS_TEST, filename ) );

    QVERIFY( fi.exists() );
    doc = YAML::LoadFile( fi.fileName().toStdString() );

    CommandList cl( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 3 );

    QCOMPARE( cl.at( 0 ).timeout(), CalamaresUtils::CommandLine::TimeoutNotSet() );
    QCOMPARE( cl.at( 2 ).timeout(), 3600s );  // slowloris
}

void
ShellProcessTests::testProcessListFromList()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    - "ls /tmp"
    - "ls /nonexistent"
    - "/bin/false"
)" );
    CommandList cl( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 3 );

    // Contains 1 bad element
    doc = YAML::Load( R"(---
script:
    - "ls /tmp"
    - false
    - "ls /nonexistent"
)" );
    CommandList cl1( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );
    QVERIFY( !cl1.isEmpty() );
    QCOMPARE( cl1.count(), 2 );  // One element ignored
}

void
ShellProcessTests::testProcessListFromString()
{
    YAML::Node doc = YAML::Load( R"(---
script: "ls /tmp"
)" );
    CommandList cl( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );

    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 1 );
    QCOMPARE( cl.at( 0 ).timeout(), 10s );
    QCOMPARE( cl.at( 0 ).command(), QStringLiteral( "ls /tmp" ) );

    // Not a string
    doc = YAML::Load( R"(---
script: false
)" );
    CommandList cl1( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );
    QVERIFY( cl1.isEmpty() );
    QCOMPARE( cl1.count(), 0 );
}

void
ShellProcessTests::testProcessFromObject()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    command: "ls /tmp"
    timeout: 20
)" );
    CommandList cl( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );

    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 1 );
    QCOMPARE( cl.at( 0 ).timeout(), 20s );
    QCOMPARE( cl.at( 0 ).command(), QStringLiteral( "ls /tmp" ) );
}

void
ShellProcessTests::testProcessListFromObject()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    - command: "ls /tmp"
      timeout: 12
    - "-/bin/false"
)" );
    CommandList cl( CalamaresUtils::yamlMapToVariant( doc ).value( "script" ) );
    QVERIFY( !cl.isEmpty() );
    QCOMPARE( cl.count(), 2 );
    QCOMPARE( cl.at( 0 ).timeout(), 12s );
    QCOMPARE( cl.at( 0 ).command(), QStringLiteral( "ls /tmp" ) );
    QCOMPARE( cl.at( 1 ).timeout(), CalamaresUtils::CommandLine::TimeoutNotSet() );  // not set
}

void
ShellProcessTests::testRootSubstitution()
{
    YAML::Node doc = YAML::Load( R"(---
script:
    - "ls /tmp"
)" );
    QVariant plainScript = CalamaresUtils::yamlMapToVariant( doc ).value( "script" );
    QVariant rootScript = CalamaresUtils::yamlMapToVariant( YAML::Load( R"(---
script:
    - "ls ${ROOT}"
)" ) )
                              .value( "script" );
    QVariant userScript = CalamaresUtils::yamlMapToVariant( YAML::Load( R"(---
script:
    - mktemp -d ${ROOT}/calatestXXXXXXXX
    - "chown ${USER} ${ROOT}/calatest*"
    - rm -rf ${ROOT}/calatest*
)" ) )
                              .value( "script" );

    if ( !Calamares::JobQueue::instance() )
        (void)new Calamares::JobQueue( nullptr );
    if ( !Calamares::Settings::instance() )
        (void)Calamares::Settings::init( QString() );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QVERIFY( gs != nullptr );

    qDebug() << "Expect WARNING, ERROR, WARNING";

    // Doesn't use ${ROOT}, so no failures
    QVERIFY( bool( CommandList( plainScript, false, 10s ).run() ) );

    // Doesn't use ${ROOT}, but does chroot, so fails
    QVERIFY( !bool( CommandList( plainScript, true, 10s ).run() ) );

    // Does use ${ROOT}, which is not set, so fails
    QVERIFY( !bool( CommandList( rootScript, false, 10s ).run() ) );
    // .. fails for two reasons
    QVERIFY( !bool( CommandList( rootScript, true, 10s ).run() ) );

    gs->insert( "rootMountPoint", "/tmp" );
    // Now that the root is set, two variants work .. still can't
    // chroot, unless the rootMountPoint contains a full system,
    // *and* we're allowed to chroot (ie. running tests as root).
    qDebug() << "Expect no output.";
    QVERIFY( bool( CommandList( plainScript, false, 10s ).run() ) );
    QVERIFY( bool( CommandList( rootScript, false, 10s ).run() ) );

    qDebug() << "Expect ERROR";
    // But no user set yet
    QVERIFY( !bool( CommandList( userScript, false, 10s ).run() ) );

    // Show that shell expansion is now quoted.
    gs->insert( "username", "`id -u`" );
    {
        CalamaresUtils::CommandLine c { QStringLiteral( "chown ${USER}" ), std::chrono::seconds( 0 ) };
        QCOMPARE( c.expand().command(), QStringLiteral( "chown '`id -u`'" ) );
    }
    // Now play dangerous games with shell expansion -- except the internal command is now
    // quoted, so this fails because it's **highly** unlikely that the literal string
    // "`id -u`" is a valid username.
    QVERIFY( !bool( CommandList( userScript, false, 10s ).run() ) );
}
