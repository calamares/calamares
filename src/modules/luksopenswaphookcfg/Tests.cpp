/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "LOSHInfo.h"
#include "LOSHJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QtTest/QtTest>

// LOSH = LUKS Open Swap Hook (Job)

// Implementation details
extern QString get_assignment_part( const QString& line );
extern void write_openswap_conf( const QString& path, QStringList& contents, const LOSHInfo& info );

class LOSHTests : public QObject
{
    Q_OBJECT
public:
    LOSHTests();
    ~LOSHTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testAssignmentExtraction_data();
    void testAssignmentExtraction();

    void testLOSHInfo();
    void testConfigWriting();
    void testJob();
};

LOSHTests::LOSHTests() {}

void
LOSHTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "LOSH test started.";
}


void
LOSHTests::testAssignmentExtraction_data()
{
    QTest::addColumn< QString >( "line" );
    QTest::addColumn< QString >( "match" );

    QTest::newRow( "empty" ) << QString() << QString();
    QTest::newRow( "comment-only1" ) << QStringLiteral( "#  " ) << QString();
    QTest::newRow( "comment-only2" ) << QStringLiteral( "###" ) << QString();
    QTest::newRow( "comment-only3" ) << QStringLiteral( "# # #" ) << QString();

    QTest::newRow( "comment-text" ) << QStringLiteral( "#   NOTE:" ) << QString();
    QTest::newRow( "comment-story" ) << QStringLiteral( "# This is a shell comment" ) << QString();
    // We look for assignments, but only for single-words
    QTest::newRow( "comment-space-eq" ) << QStringLiteral( "# Check that a = b" ) << QString();


    QTest::newRow( "assignment1" ) << QStringLiteral( "a=1" ) << QStringLiteral( "a" );
    QTest::newRow( "assignment2" ) << QStringLiteral( "a = 1" ) << QStringLiteral( "a" );
    QTest::newRow( "assignment3" ) << QStringLiteral( "#   a=1" ) << QStringLiteral( "a" );
    QTest::newRow( "assignment4" ) << QStringLiteral( "cows   = 12" ) << QStringLiteral( "cows" );
    QTest::newRow( "assignment5" ) << QStringLiteral( "#   # cows=1" ) << QStringLiteral( "cows" );
    QTest::newRow( "assignment6" ) << QStringLiteral( "# moose='cool'  # not cows" ) << QStringLiteral( "moose" );
    QTest::newRow( "assignment7" ) << QStringLiteral( " moose=cows=42" ) << QStringLiteral( "moose" );
    QTest::newRow( "assignment8" ) << QStringLiteral( "#swap_device=/dev/something" )
                                   << QStringLiteral( "swap_device" );
    QTest::newRow( "assignment9" ) << QStringLiteral( "# swap_device=/dev/something" )
                                   << QStringLiteral( "swap_device" );
    QTest::newRow( "assignment10" ) << QStringLiteral( "swap_device=/dev/something" )
                                    << QStringLiteral( "swap_device" );
}

void
LOSHTests::testAssignmentExtraction()
{
    QFETCH( QString, line );
    QFETCH( QString, match );

    QCOMPARE( get_assignment_part( line ), match );
}

static CalamaresUtils::System*
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

static void
make_valid_loshinfo( LOSHInfo& i )
{
    i.swap_outer_uuid = QStringLiteral( "UUID-0000" );
    i.swap_mapper_name = QStringLiteral( "/dev/mapper/0000" );
    i.swap_device_path = QStringLiteral( "/dev/sda0" );
    i.mountable_keyfile_device = QStringLiteral( "/dev/ada0p0s0" );
}

void
LOSHTests::testLOSHInfo()
{
    LOSHInfo i {};
    QVERIFY( !i.isValid() );

    make_valid_loshinfo( i );
    QVERIFY( i.isValid() );
    QCOMPARE( i.replacementFor( QStringLiteral( "swap_device" ) ), QStringLiteral( "/dev/sda0" ) );
    QCOMPARE( i.replacementFor( QStringLiteral( "duck" ) ), QString() );
}


