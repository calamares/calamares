/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Item.h"

#include "Settings.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include <QtTest/QtTest>

class PreserveFilesTests : public QObject
{
    Q_OBJECT
public:
    PreserveFilesTests();
    ~PreserveFilesTests() override {}

private Q_SLOTS:
    void initTestCase();

    /*
    void testOneUrl();
    void testUrls_data();
    void testUrls();

    void testBadConfigDoesNotResetUrls();
    */
    void testTrue();
};

PreserveFilesTests::PreserveFilesTests() {}

void
PreserveFilesTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "PreserveFiles test started.";

    // Ensure we have a system object, expect it to be a "bogus" one
    CalamaresUtils::System* system = CalamaresUtils::System::instance();
    QVERIFY( system );
    cDebug() << Logger::SubEntry << "System @" << Logger::Pointer( system );

    const auto* settings = Calamares::Settings::instance();
    if ( !settings )
    {
        (void)new Calamares::Settings( true );
    }
}

void
PreserveFilesTests::testTrue()
{
    QVERIFY( true );
}


QTEST_GUILESS_MAIN( PreserveFilesTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
