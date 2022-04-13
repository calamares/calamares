/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "CalamaresUtilsSystem.h"
#include "CommandList.h"
#include "Entropy.h"
#include "Logger.h"
#include "RAII.h"
#include "Runner.h"
#include "String.h"
#include "StringExpander.h"
#include "Traits.h"
#include "UMask.h"
#include "Variant.h"
#include "Yaml.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QTemporaryFile>

#include <QtTest/QtTest>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

class LibCalamaresTests : public QObject
{
    Q_OBJECT
public:
    LibCalamaresTests();
    ~LibCalamaresTests() override;

private Q_SLOTS:
    void initTestCase();
    void testDebugLevels();

    void testLoadSaveYaml();  // Just settings.conf
    void testLoadSaveYamlExtended();  // Do a find() in the src dir

    /** @section Test running commands and command-expansion. */
    void testCommands();
    void testCommandExpansion_data();
    void testCommandExpansion();  // See also shellprocess tests

    /** @section Test that all the UMask objects work correctly. */
    void testUmask();

    /** @section Tests the entropy functions. */
    void testEntropy();
    void testPrintableEntropy();
    void testOddSizedPrintable();

    /** @section Tests the RAII bits. */
    void testPointerSetter();

    /** @section Tests the Traits bits. */
    void testTraits();

    /** @section Testing the variants-methods */
    void testVariantStringListCode();
    void testVariantStringListYAMLDashed();
    void testVariantStringListYAMLBracketed();

    /** @section Test smart string truncation. */
    void testStringTruncation();
    void testStringTruncationShorter();
    void testStringTruncationDegenerate();
    void testStringRemoveLeading_data();
    void testStringRemoveLeading();
    void testStringRemoveTrailing_data();
    void testStringRemoveTrailing();

    /** @section Test String expansion. */
    void testStringMacroExpander_data();
    void testStringMacroExpander();  // The KF5::CoreAddons bits

    /** @section Test Runner directory-manipulation. */
    void testRunnerDirs();
    void testCalculateWorkingDirectory();
    void testRunnerOutput();

    /** @section Test file-functions */
    void testReadWriteFile();

private:
    void recursiveCompareMap( const QVariantMap& a, const QVariantMap& b, int depth );
};

LibCalamaresTests::LibCalamaresTests() {}

LibCalamaresTests::~LibCalamaresTests() {}

void
LibCalamaresTests::initTestCase()
{
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;

    if ( !gs )
    {
        cDebug() << "Creating new JobQueue";
        (void)new Calamares::JobQueue();
        gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    }
    QVERIFY( gs );
}

void
LibCalamaresTests::testDebugLevels()
{
    Logger::setupLogLevel( Logger::LOG_DISABLE );

    QCOMPARE( Logger::logLevel(), static_cast< unsigned int >( Logger::LOG_DISABLE ) );

    for ( unsigned int level = 0; level <= Logger::LOGVERBOSE; ++level )
    {
        Logger::setupLogLevel( level );
        QCOMPARE( Logger::logLevel(), level );
        QVERIFY( Logger::logLevelEnabled( level ) );

        for ( unsigned int xlevel = 0; xlevel <= Logger::LOGVERBOSE; ++xlevel )
        {
            QCOMPARE( Logger::logLevelEnabled( xlevel ), xlevel <= level );
        }
    }
}

void
LibCalamaresTests::testLoadSaveYaml()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    QFile f( "settings.conf" );
    // Find the nearest settings.conf to read
    for ( unsigned int up = 0; !f.exists() && ( up < 4 ); ++up )
    {
        f.setFileName( QString( "../" ) + f.fileName() );
    }
    cDebug() << QDir().absolutePath() << f.fileName() << f.exists();
    QVERIFY( f.exists() );

    auto map = CalamaresUtils::loadYaml( f.fileName() );
    QVERIFY( map.contains( "sequence" ) );
    QCOMPARE( map[ "sequence" ].type(), QVariant::List );

    // The source-repo example `settings.conf` has a show and an exec phase
    auto sequence = map[ "sequence" ].toList();
    cDebug() << "Loaded example `settings.conf` sequence:";
    for ( const auto& v : sequence )
    {
        cDebug() << Logger::SubEntry << v;
        QCOMPARE( v.type(), QVariant::Map );
        QVERIFY( v.toMap().contains( "show" ) || v.toMap().contains( "exec" ) );
    }

    CalamaresUtils::saveYaml( "out.yaml", map );

    auto other_map = CalamaresUtils::loadYaml( "out.yaml" );
    CalamaresUtils::saveYaml( "out2.yaml", other_map );
    QCOMPARE( map, other_map );

    QFile::remove( "out.yaml" );
    QFile::remove( "out2.yaml" );
}

static QStringList
findConf( const QDir& d )
{
    QStringList mine;
    if ( d.exists() )
    {
        QString path = d.absolutePath();
        path.append( d.separator() );
        for ( const auto& confname : d.entryList( { "*.conf" } ) )
            mine.append( path + confname );
        for ( const auto& subdirname : d.entryList( QDir::AllDirs | QDir::NoDotAndDotDot ) )
        {
            QDir subdir( d );
            subdir.cd( subdirname );
            mine.append( findConf( subdir ) );
        }
    }
    return mine;
}

