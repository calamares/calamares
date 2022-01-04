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
#include "utils/NamedEnum.h"
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

    void testItems_data();
    void testItems();
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
PreserveFilesTests::testItems_data()
{
    QTest::addColumn< QString >( "filename" );
    QTest::addColumn< bool >( "ok" );
    QTest::addColumn< int >( "type_i" );

    QTest::newRow( "log     " ) << QString( "1a-log.conf" ) << true << smash( ItemType::Log );
    QTest::newRow( "config  " ) << QString( "1b-config.conf" ) << true << smash( ItemType::Config );
    QTest::newRow( "src     " ) << QString( "1c-src.conf" ) << true << smash( ItemType::Path );
    QTest::newRow( "filename" ) << QString( "1d-filename.conf" ) << true << smash( ItemType::Path );
    QTest::newRow( "empty   " ) << QString( "1e-empty.conf" ) << false << smash( ItemType::None );
    QTest::newRow( "bad     " ) << QString( "1f-bad.conf" ) << false << smash( ItemType::None );
}

void
PreserveFilesTests::testItems()
{
    QFETCH( QString, filename );
    QFETCH( bool, ok );
    QFETCH( int, type_i );

    QFile fi( QString( "%1/tests/%2" ).arg( BUILD_AS_TEST, filename ) );
    QVERIFY( fi.exists() );

    bool config_file_ok = false;
    const auto map = CalamaresUtils::loadYaml( fi, &config_file_ok );
    QVERIFY( config_file_ok );

    CalamaresUtils::Permissions perm( QStringLiteral( "adridg:adridg:0750" ) );
    auto i = Item::fromVariant( map[ "item" ], perm );
    QCOMPARE( bool( i ), ok );
    QCOMPARE( smash( i.type() ), type_i );
}

QTEST_GUILESS_MAIN( PreserveFilesTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
