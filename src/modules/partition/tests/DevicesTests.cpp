/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/DeviceList.h"

#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>

#include <QObject>
#include <QtTest/QtTest>

class DevicesTests : public QObject
{
    Q_OBJECT

public:
    DevicesTests();

private Q_SLOTS:
    void testKPMScanDevices();
    void testPartUtilScanDevices();
};

DevicesTests::DevicesTests() {}

void
DevicesTests::testKPMScanDevices()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    cDebug() << "Getting devices via KPMCore";
    CoreBackend* backend = CoreBackendManager::self()->backend();
    QVERIFY( backend );
    auto devices = backend->scanDevices(); // Whatever the default is /* not includeReadOnly, not includeLoopback */ ScanFlag( 0 ) );
    cDebug() << Logger::SubEntry << "Done getting devices.";

    QVERIFY( devices.count() > 0 );
}

void
DevicesTests::testPartUtilScanDevices()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    cDebug() << "Getting devices via PartUtils";
    auto devices = PartUtils::getDevices();
    cDebug() << Logger::SubEntry << "Done getting devices.";

    QVERIFY( devices.count() > 0 );
}

QTEST_GUILESS_MAIN( DevicesTests )

#include "utils/moc-warnings.h"

#include "DevicesTests.moc"
