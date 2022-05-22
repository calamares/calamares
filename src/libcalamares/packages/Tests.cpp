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
    void testAdd_data();
    /** @brief Test various add calls, for a "clean" GS
     *
     * Check that adding through the variant- and the stringlist-API
     * does the same thing.
     */
    void testAdd();
    /// Test replacement and mixing string-list with variant calls
    void testAddMixed();
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

    QVERIFY( !CalamaresUtils::Packages::setGSPackageAdditions( &gs, k, QStringList() ) );
    QVERIFY( !gs.contains( topKey ) );
}

void
PackagesTests::testAdd_data()
{
    QTest::addColumn< QStringList >( "packages" );

    QTest::newRow( "one" ) << QStringList { QString( "vim" ) };
    QTest::newRow( "two" ) << QStringList { QString( "vim" ), QString( "emacs" ) };
    QTest::newRow( "one-again" ) << QStringList { QString( "nano" ) };
    QTest::newRow( "six" ) << QStringList { QString( "vim" ),  QString( "emacs" ), QString( "nano" ),
                                            QString( "kate" ), QString( "gedit" ), QString( "sublime" ) };
    // There is no "de-duplication" so this will insert "cim" twice
    QTest::newRow( "dups" ) << QStringList { QString( "cim" ), QString( "vim" ), QString( "cim" ) };
}

void
PackagesTests::testAdd()
{
    Calamares::GlobalStorage gs;

    const QString extraEditor( "notepad++" );
    const QString topKey( "packageOperations" );
    Calamares::ModuleSystem::InstanceKey k( "this", "that" );
    Calamares::ModuleSystem::InstanceKey otherInstance( "this", "other" );

    QFETCH( QStringList, packages );
    QVERIFY( !packages.contains( extraEditor ) );

    {
        QVERIFY( !gs.contains( topKey ) );
        QVERIFY(
            CalamaresUtils::Packages::setGSPackageAdditions( &gs, k, QVariant( packages ).toList(), QVariantList() ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 1 );
        auto action = actionList[ 0 ].toMap();
        QVERIFY( action.contains( "install" ) );
        auto op = action[ "install" ].toList();
        QCOMPARE( op.length(), packages.length() );
        for ( const auto& s : qAsConst( packages ) )
        {
            QVERIFY( op.contains( s ) );
        }
        cDebug() << op;
    }
    {
        QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions( &gs, otherInstance, packages ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 2 );  // One for each instance key!
        auto action = actionList[ 0 ].toMap();
        auto secondaction = actionList[ 1 ].toMap();
        auto op = action[ "install" ].toList();
        auto secondop = secondaction[ "install" ].toList();
        QCOMPARE( op, secondop );
    }

    {
        // Replace one and expect differences
        packages << extraEditor;
        QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions( &gs, otherInstance, packages ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 2 );  // One for each instance key!
        for ( const auto& actionVariant : qAsConst( actionList ) )
        {
            auto action = actionVariant.toMap();
            QVERIFY( action.contains( "install" ) );
            QVERIFY( action.contains( "source" ) );
            if ( action[ "source" ].toString() == otherInstance.toString() )
            {
                auto op = action[ "install" ].toList();
                QCOMPARE( op.length(), packages.length() );  // changed from original length, though
                for ( const auto& s : qAsConst( packages ) )
                {
                    QVERIFY( op.contains( s ) );
                }
            }
            else
            {
                // This is the "original" instance, so it's missing extraEditor
                auto op = action[ "install" ].toList();
                QCOMPARE( op.length(), packages.length() - 1 );  // changed from original length
                QVERIFY( !op.contains( extraEditor ) );
            }
        }
    }
}

void
PackagesTests::testAddMixed()
{
    Calamares::GlobalStorage gs;

    const QString extraEditor( "notepad++" );
    const QString topKey( "packageOperations" );
    Calamares::ModuleSystem::InstanceKey k( "this", "that" );
    Calamares::ModuleSystem::InstanceKey otherInstance( "this", "other" );

    // Just one
    {
        QVERIFY( !gs.contains( topKey ) );
        QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions(
            &gs, k, QVariantList { QString( "vim" ) }, QVariantList() ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 1 );
        auto action = actionList[ 0 ].toMap();
        QVERIFY( action.contains( "install" ) );
        auto op = action[ "install" ].toList();
        QCOMPARE( op.length(), 1 );
        QCOMPARE( op[ 0 ], QString( "vim" ) );
        cDebug() << op;
    }

    // Replace with two packages
    {
        QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions(
            &gs, k, QVariantList { QString( "vim" ), QString( "emacs" ) }, QVariantList() ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 1 );
        auto action = actionList[ 0 ].toMap();
        QVERIFY( action.contains( "install" ) );
        auto op = action[ "install" ].toList();
        QCOMPARE( op.length(), 2 );
        QCOMPARE( action[ "source" ].toString(), k.toString() );
        QVERIFY( op.contains( QString( "vim" ) ) );
        QVERIFY( op.contains( QString( "emacs" ) ) );
        cDebug() << op;
    }

    // Replace with one (different) package
    {
        QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions(
            &gs, k, QVariantList { QString( "nano" ) }, QVariantList() ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 1 );
        auto action = actionList[ 0 ].toMap();
        QVERIFY( action.contains( "install" ) );
        auto op = action[ "install" ].toList();
        QCOMPARE( op.length(), 1 );
        QCOMPARE( action[ "source" ].toString(), k.toString() );
        QCOMPARE( op[ 0 ], QString( "nano" ) );
        cDebug() << op;
    }

    // Now we have two sources
    {
        QVERIFY( CalamaresUtils::Packages::setGSPackageAdditions( &gs, otherInstance, QStringList( extraEditor ) ) );
        QVERIFY( gs.contains( topKey ) );
        auto actionList = gs.value( topKey ).toList();
        QCOMPARE( actionList.length(), 2 );

        for ( const auto& actionVariant : qAsConst( actionList ) )
        {
            auto action = actionVariant.toMap();
            QVERIFY( action.contains( "install" ) );
            QVERIFY( action.contains( "source" ) );
            if ( action[ "source" ].toString() == otherInstance.toString() )
            {
                auto op = action[ "install" ].toList();
                QCOMPARE( op.length(), 1 );
                QVERIFY(
                    op.contains( action[ "source" ] == otherInstance.toString() ? extraEditor : QString( "nano" ) ) );
            }
        }
    }
}


QTEST_GUILESS_MAIN( PackagesTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
