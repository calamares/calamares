/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "modulesystem/Descriptor.h"
#include "modulesystem/InstanceKey.h"

#include <QtTest/QtTest>

using Calamares::ModuleSystem::InstanceKey;

class ModuleSystemTests : public QObject
{
    Q_OBJECT
public:
    ModuleSystemTests() {}
    ~ModuleSystemTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testEmptyInstanceKey();
    void testCustomInstanceKey();
    void testFromStringInstanceKey();

    void testBadSimpleCases();
    void testBadFromStringCases();

    void testBasicDescriptor();
};

void
ModuleSystemTests::initTestCase()
{
}

void
assert_is_invalid( const InstanceKey& k )
{
    QVERIFY( !k.isValid() );
    QVERIFY( !k.isCustom() );
    QVERIFY( k.module().isEmpty() );
    QVERIFY( k.id().isEmpty() );
    if ( k.toString().isEmpty() )
    {
        QVERIFY( k.toString().isEmpty() );
    }
    else
    {
        QCOMPARE( k.toString(), QString() );
    }
}

void
ModuleSystemTests::testEmptyInstanceKey()
{
    InstanceKey k0;
    assert_is_invalid( k0 );
}

void
ModuleSystemTests::testCustomInstanceKey()
{
    InstanceKey k0( "derp", "derp" );
    QVERIFY( k0.isValid() );
    QVERIFY( !k0.isCustom() );
    QCOMPARE( k0.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k0.id(), QStringLiteral( "derp" ) );
    QCOMPARE( k0.toString(), QStringLiteral( "derp@derp" ) );

    InstanceKey k1( "derp", "horse" );
    QVERIFY( k1.isValid() );
    QVERIFY( k1.isCustom() );
    QCOMPARE( k1.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k1.id(), QStringLiteral( "horse" ) );
    QCOMPARE( k1.toString(), QStringLiteral( "derp@horse" ) );

    InstanceKey k4( "derp", QString() );
    QVERIFY( k4.isValid() );
    QVERIFY( !k4.isCustom() );
    QCOMPARE( k4.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k4.id(), QStringLiteral( "derp" ) );
    QCOMPARE( k4.toString(), QStringLiteral( "derp@derp" ) );
}

void
ModuleSystemTests::testFromStringInstanceKey()
{
    InstanceKey k0 = InstanceKey::fromString( "derp@derp" );
    QVERIFY( k0.isValid() );
    QVERIFY( !k0.isCustom() );
    QCOMPARE( k0.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k0.id(), QStringLiteral( "derp" ) );

    InstanceKey k1 = InstanceKey::fromString( "derp@horse" );
    QVERIFY( k1.isValid() );
    QVERIFY( k1.isCustom() );
    QCOMPARE( k1.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k1.id(), QStringLiteral( "horse" ) );

    InstanceKey k2 = InstanceKey::fromString( "derp" );
    QVERIFY( k2.isValid() );
    QVERIFY( !k2.isCustom() );
    QCOMPARE( k2.module(), QStringLiteral( "derp" ) );
    QCOMPARE( k2.id(), QStringLiteral( "derp" ) );
}

/// @brief These are expected to fail since they show bugs in the code
void
ModuleSystemTests::testBadSimpleCases()
{
    InstanceKey k4( "derp", "derp@derp" );
    assert_is_invalid( k4 );
}

void
ModuleSystemTests::testBadFromStringCases()
{
    InstanceKey k0 = InstanceKey::fromString( QString() );
    assert_is_invalid( k0 );

    k0 = InstanceKey::fromString( "derp@derp@derp" );
    assert_is_invalid( k0 );
}

void
ModuleSystemTests::testBasicDescriptor()
{
    const QString path = QStringLiteral( "/bogus.desc" );
    {
        QVariantMap m;
        auto d = Calamares::ModuleSystem::Descriptor::fromDescriptorData( m, path );

        QVERIFY( !d.isValid() );
        QVERIFY( d.name().isEmpty() );
    }
    {
        QVariantMap m;
        m.insert( "name", QVariant() );
        auto d = Calamares::ModuleSystem::Descriptor::fromDescriptorData( m, path );

        QVERIFY( !d.isValid() );
        QVERIFY( d.name().isEmpty() );
    }
    {
        QVariantMap m;
        m.insert( "name", 17 );
        auto d = Calamares::ModuleSystem::Descriptor::fromDescriptorData( m, path );

        QVERIFY( !d.isValid() );
        QVERIFY( !d.name().isEmpty() );
        QCOMPARE( d.name(), QStringLiteral( "17" ) );  // Strange but true
    }
    {
        QVariantMap m;
        m.insert( "name", "welcome" );
        m.insert( "type", "viewmodule" );
        m.insert( "interface", "qtplugin" );
        auto d = Calamares::ModuleSystem::Descriptor::fromDescriptorData( m, path );

        // QVERIFY( !d.isValid() );
        QCOMPARE( d.name(), QStringLiteral( "welcome" ) );
        QCOMPARE( d.type(), Calamares::ModuleSystem::Type::View );
        QCOMPARE( d.interface(), Calamares::ModuleSystem::Interface::QtPlugin );
    }
}


QTEST_GUILESS_MAIN( ModuleSystemTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