void
LibCalamaresTests::recursiveCompareMap( const QVariantMap& a, const QVariantMap& b, int depth )
{
    cDebug() << "Comparing depth" << depth << a.count() << b.count();
    QCOMPARE( a.keys(), b.keys() );
    for ( const auto& k : a.keys() )
    {
        cDebug() << Logger::SubEntry << k;
        const auto& av = a[ k ];
        const auto& bv = b[ k ];

        if ( av.typeName() != bv.typeName() )
        {
            cDebug() << Logger::SubEntry << "a type" << av.typeName() << av;
            cDebug() << Logger::SubEntry << "b type" << bv.typeName() << bv;
        }
        QCOMPARE( av.typeName(), bv.typeName() );
        if ( av.canConvert< QVariantMap >() )
        {
            recursiveCompareMap( av.toMap(), bv.toMap(), depth + 1 );
        }
        else
        {
            QCOMPARE( av, bv );
        }
    }
}


void
LibCalamaresTests::testLoadSaveYamlExtended()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    bool loaded_ok;
    for ( const auto& confname : findConf( QDir( "../src" ) ) )
    {
        loaded_ok = true;
        cDebug() << "Testing" << confname;
        auto map = CalamaresUtils::loadYaml( confname, &loaded_ok );
        QVERIFY( loaded_ok );
        QVERIFY( CalamaresUtils::saveYaml( "out.yaml", map ) );
        auto othermap = CalamaresUtils::loadYaml( "out.yaml", &loaded_ok );
        QVERIFY( loaded_ok );
        QCOMPARE( map.keys(), othermap.keys() );
        recursiveCompareMap( map, othermap, 0 );
        QCOMPARE( map, othermap );
    }
    QFile::remove( "out.yaml" );
}

void
LibCalamaresTests::testCommands()
{
    using CalamaresUtils::System;
    auto r = System::runCommand( System::RunLocation::RunInHost, { "/bin/ls", "/tmp" } );

    QVERIFY( r.getExitCode() == 0 );

    QTemporaryFile tf( "/tmp/calamares-test-XXXXXX" );
    QVERIFY( tf.open() );
    QVERIFY( !tf.fileName().isEmpty() );

    QFileInfo tfn( tf.fileName() );
    QVERIFY( !r.getOutput().contains( tfn.fileName() ) );

    // Run ls again, now that the file exists
    r = System::runCommand( System::RunLocation::RunInHost, { "/bin/ls", "/tmp" } );
    QVERIFY( r.getOutput().contains( tfn.fileName() ) );

    // .. and without a working directory set, assume builddir != /tmp
    r = System::runCommand( System::RunLocation::RunInHost, { "/bin/ls" } );
    QVERIFY( !r.getOutput().contains( tfn.fileName() ) );

    r = System::runCommand( System::RunLocation::RunInHost, { "/bin/ls" }, "/tmp" );
    QVERIFY( r.getOutput().contains( tfn.fileName() ) );
}

void
LibCalamaresTests::testCommandExpansion_data()
{
    QTest::addColumn< QString >( "command" );
    QTest::addColumn< QString >( "expected" );

    QTest::newRow( "empty" ) << QString() << QString();
    QTest::newRow( "ls   " ) << QStringLiteral( "ls" ) << QStringLiteral( "ls" );
    QTest::newRow( "user " ) << QStringLiteral( "chmod $USER" ) << QStringLiteral( "chmod alice" );
}

void
LibCalamaresTests::testCommandExpansion()
{
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );
    gs->insert( QStringLiteral( "username" ), QStringLiteral( "alice" ) );

    QFETCH( QString, command );
    QFETCH( QString, expected );
    CalamaresUtils::CommandLine c( command, std::chrono::seconds( 0 ) );
    CalamaresUtils::CommandLine e = c.expand();

    QCOMPARE( c.command(), command );
    QCOMPARE( e.command(), expected );
}

void
LibCalamaresTests::testUmask()
{
    struct stat mystat;

    QTemporaryFile ft;
    QVERIFY( ft.open() );

    // m gets the previous value of the mask (depends on the environment the
    // test is run in, might be 002, might be 077), ..
    mode_t m = CalamaresUtils::setUMask( 022 );
    QCOMPARE( CalamaresUtils::setUMask( m ), mode_t( 022 ) );  // But now most recently set was 022

    for ( mode_t i = 0; i <= 0777 /* octal! */; ++i )
    {
        QByteArray name = ( ft.fileName() + QChar( '.' ) + QString::number( i, 8 ) ).toLatin1();
        CalamaresUtils::UMask um( i );
        int fd = creat( name, 0777 );
        QVERIFY( fd >= 0 );
        close( fd );
        QFileInfo fi( name );
        QVERIFY( fi.exists() );
        QCOMPARE( stat( name, &mystat ), 0 );
        QCOMPARE( mystat.st_mode & 0777, 0777 & ~i );
        QCOMPARE( unlink( name ), 0 );
    }
    QCOMPARE( CalamaresUtils::setUMask( 022 ), m );
    QCOMPARE( CalamaresUtils::setUMask( m ), mode_t( 022 ) );
}

