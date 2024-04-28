/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "core/OsproberEntry.h"
#include "core/PartUtils.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/System.h"
#include "utils/Yaml.h"

#include <QByteArray>
#include <QObject>
#include <QtTest/QtTest>

using Calamares::Units::operator""_MiB;

class ConfigTests : public QObject
{
    Q_OBJECT

public:
    ConfigTests();

private Q_SLOTS:
    void initTestCase();
    void testEmptyConfig();
    void testLegacySize();
    void testAll();
    void testWeirdConfig();

    void testNormalFstab();
    void testWeirdFstab();
};

ConfigTests::ConfigTests() = default;

void
ConfigTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    // Ensure we have a system object, expect it to be a "bogus" one
    Calamares::System* system = Calamares::System::instance();
    QVERIFY( system );
    QVERIFY( system->doChroot() );

    // Ensure we have a system-wide GlobalStorage with /tmp as root
    if ( !Calamares::JobQueue::instance() )
    {
        cDebug() << "Creating new JobQueue";
        (void)new Calamares::JobQueue();
    }
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    QVERIFY( gs );
}


void
ConfigTests::testEmptyConfig()
{
    Config c( nullptr );
    c.setConfigurationMap( {} );

    const auto* gs = Calamares::JobQueue::instanceGlobalStorage();
    QVERIFY( gs );

    QVERIFY( c.initialInstallChoice() == Config::InstallChoice::NoChoice );
    QVERIFY( !gs->value( PartUtils::efiFilesystemRecommendedSizeGSKey() ).isValid() );  // Nothing filled in
    QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 300_MiB );  // Default value
    QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 300_MiB );  // Default value

    const auto firmware = gs->value( "firmwareType" ).toString();
    QVERIFY( firmware == "efi" || firmware == "bios" );

    QCOMPARE( gs->value( "efiSystemPartition" ).toString(), "/boot/efi" );  // Default
}

void
ConfigTests::testLegacySize()
{
    Config c( nullptr );

    auto* gs = Calamares::JobQueue::instanceGlobalStorage();
    QVERIFY( gs );


    // Config with just one legacy key
    {
        const auto file = QStringLiteral( BUILD_AS_TEST "/1a-legacy.conf" );
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( file, &ok ) );

        cDebug() << "Tried to load" << file << "success?" << ok;

        QVERIFY( ok );

        QVERIFY( gs->value( PartUtils::efiFilesystemRecommendedSizeGSKey() ).isValid() );  // Something was filled in
        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 100_MiB );  // From config
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 100_MiB );  // Taken from config
    }

    // Different legacy key value
    {
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( QStringLiteral( BUILD_AS_TEST "/1b-legacy.conf" ), &ok ) );

        QVERIFY( ok );

        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 100000000 );  // From config, MB
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 100000000 );  // Taken from config
    }
}

