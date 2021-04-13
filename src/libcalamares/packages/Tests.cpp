/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Globals.h"

#include "GlobalStorage.h"
#include "utils/Logger.h"

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
    void testAdd();
};

void
PackagesTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
PackagesTests::testEmpty()
{
    Calamares::GlobalStorage gs;
    const QString topKey( "packageOperations" );
    Calamares::ModuleSystem::InstanceKey k( "this", "that" );

    QVERIFY( !gs.contains( topKey ) );
    QCOMPARE( k.toString(), "this@that" );

    // Adding nothing at all does nothing
    QVERIFY( !CalamaresUtils::Packages::setGSPackageAdditions( &gs, k, QVariantList(), QVariantList() ) );
    QVERIFY( !gs.contains( topKey ) );
}

void
PackagesTests::testAdd()
{
    Calamares::GlobalStorage gs;
    const QString topKey( "packageOperations" );
    Calamares::ModuleSystem::InstanceKey k( "this", "that" );

    QVERIFY( !gs.contains( topKey ) );
    QVERIFY(
        CalamaresUtils::Packages::setGSPackageAdditions( &gs, k, QVariantList { QString( "vim" ) }, QVariantList() ) );
    QVERIFY( gs.contains( topKey ) );
    auto actionList = gs.value( topKey ).toList();
    QCOMPARE( actionList.length(), 1 );
    auto action = actionList[ 0 ].toMap();
    QVERIFY( action.contains( "install" ) );
    auto op = action[ "install" ].toList();
    QCOMPARE( op.length(), 1 );
    cDebug() << op;

    QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions(
        &gs, k, QVariantList { QString( "vim" ), QString( "emacs" ) }, QVariantList() ) );
    QVERIFY( gs.contains( topKey ) );
    actionList = gs.value( topKey ).toList();
    QCOMPARE( actionList.length(), 1 );
    action = actionList[ 0 ].toMap();
    QVERIFY( action.contains( "install" ) );
    op = action[ "install" ].toList();
    QCOMPARE( op.length(), 2 );
    QCOMPARE( action[ "source" ].toString(), k.toString() );
    cDebug() << op;
}


QTEST_GUILESS_MAIN( PackagesTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