void
LibCalamaresTests::testEntropy()
{
    QByteArray data;

    auto r0 = CalamaresUtils::getEntropy( 0, data );
    QCOMPARE( CalamaresUtils::EntropySource::None, r0 );
    QCOMPARE( data.size(), 0 );

    auto r1 = CalamaresUtils::getEntropy( 16, data );
    QVERIFY( r1 != CalamaresUtils::EntropySource::None );
    QCOMPARE( data.size(), 16 );
    // This can randomly fail (but not often)
    QVERIFY( data.at( data.size() - 1 ) != char( 0xcb ) );

    auto r2 = CalamaresUtils::getEntropy( 8, data );
    QVERIFY( r2 != CalamaresUtils::EntropySource::None );
    QCOMPARE( data.size(), 8 );
    QCOMPARE( r1, r2 );
    // This can randomly fail (but not often)
    QVERIFY( data.at( data.size() - 1 ) != char( 0xcb ) );
}

void
LibCalamaresTests::testPrintableEntropy()
{
    QString s;

    auto r0 = CalamaresUtils::getPrintableEntropy( 0, s );
    QCOMPARE( CalamaresUtils::EntropySource::None, r0 );
    QCOMPARE( s.length(), 0 );

    auto r1 = CalamaresUtils::getPrintableEntropy( 16, s );
    QVERIFY( r1 != CalamaresUtils::EntropySource::None );
    QCOMPARE( s.length(), 16 );
    for ( QChar c : s )
    {
        QVERIFY( c.isPrint() );
        QCOMPARE( c.row(), uchar( 0 ) );
        QVERIFY( c.cell() > 32 );  // ASCII SPACE
        QVERIFY( c.cell() < 127 );
    }
}

void
LibCalamaresTests::testOddSizedPrintable()
{
    QString s;
    for ( int l = 0; l <= 37; ++l )
    {
        auto r = CalamaresUtils::getPrintableEntropy( l, s );
        if ( l == 0 )
        {
            QCOMPARE( r, CalamaresUtils::EntropySource::None );
        }
        else
        {
            QVERIFY( r != CalamaresUtils::EntropySource::None );
        }
        QCOMPARE( s.length(), l );

        for ( QChar c : s )
        {
            QVERIFY( c.isPrint() );
            QCOMPARE( c.row(), uchar( 0 ) );
            QVERIFY( c.cell() > 32 );  // ASCII SPACE
            QVERIFY( c.cell() < 127 );
        }
    }
}

void
LibCalamaresTests::testPointerSetter()
{
    int special = 17;

    QCOMPARE( special, 17 );
    {
        cScopedAssignment p( &special );
    }
    QCOMPARE( special, 17 );
    {
        cScopedAssignment p( &special );
        p = 18;
    }
    QCOMPARE( special, 18 );
    {
        cScopedAssignment p( &special );
        p = 20;
        p = 3;
    }
    QCOMPARE( special, 3 );
    {
        cScopedAssignment< int > p( nullptr );
    }
    QCOMPARE( special, 3 );
    {
        // "don't do this" .. order of destructors is important
        cScopedAssignment p( &special );
        cScopedAssignment q( &special );
        p = 17;
    }
    QCOMPARE( special, 17 );
    {
        // "don't do this" .. order of destructors is important
        cScopedAssignment p( &special );
        cScopedAssignment q( &special );
        p = 34;
        q = 2;
        // q destroyed first, then p
    }
    QCOMPARE( special, 34 );
}


/* Demonstration of Traits support for has-a-method or not.
 *
 * We have two classes, c1 and c2; one has a method do_the_thing() and the
 * other does not. A third class, Thinginator, has a method thingify(),
 * which should call do_the_thing() of its argument if it exists.
 */

struct c1
{
    int do_the_thing() { return 2; }
};
struct c2
{
};

DECLARE_HAS_METHOD( do_the_thing )

struct Thinginator
{
public:
    /// When class T has function do_the_thing()
    template < class T >
    int thingify( T& t, const std::true_type& )
    {
        return t.do_the_thing();
    }

    template < class T >
    int thingify( T&, const std::false_type& )
    {
        return -1;
    }

    template < class T >
    int thingify( T& t )
    {
        return thingify( t, has_do_the_thing< T > {} );
    }
};


void
LibCalamaresTests::testTraits()
{
    has_do_the_thing< c1 > x {};
    has_do_the_thing< c2 > y {};

    QVERIFY( x );
    QVERIFY( !y );

    c1 c1 {};
    c2 c2 {};

    QCOMPARE( c1.do_the_thing(), 2 );

    Thinginator t;
    QCOMPARE( t.thingify( c1 ), 2 );  // Calls c1::do_the_thing()
    QCOMPARE( t.thingify( c2 ), -1 );
}

void
LibCalamaresTests::testVariantStringListCode()
{
    using namespace CalamaresUtils;
    const QString key( "strings" );
    {
        // Things that are not stringlists
        QVariantMap m;
        QCOMPARE( getStringList( m, key ), QStringList {} );
        m.insert( key, 17 );
        QCOMPARE( getStringList( m, key ), QStringList {} );
        m.insert( key, QVariant {} );
        QCOMPARE( getStringList( m, key ), QStringList {} );
    }

    {
        // Things that are **like** stringlists
        QVariantMap m;
        m.insert( key, QString( "astring" ) );
        QCOMPARE( getStringList( m, key ).count(), 1 );
        QCOMPARE( getStringList( m, key ),
                  QStringList { "astring" } );  // A single string **can** be considered a stringlist!
        m.insert( key, QString( "more strings" ) );
        QCOMPARE( getStringList( m, key ).count(), 1 );
        QCOMPARE( getStringList( m, key ), QStringList { "more strings" } );
        m.insert( key, QString() );
        QCOMPARE( getStringList( m, key ).count(), 1 );
        QCOMPARE( getStringList( m, key ), QStringList { QString() } );
    }

    {
        // Things that are definitely stringlists
        QVariantMap m;
        m.insert( key, QStringList { "aap", "noot" } );
        QCOMPARE( getStringList( m, key ).count(), 2 );
        QVERIFY( getStringList( m, key ).contains( "aap" ) );
        QVERIFY( !getStringList( m, key ).contains( "mies" ) );
    }
}

