/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"
#include "PackageModel.h"
#include "PackageTreeItem.h"

#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

#include <KMacroExpander>

#include <QtTest/QtTest>

class ItemTests : public QObject
{
    Q_OBJECT
public:
    ItemTests();
    ~ItemTests() override {}

private:
    void checkAllSelected( PackageTreeItem* p );
    void recursiveCompare( PackageTreeItem*, PackageTreeItem* );
    void recursiveCompare( PackageModel&, PackageModel& );

private Q_SLOTS:
    void initTestCase();

    void testRoot();

    void testPackage();
    void testExtendedPackage();

    void testGroup();
    void testCompare();
    void testModel();
    void testExampleFiles();

    void testUrlFallback_data();
    void testUrlFallback();
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
    QVERIFY( p.description().isEmpty() );
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

static const char doc_with_expanded[] =
"- name: \"CCR\"\n"
"  description: \"Tools for the Chakra Community Repository\"\n"
"  expanded: true\n"
"  packages:\n"
"    - ccr\n"
"    - base-devel\n"
"    - bash\n";
// *INDENT-ON*
// clang-format on

void
ItemTests::testExtendedPackage()
{
    YAML::Node yamldoc = YAML::Load( doc );
    QVariantList yamlContents = CalamaresUtils::yamlSequenceToVariant( yamldoc );

    QCOMPARE( yamlContents.length(), 1 );

    // Kind of derpy, but we can treat a group as if it is a package
    // because the keys name and description are the same
    PackageTreeItem p( yamlContents[ 0 ].toMap(), PackageTreeItem::PackageTag { nullptr } );

    QCOMPARE( p.isSelected(), Qt::Unchecked );
    QCOMPARE( p.packageName(), QStringLiteral( "CCR" ) );
    QVERIFY( p.name().isEmpty() );  // not a group
    QVERIFY( !p.description().isEmpty() );  // because it is set
    QVERIFY( p.description().startsWith( QStringLiteral( "Tools for the Chakra" ) ) );
    QCOMPARE( p.parentItem(), nullptr );
    QCOMPARE( p.childCount(), 0 );
    QVERIFY( !p.isHidden() );
    QVERIFY( !p.isCritical() );
    QVERIFY( !p.isGroup() );
    QVERIFY( p.isPackage() );
    QVERIFY( p == p );
}


void
ItemTests::testGroup()
{
    YAML::Node yamldoc = YAML::Load( doc );
    QVariantList yamlContents = CalamaresUtils::yamlSequenceToVariant( yamldoc );

    QCOMPARE( yamlContents.length(), 1 );

    PackageTreeItem p( yamlContents[ 0 ].toMap(), PackageTreeItem::GroupTag { nullptr } );
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

    PackageTreeItem c( "zsh", nullptr );  // Single string, package
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

    PackageTreeItem p3( yamlContents[ 0 ].toMap(), PackageTreeItem::GroupTag { nullptr } );
    QVERIFY( p3 == p3 );
    QVERIFY( p3 != p1 );
    QVERIFY( p1 != p3 );
    QCOMPARE( p3.childCount(), 0 );  // Doesn't load the packages: list

    PackageTreeItem p4( CalamaresUtils::yamlSequenceToVariant( YAML::Load( doc ) )[ 0 ].toMap(),
                        PackageTreeItem::GroupTag { nullptr } );
    QVERIFY( p3 == p4 );
    PackageTreeItem p5( CalamaresUtils::yamlSequenceToVariant( YAML::Load( doc_no_packages ) )[ 0 ].toMap(),
                        PackageTreeItem::GroupTag { nullptr } );
    QVERIFY( p3 == p5 );
}

void
ItemTests::checkAllSelected( PackageTreeItem* p )
{
    QVERIFY( p->isSelected() );
    for ( int i = 0; i < p->childCount(); ++i )
    {
        checkAllSelected( p->child( i ) );
    }
}

void
ItemTests::recursiveCompare( PackageTreeItem* l, PackageTreeItem* r )
{
    QVERIFY( l && r );
    QVERIFY( *l == *r );
    QCOMPARE( l->childCount(), r->childCount() );

    for ( int i = 0; i < l->childCount(); ++i )
    {
        QCOMPARE( l->childCount(), r->childCount() );
        recursiveCompare( l->child( i ), r->child( i ) );
    }
}

void
ItemTests::recursiveCompare( PackageModel& l, PackageModel& r )
{
    return recursiveCompare( l.m_rootItem, r.m_rootItem );
}


void
ItemTests::testModel()
{
    YAML::Node yamldoc = YAML::Load( doc );  // See testGroup()
    QVariantList yamlContents = CalamaresUtils::yamlSequenceToVariant( yamldoc );
    QCOMPARE( yamlContents.length(), 1 );

    PackageModel m0( nullptr );
    m0.setupModelData( yamlContents );

    QCOMPARE( m0.m_hiddenItems.count(), 0 );  // Nothing hidden
    QCOMPARE( m0.rowCount(), 1 );  // Group, the packages are invisible
    QCOMPARE( m0.rowCount( m0.index( 0, 0 ) ), 3 );  // The packages

    checkAllSelected( m0.m_rootItem );

    PackageModel m2( nullptr );
    m2.setupModelData( CalamaresUtils::yamlSequenceToVariant( YAML::Load( doc_with_expanded ) ) );
    QCOMPARE( m2.m_hiddenItems.count(), 0 );
    QCOMPARE( m2.rowCount(), 1 );  // Group, now the packages expanded but not counted
    QCOMPARE( m2.rowCount( m2.index( 0, 0 ) ), 3 );  // The packages
    checkAllSelected( m2.m_rootItem );

    PackageTreeItem r;
    QVERIFY( r == *m0.m_rootItem );

    QCOMPARE( m0.m_rootItem->childCount(), 1 );

    PackageTreeItem* group = m0.m_rootItem->child( 0 );
    QVERIFY( group->isGroup() );
    QCOMPARE( group->name(), QStringLiteral( "CCR" ) );
    QCOMPARE( group->childCount(), 3 );

    PackageTreeItem bash( "bash", nullptr );
    // Check that the sub-packages loaded correctly
    bool found_one_bash = false;
    for ( int i = 0; i < group->childCount(); ++i )
    {
        QVERIFY( group->child( i )->isPackage() );
        if ( bash == *( group->child( i ) ) )
        {
            found_one_bash = true;
        }
    }
    QVERIFY( found_one_bash );

    // But m2 has "expanded" set which the others do no
    QVERIFY( *( m2.m_rootItem->child( 0 ) ) != *group );
}

void
ItemTests::testExampleFiles()
{
    QVERIFY( QStringLiteral( BUILD_AS_TEST ).endsWith( "/netinstall" ) );

    QDir d( BUILD_AS_TEST );

    for ( const QString& filename : QStringList { "netinstall.yaml" } )
    {
        QFile f( d.filePath( filename ) );
        QVERIFY( f.exists() );
        QVERIFY( f.open( QIODevice::ReadOnly ) );
        QByteArray contents = f.readAll();
        QVERIFY( !contents.isEmpty() );

        YAML::Node yamldoc = YAML::Load( contents.constData() );
        QVariantList yamlContents = CalamaresUtils::yamlSequenceToVariant( yamldoc );

        PackageModel m1( nullptr );
        m1.setupModelData( yamlContents );

        // TODO: should test *something* about this file :/
    }
}

void
ItemTests::testUrlFallback_data()
{
    QTest::addColumn< QString >( "filename" );
    QTest::addColumn< int >( "status" );
    QTest::addColumn< int >( "count" );

    using S = Config::Status;

    QTest::newRow( "bad" ) << "1a-single-bad.conf" << smash( S::FailedBadConfiguration ) << 0;
    QTest::newRow( "empty" ) << "1a-single-empty.conf" << smash( S::FailedNoData ) << 0;
    QTest::newRow( "error" ) << "1a-single-error.conf" << smash( S::FailedBadData ) << 0;
    QTest::newRow( "two" ) << "1b-single-small.conf" << smash( S::Ok ) << 2;
    QTest::newRow( "five" ) << "1b-single-large.conf" << smash( S::Ok ) << 5;
    QTest::newRow( "none" ) << "1c-none.conf" << smash( S::FailedNoData ) << 0;
    QTest::newRow( "unset" ) << "1c-unset.conf" << smash( S::FailedNoData ) << 0;
    // Finds small, then stops
    QTest::newRow( "fallback-small" ) << "1d-fallback-small.conf" << smash( S::Ok ) << 2;
    // Finds large, then stops
    QTest::newRow( "fallback-large" ) << "1d-fallback-large.conf" << smash( S::Ok ) << 5;
    // Finds empty, finds small
    QTest::newRow( "fallback-mixed" ) << "1d-fallback-mixed.conf" << smash( S::Ok ) << 2;
    // Finds empty, then bad
    QTest::newRow( "fallback-bad" ) << "1d-fallback-bad.conf" << smash( S::FailedBadConfiguration ) << 0;
}

void
ItemTests::testUrlFallback()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    QFETCH( QString, filename );
    QFETCH( int, status );
    QFETCH( int, count );

