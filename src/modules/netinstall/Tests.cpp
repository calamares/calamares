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

    // This doesn't happen in normal constructions,
    // because a package can't have children.
    PackageTreeItem c( "zsh", &p );
    QCOMPARE( c.isSelected(), Qt::Unchecked );
    QCOMPARE( c.packageName(), QStringLiteral( "zsh" ) );
    QVERIFY( c.name().isEmpty() );  // not a group
    QCOMPARE( c.parentItem(), &p );
    QVERIFY( !c.isGroup() );
    QVERIFY( c.isPackage() );

    QCOMPARE( p.childCount(), 0 );  // not noticed it has a child
}

// *INDENT-OFF*
// clang-format off
static const char doc[] =
"- name: \"CCR\"\n"
"  description: \"Tools for the Chakra Community Repository\"\n"
"  packages:\n"
"    - ccr\n"
"    - base-devel\n";
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
}

QTEST_GUILESS_MAIN( ItemTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