void
LibCalamaresTests::testVariantStringListYAMLDashed()
{
    using namespace CalamaresUtils;
    const QString key( "strings" );

    // Looks like a stringlist to me
    QTemporaryFile f;
    QVERIFY( f.open() );
    f.write( R"(---
strings:
    - aap
    - noot
    - mies
)" );
    f.close();
    bool ok = false;
    QVariantMap m = loadYaml( f.fileName(), &ok );

    QVERIFY( ok );
    QCOMPARE( m.count(), 1 );
    QVERIFY( m.contains( key ) );

    QVERIFY( getStringList( m, key ).contains( "aap" ) );
    QVERIFY( getStringList( m, key ).contains( "mies" ) );
    QVERIFY( !getStringList( m, key ).contains( "lam" ) );
}

void
LibCalamaresTests::testVariantStringListYAMLBracketed()
{
    using namespace CalamaresUtils;
    const QString key( "strings" );

    // Looks like a stringlist to me
    QTemporaryFile f;
    QVERIFY( f.open() );
    f.write( R"(---
strings: [ aap, noot, mies ]
)" );
    f.close();
    bool ok = false;
    QVariantMap m = loadYaml( f.fileName(), &ok );

    QVERIFY( ok );
    QCOMPARE( m.count(), 1 );
    QVERIFY( m.contains( key ) );

    QVERIFY( getStringList( m, key ).contains( "aap" ) );
    QVERIFY( getStringList( m, key ).contains( "mies" ) );
    QVERIFY( !getStringList( m, key ).contains( "lam" ) );
}

void
LibCalamaresTests::testStringTruncation()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    using namespace Calamares::String;

    const QString longString( R"(---
--- src/libcalamares/utils/String.h
+++ src/libcalamares/utils/String.h
@@ -62,15 +62,22 @@ DLLEXPORT QString removeDiacritics( const QString& string );
  */
 DLLEXPORT QString obscure( const QString& string );

+/** @brief Parameter for counting lines at beginning and end of string
+ *
+ * This is used by truncateMultiLine() to indicate how many lines from
+ * the beginning and how many from the end should be kept.
+ */
 struct LinesStartEnd
 {
-    int atStart;
-    int atEnd;
+    int atStart = 0;
+    int atEnd = 0;
)" );

    const int sufficientLength = 812;
    // There's 18 lines in all
    QCOMPARE( longString.count( '\n' ), 18 );
    QVERIFY( longString.length() < sufficientLength );

    // If we ask for more, we get everything back
    QCOMPARE( longString, truncateMultiLine( longString, LinesStartEnd { 20, 0 }, CharCount { sufficientLength } ) );
    QCOMPARE( longString, truncateMultiLine( longString, LinesStartEnd { 0, 20 }, CharCount { sufficientLength } ) );

    // If we ask for no lines, only characters, we get that
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 0, 0 }, CharCount { 4 } );
        QCOMPARE( s.length(), 4 );
        QCOMPARE( s, QString( "---\n" ) );
    }
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 0, 0 }, CharCount { sufficientLength } );
        QCOMPARE( s, longString );
    }

    // Lines at the start
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 4, 0 }, CharCount { sufficientLength } );
        QVERIFY( s.length() > 1 );
        QVERIFY( longString.startsWith( s ) );
        cDebug() << "Result-line" << Logger::Quote << s;
        QCOMPARE( s.count( '\n' ), 4 );
    }

    // Lines at the end
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 0, 4 }, CharCount { sufficientLength } );
        QVERIFY( s.length() > 1 );
        QVERIFY( longString.endsWith( s ) );
        cDebug() << "Result-line" << Logger::Quote << s;
        QCOMPARE( s.count( '\n' ), 4 );
    }

    // Lines at both ends
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 2, 2 }, CharCount { sufficientLength } );
        QVERIFY( s.length() > 1 );
        cDebug() << "Result-line" << Logger::Quote << s;
        QCOMPARE( s.count( '\n' ), 4 );

        auto firsttwo = truncateMultiLine( s, LinesStartEnd { 2, 0 }, CharCount { sufficientLength } );
        auto lasttwo = truncateMultiLine( s, LinesStartEnd { 0, 2 }, CharCount { sufficientLength } );
        QCOMPARE( firsttwo + lasttwo, s );
        QCOMPARE( firsttwo.count( '\n' ), 2 );
        QVERIFY( longString.startsWith( firsttwo ) );
        QVERIFY( longString.endsWith( lasttwo ) );
    }
}