    cDebug() << "Loading" << filename;

    // BUILD_AS_TEST is the source-directory path
    QString testdir = QString( "%1/tests" ).arg( BUILD_AS_TEST );
    QFile fi( QString( "%1/%2" ).arg( testdir, filename ) );
    QVERIFY( fi.exists() );

    Config c;

    QFile yamlFile( fi.fileName() );
    if ( yamlFile.exists() && yamlFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        QString ba( yamlFile.readAll() );
        QVERIFY( ba.length() > 0 );
        QHash< QString, QString > replace;
        replace.insert( "TESTDIR", testdir );
        QString correctedDocument = KMacroExpander::expandMacros( ba, replace, '$' );

        try
        {
            YAML::Node yamldoc = YAML::Load( correctedDocument.toUtf8() );
            auto map = CalamaresUtils::yamlToVariant( yamldoc ).toMap();
            QVERIFY( map.count() > 0 );
            c.setConfigurationMap( map );
        }
        catch ( YAML::Exception& )
        {
            bool badYaml = true;
            QVERIFY( !badYaml );
        }
    }
    else
    {
        QCOMPARE( QStringLiteral( "not found" ), fi.fileName() );
    }

    // Each of the configs sets required to **true**, which is not the default
    QVERIFY( c.required() );

    // Now give the loader time to complete
    QEventLoop loop;
    connect( &c, &Config::statusReady, &loop, &QEventLoop::quit );
    QSignalSpy spy( &c, &Config::statusReady );
    QTimer::singleShot( std::chrono::seconds( 1 ), &loop, &QEventLoop::quit );
    loop.exec();

    // Check it didn't time out
    QCOMPARE( spy.count(), 1 );
    // Check YAML-loading results
    QCOMPARE( smash( c.statusCode() ), status );
    QCOMPARE( c.model()->rowCount(), count );
}


QTEST_GUILESS_MAIN( ItemTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
