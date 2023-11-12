/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "core/PartUtils.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/System.h"
#include "utils/Yaml.h"

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

    const auto* gs = Calamares::JobQueue::instanceGlobalStorage();
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


QTEST_GUILESS_MAIN( ConfigTests )

#include "utils/moc-warnings.h"

#include "ConfigTests.moc"