void
LibCalamaresTests::testStringTruncationShorter()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    using namespace Calamares::String;

    const QString longString( R"(Some strange string artifacts appeared, leading to `{1?}` being
displayed in various user-facing messages. These have been removed
and the translations updated.)" );
    const char NEWLINE = '\n';

    const int insufficientLength = 42;
    // There's 2 newlines in all, no trailing newline
    QVERIFY( !longString.endsWith( NEWLINE ) );
    QCOMPARE( longString.count( NEWLINE ), 2 );
    QVERIFY( longString.length() > insufficientLength );
    // Even the first line must be more than the insufficientLength
    QVERIFY( longString.indexOf( NEWLINE ) > insufficientLength );

    // Grab first line, untruncated
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 1, 0 } );
        QVERIFY( s.length() > 1 );
        QVERIFY( longString.startsWith( s ) );
        QVERIFY( s.endsWith( NEWLINE ) );
        QVERIFY( s.endsWith( "being\n" ) );
        QVERIFY( s.startsWith( "Some " ) );
    }

    // Grab last line, untruncated
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 0, 1 } );
        QVERIFY( s.length() > 1 );
        QVERIFY( longString.endsWith( s ) );
        QVERIFY( !s.endsWith( NEWLINE ) );
        QVERIFY( s.endsWith( "updated." ) );
        QCOMPARE( s.count( NEWLINE ), 0 );  // Because last line doesn't end with a newline
        QVERIFY( s.startsWith( "and the " ) );
    }

    // Grab last two lines, untruncated
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 0, 2 } );
        QVERIFY( s.length() > 1 );
        QVERIFY( longString.endsWith( s ) );
        QVERIFY( !s.endsWith( NEWLINE ) );
        QVERIFY( s.endsWith( "updated." ) );
        QCOMPARE( s.count( NEWLINE ), 1 );  // Because last line doesn't end with a newline
        QVERIFY( s.startsWith( "displayed in " ) );
    }

    // First line, truncated
    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 1, 0 }, CharCount { insufficientLength } );
        cDebug() << "Result-line" << Logger::Quote << s;
        QVERIFY( s.length() > 1 );
        QVERIFY( s.endsWith( NEWLINE ) );
        QVERIFY( s.startsWith( "Some " ) );
        // Because the first line has a newline, the truncated version does too,
        //   but that makes it one longer than requested.
        QCOMPARE( s.length(), insufficientLength + 1 );
        QVERIFY( longString.startsWith( s.left( insufficientLength ) ) );
    }

    // Last line, truncated; this line is quite short
    {
        const int quiteShort = 8;
        QVERIFY( longString.lastIndexOf( NEWLINE ) < longString.length() - quiteShort );

        auto s = truncateMultiLine( longString, LinesStartEnd { 0, 1 }, CharCount { quiteShort } );
        cDebug() << "Result-line" << Logger::Quote << s;
        QVERIFY( s.length() > 1 );
        QVERIFY( !s.endsWith( NEWLINE ) );  // Because the original doesn't either
        QVERIFY( s.startsWith( "upda" ) );
        QCOMPARE( s.length(), quiteShort );  // No extra newlines
        QVERIFY( longString.endsWith( s ) );
    }

    // First and last, but both truncated
    {
        const int quiteShort = 16;
        QVERIFY( longString.indexOf( NEWLINE ) > quiteShort );
        QVERIFY( longString.lastIndexOf( NEWLINE ) < longString.length() - quiteShort );

        auto s = truncateMultiLine( longString, LinesStartEnd { 1, 1 }, CharCount { quiteShort } );
        cDebug() << "Result-line" << Logger::Quote << s;
        QVERIFY( s.length() > 1 );
        QVERIFY( !s.endsWith( NEWLINE ) );  // Because the original doesn't either
        QVERIFY( s.startsWith( "Some " ) );
        QVERIFY( s.endsWith( "updated." ) );
        QCOMPARE( s.length(), quiteShort + 1 );  // Newline between front and back part
    }
}

void
LibCalamaresTests::testStringTruncationDegenerate()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    using namespace Calamares::String;

    // This is quite long, 1 line only, with no newlines
    const QString longString( "The portscout new distfile checker has detected that one or more of your "
                              "ports appears to be out of date. Please take the opportunity to check "
                              "each of the ports listed below, and if possible and appropriate, "
                              "submit/commit an update. If any ports have already been updated, you can "
                              "safely ignore the entry." );

    const char NEWLINE = '\n';
    const int quiteShort = 16;
    QVERIFY( longString.length() > quiteShort );
    QVERIFY( !longString.contains( NEWLINE ) );
    QVERIFY( longString.indexOf( NEWLINE ) < 0 );

    {
        auto s = truncateMultiLine( longString, LinesStartEnd { 1, 0 }, CharCount { quiteShort } );
        cDebug() << "Result-line" << Logger::Quote << s;
        QVERIFY( s.length() > 1 );
        QCOMPARE( s.length(), quiteShort );  // No newline between front and back part
        QVERIFY( s.startsWith( "The port" ) );  // 8, which is quiteShort / 2
        QVERIFY( s.endsWith( "e entry." ) );  // also 8 chars

        auto t = truncateMultiLine( longString, LinesStartEnd { 2, 2 }, CharCount { quiteShort } );
        QCOMPARE( s, t );
    }
}

