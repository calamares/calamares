/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/System.h"

#include "core/PartUtils.h"

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
};

ConfigTests::ConfigTests() = default;

void
ConfigTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );

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
    Logger::setupLogLevel( Logger::LOGVERBOSE );

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

QTEST_GUILESS_MAIN( ConfigTests )

#include "utils/moc-warnings.h"

#include "ConfigTests.moc"
