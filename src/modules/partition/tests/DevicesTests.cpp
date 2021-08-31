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

#if defined( WITH_KPMCORE4API )
    cDebug() << "Getting devices via KPMCore";
    CoreBackend* backend = CoreBackendManager::self()->backend();
    DeviceList devices = backend->scanDevices( /* not includeReadOnly, not includeLoopback */ ScanFlag( 0 ) );
    cDebug() << Logger::SubEntry << "Done getting devices.";
#else
    cWarning() << "Test skipped; use KPMCore4";
#endif
}

void
DevicesTests::testPartUtilScanDevices()
{
    Logger::setupLogLevel( Logger::LOGVERBOSE );

    cDebug() << "Getting devices via PartUtils";
    auto l = PartUtils::getDevices();
    cDebug() << Logger::SubEntry << "Done getting devices.";

    QVERIFY( l.count() > 0 );
}