void
LibCalamaresTests::testStringRemoveLeading_data()
{
    QTest::addColumn< QString >( "string" );
    QTest::addColumn< char >( "c" );
    QTest::addColumn< QString >( "result" );

    QTest::newRow( "empty" ) << QString() << '/' << QString();
    QTest::newRow( "one-slash" ) << QStringLiteral( "/tmp" ) << '/' << QStringLiteral( "tmp" );
    QTest::newRow( "two-slash" ) << QStringLiteral( "//tmp" ) << '/' << QStringLiteral( "tmp" );
    QTest::newRow( "multi-slash" ) << QStringLiteral( "/tmp/p" ) << '/' << QStringLiteral( "tmp/p" );
    QTest::newRow( "later-slash" ) << QStringLiteral( "@/tmp" ) << '/' << QStringLiteral( "@/tmp" );
    QTest::newRow( "all-one-slash" ) << QStringLiteral( "/" ) << '/' << QString();
    QTest::newRow( "all-many-slash" ) << QStringLiteral( "////////////////////" ) << '/' << QString();
    QTest::newRow( "trailing" ) << QStringLiteral( "tmp/" ) << '/' << QStringLiteral( "tmp/" );
}

void
LibCalamaresTests::testStringRemoveLeading()
{
    QFETCH( QString, string );
    QFETCH( char, c );
    QFETCH( QString, result );

    const QString initial = string;
    Calamares::String::removeLeading( string, c );
    QCOMPARE( string, result );
}

void
LibCalamaresTests::testStringRemoveTrailing_data()
{
    QTest::addColumn< QString >( "string" );
    QTest::addColumn< char >( "c" );
    QTest::addColumn< QString >( "result" );

    QTest::newRow( "empty" ) << QString() << '/' << QString();
    QTest::newRow( "one-slash" ) << QStringLiteral( "/tmp" ) << '/' << QStringLiteral( "/tmp" );
    QTest::newRow( "two-slash" ) << QStringLiteral( "//tmp" ) << '/' << QStringLiteral( "//tmp" );
    QTest::newRow( "multi-slash" ) << QStringLiteral( "/tmp//p/" ) << '/' << QStringLiteral( "/tmp//p" );
    QTest::newRow( "later-slash" ) << QStringLiteral( "@/tmp/@" ) << '/' << QStringLiteral( "@/tmp/@" );
    QTest::newRow( "later-slash2" ) << QStringLiteral( "@/tmp/@//" ) << '/' << QStringLiteral( "@/tmp/@" );
    QTest::newRow( "all-one-slash" ) << QStringLiteral( "/" ) << '/' << QString();
    QTest::newRow( "all-many-slash" ) << QStringLiteral( "////////////////////" ) << '/' << QString();
    QTest::newRow( "trailing" ) << QStringLiteral( "tmp/" ) << '/' << QStringLiteral( "tmp" );
}

void
LibCalamaresTests::testStringRemoveTrailing()
{
    QFETCH( QString, string );
    QFETCH( char, c );
    QFETCH( QString, result );

    const QString initial = string;
    Calamares::String::removeTrailing( string, c );
    QCOMPARE( string, result );
}

void
LibCalamaresTests::testStringMacroExpander_data()
{
    QTest::addColumn< QString >( "source" );
    QTest::addColumn< QString >( "result" );
    QTest::addColumn< QStringList >( "errors" );

    QTest::newRow( "empty   " ) << QString() << QString() << QStringList {};
    QTest::newRow( "constant" ) << QStringLiteral( "bunnies!" ) << QStringLiteral( "bunnies!" ) << QStringList {};
    QTest::newRow( "escaped " ) << QStringLiteral( "$$bun" ) << QStringLiteral( "$bun" )
                                << QStringList {};  // Double $$ is an escaped $
    QTest::newRow( "whole   " ) << QStringLiteral( "${ROOT}" ) << QStringLiteral( "wortel" ) << QStringList {};
    QTest::newRow( "unbraced" ) << QStringLiteral( "$ROOT" ) << QStringLiteral( "wortel" )
                                << QStringList {};  // Does not need {}
    QTest::newRow( "bad-var1" ) << QStringLiteral( "${ROOF}" ) << QStringLiteral( "${ROOF}" )
                                << QStringList { QStringLiteral( "ROOF" ) };  // Not replaced
    QTest::newRow( "twice   " ) << QStringLiteral( "${ROOT}x${ROOT}" ) << QStringLiteral( "wortelxwortel" )
                                << QStringList {};
    QTest::newRow( "bad-var2" ) << QStringLiteral( "${ROOT}x${ROPE}" ) << QStringLiteral( "wortelx${ROPE}" )
                                << QStringList { QStringLiteral( "ROPE" ) };  // Not replaced
    // This is a borked string with a "nested" variable. The variable-name-
    // scanner goes from ${ to the next } and tries to match that.
    QTest::newRow( "confuse1" ) << QStringLiteral( "${RO${ROOT}" ) << QStringLiteral( "${ROwortel" )
                                << QStringList { "RO${ROOT" };
    // This one doesn't have a { for the first name to match with
    QTest::newRow( "confuse2" ) << QStringLiteral( "$RO${ROOT}" ) << QStringLiteral( "$ROwortel" )
                                << QStringList { "RO" };
    // Here we see it just doesn't nest
    QTest::newRow( "confuse3" ) << QStringLiteral( "${RO${ROOT}}" ) << QStringLiteral( "${ROwortel}" )
                                << QStringList { "RO${ROOT" };
}

