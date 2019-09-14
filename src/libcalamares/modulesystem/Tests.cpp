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

#include "modulesystem/InstanceKey.h"

#include <QtTest/QtTest>

using Calamares::ModuleSystem::InstanceKey;

class ModuleSystemTests : public QObject
{
    Q_OBJECT
public:
    ModuleSystemTests() {}
    virtual ~ModuleSystemTests() {}

private Q_SLOTS:
    void initTestCase();

    void testEmptyInstanceKey();
    void testSimpleInstanceKey();
    void testCustomInstanceKey();
    void testFromStringInstanceKey();

    void testBadSimpleCases();
    void testBadFromStringCases();
};

void ModuleSystemTests::initTestCase()
{
}

void assert_is_invalid( const InstanceKey& k )
{
    QVERIFY( !k.isValid() );
    QVERIFY( !k.isCustom() );
    QVERIFY( k.module().isEmpty() );
    QVERIFY( k.id().isEmpty() );
    QVERIFY( QString( k ).isEmpty() );
}

void ModuleSystemTests::testEmptyInstanceKey()
{
    InstanceKey k0;
    assert_is_invalid( k0 );
}

void ModuleSystemTests::testSimpleInstanceKey()
{
    InstanceKey k1( "derp" );
    QVERIFY( k1.isValid() );
    QVERIFY( !k1.isCustom() );
    QCOMPARE( k1.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k1.id(), QStringLiteral( "derp" ) );
    QCOMPARE( QString( k1 ), QStringLiteral( "derp@derp" ) );
}

void ModuleSystemTests::testCustomInstanceKey()
{
    InstanceKey k0("derp", "derp");
    QVERIFY( k0.isValid() );
    QVERIFY( !k0.isCustom() );
    QCOMPARE( k0.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k0.id(), QStringLiteral( "derp" ) );
    QCOMPARE( QString( k0 ), QStringLiteral( "derp@derp" ) );

    InstanceKey k1("derp", "horse");
    QVERIFY( k1.isValid() );
    QVERIFY( k1.isCustom() );
    QCOMPARE( k1.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k1.id(), QStringLiteral( "horse" ) );
    QCOMPARE( QString( k1 ), QStringLiteral( "derp@horse" ) );

    InstanceKey k4( "derp", QString() );
    QVERIFY( k4.isValid() );
    QVERIFY( !k4.isCustom() );
    QCOMPARE( k4.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k4.id(), QStringLiteral( "derp" ) );
    QCOMPARE( QString( k4 ), QStringLiteral( "derp@derp" ) );
}

void ModuleSystemTests::testFromStringInstanceKey()
{
    InstanceKey k0 = InstanceKey::fromString( "derp@derp" );
    QVERIFY( k0.isValid() );
    QVERIFY( !k0.isCustom() );
    QCOMPARE( k0.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k0.id(), QStringLiteral( "derp" ) );
    QCOMPARE( QString( k0 ), QStringLiteral( "derp@derp" ) );

    InstanceKey k1 = InstanceKey::fromString( "derp@horse" );
    QVERIFY( k1.isValid() );
    QVERIFY( k1.isCustom() );
    QCOMPARE( k1.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k1.id(), QStringLiteral( "horse" ) );
    QCOMPARE( QString( k1 ), QStringLiteral( "derp@horse" ) );

    InstanceKey k2 = InstanceKey::fromString( "derp" );
    QVERIFY( k2.isValid() );
    QVERIFY( !k2.isCustom() );
    QCOMPARE( k2.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k2.id(), QStringLiteral( "derp" ) );
    QCOMPARE( QString( k2 ), QStringLiteral( "derp@derp" ) );
}

/// @brief These are expected to fail since they show bugs in the code
void ModuleSystemTests::testBadSimpleCases()
{
    InstanceKey k2( "derp@derp" );
    assert_is_invalid( k2 );

    InstanceKey k3( "derp@horse" );
    assert_is_invalid( k3 );

    InstanceKey k4( "derp", "derp@derp" );
    assert_is_invalid( k4 );
}

void ModuleSystemTests::testBadFromStringCases()
{
    InstanceKey k0 = InstanceKey::fromString( QString() );
    assert_is_invalid( k0 );

    k0 = InstanceKey::fromString( "derp@derp@derp" );
    assert_is_invalid( k0 );
}


QTEST_GUILESS_MAIN( ModuleSystemTests )

#include "Tests.moc"
