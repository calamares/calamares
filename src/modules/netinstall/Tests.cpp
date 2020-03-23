/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "PackageTreeItem.h"

#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

class ItemTests : public QObject
{
    Q_OBJECT
public:
    ItemTests();
    virtual ~ItemTests() {}

private Q_SLOTS:
    void initTestCase();

    void testRoot();
    void testPackage();
    void testGroup();
    void testCompare();
};

ItemTests::ItemTests() {}

void
ItemTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
ItemTests::testRoot()
{
    PackageTreeItem r;

    QCOMPARE( r.isSelected(), Qt::Checked );
    QCOMPARE( r.name(), QStringLiteral( "<root>" ) );
    QCOMPARE( r.parentItem(), nullptr );
    QVERIFY( r.isGroup() );

    QVERIFY( r == r );
}

void
ItemTests::testPackage()
{
    PackageTreeItem p( "bash", nullptr );

    QCOMPARE( p.isSelected(), Qt::Unchecked );
    QCOMPARE( p.packageName(), QStringLiteral( "bash" ) );
    QVERIFY( p.name().isEmpty() );  // not a group
    QCOMPARE( p.parentItem(), nullptr );
    QCOMPARE( p.childCount(), 0 );
    QVERIFY( !p.isHidden() );
    QVERIFY( !p.isCritical() );
    QVERIFY( !p.isGroup() );
    QVERIFY( p.isPackage() );
    QVERIFY( p == p );

    // This doesn't happen in normal constructions,
    // because a package can't have children.
    PackageTreeItem c( "zsh", &p );
    QCOMPARE( c.isSelected(), Qt::Unchecked );
    QCOMPARE( c.packageName(), QStringLiteral( "zsh" ) );
    QVERIFY( c.name().isEmpty() );  // not a group
    QCOMPARE( c.parentItem(), &p );
    QVERIFY( !c.isGroup() );
    QVERIFY( c.isPackage() );
    QVERIFY( c == c );
    QVERIFY( c != p );

    QCOMPARE( p.childCount(), 0 );  // not noticed it has a child
}

// *INDENT-OFF*
// clang-format off
static const char doc[] =
"- name: \"CCR\"\n"
"  description: \"Tools for the Chakra Community Repository\"\n"
"  packages:\n"
"    - ccr\n"
"    - base-devel\n"
"    - bash\n";

static const char doc_no_packages[] =
"- name: \"CCR\"\n"
"  description: \"Tools for the Chakra Community Repository\"\n"
"  packages: []\n";
// *INDENT-ON*
// clang-format on

void
ItemTests::testGroup()
{
    YAML::Node yamldoc = YAML::Load( doc );
    QVariantList yamlContents = CalamaresUtils::yamlSequenceToVariant( yamldoc );

    QCOMPARE( yamlContents.length(), 1 );

    PackageTreeItem p( yamlContents[ 0 ].toMap(), nullptr );
    QCOMPARE( p.name(), QStringLiteral( "CCR" ) );
    QVERIFY( p.packageName().isEmpty() );
    QVERIFY( p.description().startsWith( QStringLiteral( "Tools " ) ) );
    QCOMPARE( p.parentItem(), nullptr );
    QVERIFY( !p.isHidden() );
    QVERIFY( !p.isCritical() );
    // The item-constructor doesn't consider the packages: list
    QCOMPARE( p.childCount(), 0 );
    QVERIFY( p.isGroup() );
    QVERIFY( !p.isPackage() );
    QVERIFY( p == p );

    PackageTreeItem c( "zsh", nullptr );
    QVERIFY( p != c );
}

void
ItemTests::testCompare()
{
    PackageTreeItem p0( "bash", nullptr );
    PackageTreeItem p1( "bash", &p0 );
    PackageTreeItem p2( "bash", nullptr );

    QVERIFY( p0 == p1 );  // Parent doesn't matter
    QVERIFY( p0 == p2 );

    p2.setSelected( Qt::Checked );
    p1.setSelected( Qt::Unchecked );
    QVERIFY( p0 == p1 );  // Neither does selected state
    QVERIFY( p0 == p2 );

    PackageTreeItem r0( nullptr );
    QVERIFY( p0 != r0 );
    QVERIFY( p1 != r0 );
    QVERIFY( r0 == r0 );
    PackageTreeItem r1( nullptr );
    QVERIFY( r0 == r1 );  // Different roots are still equal

    PackageTreeItem r2( "<root>", nullptr );  // Fake root
    QVERIFY( r0 != r2 );
    QVERIFY( r1 != r2 );
    QVERIFY( p0 != r2 );
    PackageTreeItem r3( "<root>", nullptr );
    QVERIFY( r3 == r2 );

    YAML::Node yamldoc = YAML::Load( doc );  // See testGroup()
    QVariantList yamlContents = CalamaresUtils::yamlSequenceToVariant( yamldoc );
    QCOMPARE( yamlContents.length(), 1 );

    PackageTreeItem p3( yamlContents[ 0 ].toMap(), nullptr );
    QVERIFY( p3 == p3 );
    QVERIFY( p3 != p1 );
    QVERIFY( p1 != p3 );
    QCOMPARE( p3.childCount(), 0 );  // Doesn't load the packages: list

    PackageTreeItem p4( CalamaresUtils::yamlSequenceToVariant( YAML::Load( doc ) )[ 0 ].toMap(), nullptr );
    QVERIFY( p3 == p4 );
    PackageTreeItem p5( CalamaresUtils::yamlSequenceToVariant( YAML::Load( doc_no_packages ) )[ 0 ].toMap(), nullptr );
    QVERIFY( p3 == p5 );

#if 0
    // Check that the sub-packages loaded correctly
    bool found_one_bash = false;
    for ( int i = 0; i < p3.childCount(); ++i )
    {
        QVERIFY( p3.child( i )->isPackage() );
        if ( p0 == *p3.child( i ) )
        {
            found_one_bash = true;
        }
    }
    QVERIFY( found_one_bash );
#endif
}


QTEST_GUILESS_MAIN( ItemTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