void
LibCalamaresTests::testStringMacroExpander()
{
    QHash< QString, QString > dict;
    dict.insert( QStringLiteral( "ROOT" ), QStringLiteral( "wortel" ) );

    Calamares::String::DictionaryExpander d;
    d.insert( QStringLiteral( "ROOT" ), QStringLiteral( "wortel" ) );

    QFETCH( QString, source );
    QFETCH( QString, result );
    QFETCH( QStringList, errors );

    QString km_expanded = KMacroExpander::expandMacros( source, dict, '$' );
    QCOMPARE( km_expanded, result );

    QString de_expanded = d.expand( source );
    QCOMPARE( de_expanded, result );
    QCOMPARE( d.errorNames(), errors );
    QCOMPARE( d.hasErrors(), !errors.isEmpty() );
}

static QString
dirname( const QTemporaryDir& d )
{
    return d.path().split( '/' ).last();
}
static QString
dirname( const QDir& d )
{
    return d.absolutePath().split( '/' ).last();
}

// Method under test
extern bool relativeChangeDirectory( QDir& directory, const QString& subdir );

void
LibCalamaresTests::testRunnerDirs()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

    QDir startDir( QDir::current() );
    QTemporaryDir tempDir( "./utilstest" );
    QVERIFY( tempDir.isValid() );
    QVERIFY( startDir.isReadable() );

    // Test changing "downward"
    {
        QDir testDir( QDir::current() );
        QCOMPARE( startDir, testDir );
    }

    {
        QDir testDir( QDir::current() );
        const bool could_change_to_dot = relativeChangeDirectory( testDir, QStringLiteral( "." ) );
        QVERIFY( could_change_to_dot );
        QCOMPARE( startDir, testDir );
    }

    {
        // The tempDir was created inside the current directory, we want only the subdir-name
        QDir testDir( QDir::current() );
        const bool could_change_to_temp = relativeChangeDirectory( testDir, dirname( tempDir ) );
        QVERIFY( could_change_to_temp );
        QVERIFY( startDir != testDir );
        QVERIFY( testDir.absolutePath().startsWith( startDir.absolutePath() ) );
    }

    // Test changing to something that doesn't exist
    {
        QDir testDir( QDir::current() );
        const bool could_change_to_bogus = relativeChangeDirectory( testDir, QStringLiteral( "bogus" ) );
        QVERIFY( !could_change_to_bogus );
        QCOMPARE( startDir, testDir );  // Must be unchanged
    }

    // Testing escape-from-start
    {
        // Escape briefly from the start
        QDir testDir( QDir::current() );
        const bool could_change_to_current
            = relativeChangeDirectory( testDir, QStringLiteral( "../" ) + dirname( startDir ) );
        QVERIFY( could_change_to_current );
        QCOMPARE( startDir, testDir );  // The change succeeded, but net effect is zero

        const bool could_change_to_temp = relativeChangeDirectory(
            testDir, QStringLiteral( "../" ) + dirname( startDir ) + QStringLiteral( "/./" ) + dirname( tempDir ) );
        QVERIFY( could_change_to_temp );
        QVERIFY( startDir != testDir );
        QVERIFY( testDir.absolutePath().startsWith( startDir.absolutePath() ) );
    }

    {
        // Escape?
        QDir testDir( QDir::current() );
        const bool could_change_to_parent = relativeChangeDirectory( testDir, QStringLiteral( "../" ) );
        QVERIFY( !could_change_to_parent );
        QCOMPARE( startDir, testDir );  // Change failed

        const bool could_change_to_tmp = relativeChangeDirectory( testDir, QStringLiteral( "/tmp" ) );
        QVERIFY( !could_change_to_tmp );
        QCOMPARE( startDir, testDir );

        const bool could_change_to_elsewhere = relativeChangeDirectory( testDir, QStringLiteral( "../src" ) );
        QVERIFY( !could_change_to_elsewhere );
        QCOMPARE( startDir, testDir );
    }
}

// Method under test
extern std::pair< bool, QDir > calculateWorkingDirectory( Calamares::Utils::RunLocation location,
                                                          const QString& directory );

void
LibCalamaresTests::testCalculateWorkingDirectory()
{
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;

    if ( !gs )
    {
        cDebug() << "Creating new JobQueue";
        (void)new Calamares::JobQueue();
        gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    }
    QVERIFY( gs );

    // Working with a rootMountPoint set
    QTemporaryDir tempRoot( QDir::tempPath() + QStringLiteral( "/test-job-XXXXXX" ) );
    gs->insert( "rootMountPoint", tempRoot.path() );

    {
        auto [ ok, d ] = calculateWorkingDirectory( CalamaresUtils::System::RunLocation::RunInHost, QString() );
        QVERIFY( ok );
        QCOMPARE( d, QDir::current() );
    }
    {
        auto [ ok, d ] = calculateWorkingDirectory( CalamaresUtils::System::RunLocation::RunInTarget, QString() );
        QVERIFY( ok );
        QCOMPARE( d.absolutePath(), tempRoot.path() );
    }

    gs->remove( "rootMountPoint" );
    {
        auto [ ok, d ] = calculateWorkingDirectory( CalamaresUtils::System::RunLocation::RunInHost, QString() );
        QVERIFY( ok );
        QCOMPARE( d, QDir::current() );
    }
    {
        auto [ ok, d ] = calculateWorkingDirectory( CalamaresUtils::System::RunLocation::RunInTarget, QString() );
        QVERIFY( !ok );
        QCOMPARE( d, QDir::current() );
    }
}

