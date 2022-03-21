/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/DeviceList.h"

#include "partition/KPMManager.h"
#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>

#include <QObject>
#include <QtTest/QtTest>

#include <memory>

#include <unistd.h>

class DevicesTests : public QObject
{
    Q_OBJECT

public:
    DevicesTests();

private Q_SLOTS:
    void testKPMScanDevices();
    void testPartUtilScanDevices();

private:
    std::unique_ptr< CalamaresUtils::Partition::KPMManager > m_d;
    bool m_isRoot = false;
};

DevicesTests::DevicesTests()
    : m_d( std::make_unique< CalamaresUtils::Partition::KPMManager >() )
    , m_isRoot( geteuid() == 0 )
{
}

void
DevicesTests::testKPMScanDevices()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    cDebug() << "Getting devices via KPMCore";
    CoreBackend* backend = CoreBackendManager::self()->backend();
    QVERIFY( backend );
    auto devices = backend->scanDevices( ScanFlag( ~0 ) );  // These flags try to get "all"
    cDebug() << Logger::SubEntry << "Done getting devices.";

    if ( !m_isRoot )
    {
        QEXPECT_FAIL( "", "Test invalid when not root", Continue );
    }
    QVERIFY( devices.count() > 0 );
}

void
DevicesTests::testPartUtilScanDevices()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    cDebug() << "Getting devices via PartUtils";
    auto devices = PartUtils::getDevices();
    cDebug() << Logger::SubEntry << "Done getting devices.";

    if ( !m_isRoot )
    {
        QEXPECT_FAIL( "", "Test invalid when not root", Continue );
    }
    QVERIFY( devices.count() > 0 );
}

QTEST_GUILESS_MAIN( DevicesTests )

#include "utils/moc-warnings.h"

#include "DevicesTests.moc"