void
ConfigTests::testAll()
{
    Config c( nullptr );

    auto* gs = Calamares::JobQueue::instanceGlobalStorage();
    QVERIFY( gs );


    // Legacy only
    {
        gs->clear();
        const auto file = QStringLiteral( BUILD_AS_TEST "/2a-legacy.conf" );
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( file, &ok ) );

        cDebug() << "Tried to load" << file << "success?" << ok;

        QVERIFY( ok );

        QVERIFY( gs->value( PartUtils::efiFilesystemRecommendedSizeGSKey() ).isValid() );  // Something was filled in
        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 75_MiB );  // From config
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 75_MiB );  // No separate setting

        QCOMPARE( gs->value( "efiSystemPartition" ).toString(), QStringLiteral( "/boot/thisisatest" ) );
        QCOMPARE( gs->value( "efiSystemPartitionName" ).toString(), QStringLiteral( "testLabel" ) );
    }

    // Modern only
    {
        gs->clear();
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( QStringLiteral( BUILD_AS_TEST "/2b-modern.conf" ), &ok ) );

        QVERIFY( ok );

        QVERIFY( PartUtils::efiFilesystemRecommendedSizeGSKey() != PartUtils::efiFilesystemMinimumSizeGSKey() );
        QCOMPARE( gs->value( PartUtils::efiFilesystemRecommendedSizeGSKey() ).toString(),
                  QStringLiteral( "83886080" ) );
        QCOMPARE( gs->value( PartUtils::efiFilesystemMinimumSizeGSKey() ).toString(), QStringLiteral( "68157440" ) );

        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 80_MiB );  // From config
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 65_MiB );  // Taken from config

        QCOMPARE( gs->value( "efiSystemPartition" ).toString(), QStringLiteral( "/boot/thisismodern" ) );
        QCOMPARE( gs->value( "efiSystemPartitionName" ).toString(), QStringLiteral( "UEFI" ) );
    }

    // Mixed settings
    {
        gs->clear();
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( QStringLiteral( BUILD_AS_TEST "/2c-mixed.conf" ), &ok ) );

        QVERIFY( ok );

        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 175_MiB );  // From config
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 80_MiB );  // Taken from config

        QCOMPARE( gs->value( "efiSystemPartition" ).toString(), QStringLiteral( "/boot/thisismixed" ) );
        QCOMPARE( gs->value( "efiSystemPartitionName" ).toString(), QStringLiteral( "legacy" ) );
    }

    // Mixed settings with overlap
    {
        gs->clear();
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( QStringLiteral( BUILD_AS_TEST "/2d-overlap.conf" ), &ok ) );

        QVERIFY( ok );

        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 300_MiB );  // From modern config
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 100_MiB );  // Taken from modern config, legacy ignored

        QCOMPARE( gs->value( "efiSystemPartition" ).toString(), QStringLiteral( "/boot/thisoverlaps" ) );
        QCOMPARE( gs->value( "efiSystemPartitionName" ).toString(), QStringLiteral( "legacy" ) );
    }
}

void
ConfigTests::testWeirdConfig()
{
    Config c( nullptr );

    auto* gs = Calamares::JobQueue::instanceGlobalStorage();
    QVERIFY( gs );
    gs->clear();


    // Config with an invalid minimum size
    {
        const auto file = QStringLiteral( BUILD_AS_TEST "/3a-min-too-large.conf" );
        bool ok = false;
        c.setConfigurationMap( Calamares::YAML::load( file, &ok ) );

        cDebug() << "Tried to load" << file << "success?" << ok;
        QVERIFY( ok );

        QCOMPARE( PartUtils::efiFilesystemRecommendedSize(), 133_MiB );
        QCOMPARE( PartUtils::efiFilesystemMinimumSize(), 133_MiB );  // Config setting was ignored

        QCOMPARE( gs->value( "efiSystemPartitionName" ).toString(), QStringLiteral( "bigmin" ) );
    }
}

void
ConfigTests::testNormalFstab()
{
    const auto contents
        = QByteArrayLiteral( "# A FreeBSD fstab\n"
                             "/dev/nvd0p3                     none            swap    sw              0       0\n" );
    const auto entries = Calamares::fromEtcFstabContents( contents );
    for ( const auto& e : entries )
    {
        QVERIFY( e.isValid() );
    }
    QCOMPARE( entries.count(), 1 );
}

void
ConfigTests::testWeirdFstab()
{
    const auto contents
        = QByteArrayLiteral( "# <file system>             <mount point>  <type>  <options>  <dump>  <pass>\n"
                             "UUID=dae80d0a-f6c7-46f4-a04a-6761f2cfd9b6 /              ext4    defaults,noatime 0 1\n"
                             "UUID=423892d5-a929-41a9-a846-f410cf3fe25b swap           swap    defaults,noatime 0 2\n"
                             "# another comment\n"
                             "borked 2\n"
                             "ok /dev1 ext4 none 0 0\n"
                             "bogus /dev2 ext4 none no later\n"
                             "# comment\n" );
    const auto entries = Calamares::fromEtcFstabContents( contents );
    QCOMPARE( entries.count(), 4 );

    QStringList mountPoints;
    for ( const auto& e : entries )
    {
        mountPoints.append( e.mountPoint );
    }
    mountPoints.sort();
    QCOMPARE( mountPoints,
              QStringList() << "/"
                            << "/dev1"
                            << "/dev2"
                            << "swap" );
}


QTEST_GUILESS_MAIN( ConfigTests )

#include "utils/moc-warnings.h"

#include "ConfigTests.moc"