void
LibCalamaresTests::testRunnerOutput()
{
    cDebug() << "Testing ls";
    {
        Calamares::Utils::Runner r( { "ls", "-d", "." } );
        QSignalSpy spy( &r, &decltype( r )::output );
        r.enableOutputProcessing();

        auto result = r.run();
        QCOMPARE( result.getExitCode(), 0 );
        QCOMPARE( result.getOutput(), QString() );
        QCOMPARE( spy.count(), 1 );
    }

    cDebug() << "Testing cat";
    {
        Calamares::Utils::Runner r( { "cat" } );
        QSignalSpy spy( &r, &decltype( r )::output );
        r.enableOutputProcessing().setInput( QStringLiteral( "hello\nworld\n\n!\n" ) );

        {
            auto result = r.run();
            QCOMPARE( result.getExitCode(), 0 );
            QCOMPARE( result.getOutput(), QString() );
            QCOMPARE( spy.count(), 4 );
        }

        r.setInput( QStringLiteral( "yo\ndogg" ) );
        {
            auto result = r.run();
            QCOMPARE( result.getExitCode(), 0 );
            QCOMPARE( result.getOutput(), QString() );
            QCOMPARE( spy.count(), 6 );  // 4 from before, +2 here
        }
    }

    cDebug() << "Testing cat (again)";
    {
        QStringList collectedOutput;

        Calamares::Utils::Runner r( { "cat" } );
        r.enableOutputProcessing().setInput( QStringLiteral( "hello\nworld\n\n!\n" ) );
        QObject::connect( &r, &decltype( r )::output, [ &collectedOutput ]( QString s ) { collectedOutput << s; } );

        {
            auto result = r.run();
            QCOMPARE( result.getExitCode(), 0 );
            QCOMPARE( result.getOutput(), QString() );
            QCOMPARE( collectedOutput.count(), 4 );
            QVERIFY( collectedOutput.contains( QStringLiteral( "world\n" ) ) );
        }

        r.setInput( QStringLiteral( "yo\ndogg" ) );
        {
            auto result = r.run();
            QCOMPARE( result.getExitCode(), 0 );
            QCOMPARE( result.getOutput(), QString() );
            QCOMPARE( collectedOutput.count(), 6 );
            QVERIFY( collectedOutput.contains( QStringLiteral( "dogg" ) ) );  // no newline
        }
    }
}


CalamaresUtils::System*
file_setup( const QTemporaryDir& tempRoot )
{
    CalamaresUtils::System* ss = CalamaresUtils::System::instance();
    if ( !ss )
    {
        ss = new CalamaresUtils::System( true );
    }

    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( !gs )
    {
        cDebug() << "Creating new JobQueue";
        (void)new Calamares::JobQueue();
        gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    }
    if ( gs )
    {
        // Working with a rootMountPoint set
        gs->insert( "rootMountPoint", tempRoot.path() );
    }
    return ss;
}

void
LibCalamaresTests::testReadWriteFile()
{
    static const QByteArray otherContents( "first\nsecond\n" );

    QTemporaryDir tempRoot( QDir::tempPath() + QStringLiteral( "/test-job-XXXXXX" ) );
    auto* ss = file_setup( tempRoot );

    QVERIFY( ss );
    {
        auto fullPath = ss->createTargetFile( "test0", QByteArray(), CalamaresUtils::System::WriteMode::Overwrite );
        QVERIFY( fullPath );
        QVERIFY( !fullPath.path().isEmpty() );

        QFileInfo fi( fullPath.path() );
        QVERIFY( fi.exists() );
        QVERIFY( fi.isFile() );
        QCOMPARE( fi.size(), 0 );
    }
    // It won't overwrite unless you ask for it
    {
        auto fullPath = ss->createTargetFile( "test0", otherContents );
        QVERIFY( !fullPath );  // Failed, because it won't overwrite
        QCOMPARE( fullPath.code(), decltype( fullPath )::Code::AlreadyExists );
        QVERIFY( fullPath.path().isEmpty() );  // Because it wasn't written

        QFileInfo fi( tempRoot.filePath( "test0" ) );  // Compute the name some other way
        QVERIFY( fi.exists() );
        QVERIFY( fi.isFile() );
        QCOMPARE( fi.size(), 0 );
    }
    // But it will if you say so explicitly
    {
        auto fullPath = ss->createTargetFile( "test0", otherContents, CalamaresUtils::System::WriteMode::Overwrite );
        QVERIFY( fullPath );
        QVERIFY( !fullPath.path().isEmpty() );

        QFileInfo fi( fullPath.path() );
        QVERIFY( fi.exists() );
        QVERIFY( fi.isFile() );
        QCOMPARE( fi.size(), 13 );
    }

    // Now it's been written, we can read it, too
    {
        auto contents = ss->readTargetFile( "test0" );
        QVERIFY( !contents.isEmpty() );
        QCOMPARE( contents.count(), 2 );
        QCOMPARE( contents[ 0 ], QStringLiteral( "first" ) );  // No trailing \n
        QCOMPARE( contents[ 1 ], QStringLiteral( "second" ) );  // No trailing \n
    }
}


QTEST_GUILESS_MAIN( LibCalamaresTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
