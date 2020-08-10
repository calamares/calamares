/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2018-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
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
 *
 */

#include "GlobalStorage.h"

#include "utils/Logger.h"

#include <QObject>
#include <QSignalSpy>
#include <QtTest/QtTest>

class TestLibCalamares : public QObject
{
    Q_OBJECT
public:
    TestLibCalamares() {}
    virtual ~TestLibCalamares() {}

private Q_SLOTS:
    void testGSModify();
    void testGSLoadSave();
    void testGSLoadSave2();
    void testGSLoadSaveYAMLStringList();
};

void
TestLibCalamares::testGSModify()
{
    Calamares::GlobalStorage gs;
    QSignalSpy spy( &gs, &Calamares::GlobalStorage::changed );

    const QString key( "derp" );

    QCOMPARE( gs.count(), 0 );
    QVERIFY( !gs.contains( key ) );

    const int value = 17;
    gs.insert( key, value );
    QCOMPARE( gs.count(), 1 );
    QVERIFY( gs.contains( key ) );
    QCOMPARE( gs.value( key ).type(), QVariant::Int );
    QCOMPARE( gs.value( key ).toString(), QString( "17" ) );  // It isn't a string, but does convert
    QCOMPARE( gs.value( key ).toInt(), value );

    gs.remove( key );
    QCOMPARE( gs.count(), 0 );
    QVERIFY( !gs.contains( key ) );

    QCOMPARE( spy.count(), 2 );  // one insert, one remove
}

void
TestLibCalamares::testGSLoadSave()
{
    Calamares::GlobalStorage gs;
    const QString jsonfilename( "gs.test.json" );
    const QString yamlfilename( "gs.test.yaml" );

    gs.insert( "derp", 17 );
    gs.insert( "cow", "moo" );

    QVariantList l;
    for ( const auto& s : QStringList { "dopey", "sneezy" } )
    {
        l.append( s );
    }
    gs.insert( "dwarfs", l );

    QCOMPARE( gs.count(), 3 );

    QVERIFY( gs.saveJson( jsonfilename ) );
    Calamares::GlobalStorage gs2;
    QCOMPARE( gs2.count(), 0 );
    QVERIFY( gs2.loadJson( jsonfilename ) );
    QCOMPARE( gs2.count(), 3 );
    QCOMPARE( gs2.data(), gs.data() );

    QVERIFY( gs.saveYaml( yamlfilename ) );
    Calamares::GlobalStorage gs3;
    QCOMPARE( gs3.count(), 0 );
    QVERIFY( gs3.loadYaml( jsonfilename ) );
    QCOMPARE( gs3.count(), 3 );
    QCOMPARE( gs3.data(), gs.data() );

    // YAML can load as JSON!
    QVERIFY( gs3.loadYaml( jsonfilename ) );
    QCOMPARE( gs3.count(), 3 );
    QCOMPARE( gs3.data(), gs.data() );

    // Failures in loading
    QVERIFY( !gs3.loadJson( yamlfilename ) );

    Calamares::GlobalStorage gs4;
    gs4.insert( "derp", 32 );
    gs4.insert( "dorp", "Varsseveld" );
    QCOMPARE( gs4.count(), 2 );
    QVERIFY( gs4.contains( "dorp" ) );
    QCOMPARE( gs4.value( "derp" ).toInt(), 32 );
    QVERIFY( gs4.loadJson( jsonfilename ) );
    // 3 keys from the file, but one overwrite
    QCOMPARE( gs4.count(), 4 );
    QVERIFY( gs4.contains( "dorp" ) );
    QCOMPARE( gs4.value( "derp" ).toInt(), 17 );  // This one was overwritten
}

void
TestLibCalamares::testGSLoadSave2()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    const QString filename( "../src/libcalamares/testdata/yaml-list.conf" );
    if ( !QFile::exists( filename ) )
    {
        return;
    }

    Calamares::GlobalStorage gs1;
    const QString key( "dwarfs" );

    QVERIFY( gs1.loadYaml( filename ) );
    QCOMPARE( gs1.count(), 3 );  // From examining the file
    QVERIFY( gs1.contains( key ) );
    cDebug() << gs1.value( key ).type() << gs1.value( key );
    QCOMPARE( gs1.value( key ).type(), QVariant::List );

    const QString yamlfilename( "gs.test.yaml" );
    QVERIFY( gs1.saveYaml( yamlfilename ) );

    Calamares::GlobalStorage gs2;
    QVERIFY( gs2.loadYaml( yamlfilename ) );
    QVERIFY( gs2.contains( key ) );
    QCOMPARE( gs2.value( key ).type(), QVariant::List );
}

void
TestLibCalamares::testGSLoadSaveYAMLStringList()
{
    Calamares::GlobalStorage gs;
    const QString yamlfilename( "gs.test.yaml" );

    gs.insert( "derp", 17 );
    gs.insert( "cow", "moo" );
    gs.insert( "dwarfs", QStringList { "happy", "dopey", "sleepy", "sneezy", "doc", "thorin", "balin" } );

    QCOMPARE( gs.count(), 3 );
    QCOMPARE( gs.value( "dwarfs" ).toList().count(), 7 );  // There's seven dwarfs, right?
    QVERIFY( gs.value( "dwarfs" ).toStringList().contains( "thorin" ) );
    QVERIFY( !gs.value( "dwarfs" ).toStringList().contains( "gimli" ) );


    QVERIFY( gs.saveYaml( yamlfilename ) );

    Calamares::GlobalStorage gs2;
    QCOMPARE( gs2.count(), 0 );
    QVERIFY( gs2.loadYaml( yamlfilename ) );
    QCOMPARE( gs2.count(), 3 );
    QEXPECT_FAIL( "", "QStringList doesn't write out nicely", Continue );
    QCOMPARE( gs2.value( "dwarfs" ).toList().count(), 7 );  // There's seven dwarfs, right?
    QCOMPARE( gs2.value( "dwarfs" ).toString(), QStringLiteral( "<QStringList>" ) );  // .. they're gone
}


QTEST_GUILESS_MAIN( TestLibCalamares )

#include "utils/moc-warnings.h"

#include "Tests.moc"