void
LOSHTests::testConfigWriting()
{
    QTemporaryDir tempRoot( QDir::tempPath() + QStringLiteral( "/test-job-XXXXXX" ) );
    QVERIFY( tempRoot.isValid() );
    auto* ss = file_setup( tempRoot );
    QVERIFY( ss );
    QVERIFY( Calamares::JobQueue::instance()->globalStorage() );
    QVERIFY( QFile::exists( tempRoot.path() ) );
    QVERIFY( QFileInfo( tempRoot.path() ).isDir() );

    const QString targetFilePath = QStringLiteral( "losh.conf" );
    const QString filePath = tempRoot.filePath( targetFilePath );
    QStringList contents { QStringLiteral( "# Calamares demo" ),
                           QStringLiteral( "#  swap_device=a thing" ),
                           QStringLiteral( "#  duck duck swap_device=another" ) };

    // When the information is invalid, file contents are unchanged,
    // and no file is written either.
    LOSHInfo i {};
    QVERIFY( !i.isValid() );
    QVERIFY( !QFile::exists( filePath ) );
    write_openswap_conf( targetFilePath, contents, i );  // Invalid i
    QVERIFY( !QFile::exists( filePath ) );
    QCOMPARE( contents.length(), 3 );
    QCOMPARE( contents.at( 1 ).left( 4 ), QStringLiteral( "#  s" ) );

    // Can we write there at all?
    QFile derp( filePath );
    QVERIFY( derp.open( QIODevice::WriteOnly ) );
    QVERIFY( derp.write( "xx", 2 ) );
    derp.close();
    QVERIFY( QFile::exists( filePath ) );
    QVERIFY( QFile::remove( filePath ) );

    // Once the information is valid, though, the file is written
    make_valid_loshinfo( i );
    QVERIFY( i.isValid() );
    QVERIFY( !QFile::exists( filePath ) );
    write_openswap_conf( targetFilePath, contents, i );  // Now it is valid
    QVERIFY( QFile::exists( filePath ) );
    QCOMPARE( contents.length(), 3 );
    QCOMPARE( i.swap_device_path, QStringLiteral( "/dev/sda0" ) );  // expected key value
    QCOMPARE( contents.at( 1 ), QStringLiteral( "swap_device=/dev/sda0" ) );  // expected line

    // readLine() returns with newlines-added
    QFile f( filePath );
    QVERIFY( f.open( QIODevice::ReadOnly ) );
    QCOMPARE( f.readLine(), QStringLiteral( "# Calamares demo\n" ) );
    QCOMPARE( f.readLine(), QStringLiteral( "swap_device=/dev/sda0\n" ) );
    QCOMPARE( f.readLine(), QStringLiteral( "#  duck duck swap_device=another\n" ) );
    QCOMPARE( f.readLine(), QString() );
    QVERIFY( f.atEnd() );

    // Note how the contents is updated on every write_openswap_conf()
    i.swap_device_path = QStringLiteral( "/dev/zram/0.zram" );
    write_openswap_conf( targetFilePath, contents, i );  // Still valid
    QCOMPARE( contents.length(), 3 );
    QCOMPARE( i.swap_device_path, QStringLiteral( "/dev/zram/0.zram" ) );  // expected key value
    QCOMPARE( contents.at( 1 ), QStringLiteral( "swap_device=/dev/zram/0.zram" ) );  // expected line
}


void
LOSHTests::testJob()
{
    QTemporaryDir tempRoot( QDir::tempPath() + QStringLiteral( "/test-job-XXXXXX" ) );
    QVERIFY( tempRoot.isValid() );
    auto* ss = file_setup( tempRoot );
    QVERIFY( ss );
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );

    {
        QDir d( tempRoot.path() );
        d.mkdir( "etc" );
    }

    QVERIFY( !LOSHInfo::fromGlobalStorage().isValid() );
    QVariantList outerPartition;
    QVariantMap innerPartition;
    innerPartition.insert( "mountPoint", "/" );
    innerPartition.insert( "fs", "ext4" );
    innerPartition.insert( "luksMapperName", "root" );
    innerPartition.insert( "luksUUID", "0000" );
    outerPartition.append( innerPartition );
    innerPartition.remove( "mountPoint" );
    innerPartition.insert( "fs", "linuxswap" );
    innerPartition.insert( "luksMapperName", "swap" );
    innerPartition.insert( "luksUuid", "0001" );
    outerPartition.append( innerPartition );
    gs->insert( "partitions", outerPartition );
    QVERIFY( LOSHInfo::fromGlobalStorage().isValid() );

    LOSHJob j;
    j.setConfigurationMap( QVariantMap() );
    auto jobresult = j.exec();
    QVERIFY( jobresult );

    {
        QFile f( tempRoot.filePath( "etc/openswap.conf" ) );
        QVERIFY( f.exists() );
        QVERIFY( f.open( QIODevice::ReadOnly ) );
        cDebug() << f.readAll();
    }
}


QTEST_GUILESS_MAIN( LOSHTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
