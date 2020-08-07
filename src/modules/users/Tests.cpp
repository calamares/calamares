/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Config.h"

#include "utils/Logger.h"

#include <QtTest/QtTest>

// Implementation details
extern void setConfigurationDefaultGroups( const QVariantMap& map, QStringList& defaultGroups );
extern HostNameActions getHostNameActions( const QVariantMap& configurationMap );
extern bool addPasswordCheck( const QString& key, const QVariant& value, PasswordCheckList& passwordChecks );

/** @brief Test Config object methods and internals
 *
 */
class UserTests : public QObject
{
    Q_OBJECT
public:
    UserTests();
    virtual ~UserTests() {}

private Q_SLOTS:
    void initTestCase();

    void testDefaultGroups();
    void testHostActions_data();
    void testHostActions();
    void testPasswordChecks();
};

UserTests::UserTests() {}

void
UserTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Users test started.";
}

void
UserTests::testDefaultGroups()
{
    {
        QStringList groups;
        QVariantMap hweelGroup;
        QVERIFY( groups.isEmpty() );
        hweelGroup.insert( "defaultGroups", QStringList { "hweel" } );
        setConfigurationDefaultGroups( hweelGroup, groups );
        QCOMPARE( groups.count(), 1 );
        QVERIFY( groups.contains( "hweel" ) );
    }

    {
        QStringList desired { "wheel", "root", "operator" };
        QStringList groups;
        QVariantMap threeGroup;
        QVERIFY( groups.isEmpty() );
        threeGroup.insert( "defaultGroups", desired );
        setConfigurationDefaultGroups( threeGroup, groups );
        QCOMPARE( groups.count(), 3 );
        QVERIFY( !groups.contains( "hweel" ) );
        QCOMPARE( groups, desired );
    }

    {
        QStringList groups;
        QVariantMap explicitEmpty;
        QVERIFY( groups.isEmpty() );
        explicitEmpty.insert( "defaultGroups", QStringList() );
        setConfigurationDefaultGroups( explicitEmpty, groups );
        QCOMPARE( groups.count(), 0 );
    }

    {
        QStringList groups;
        QVariantMap missing;
        QVERIFY( groups.isEmpty() );
        setConfigurationDefaultGroups( missing, groups );
        QCOMPARE( groups.count(), 6 );  // because of fallback!
        QVERIFY( groups.contains( "lp" ) );
    }

    {
        QStringList groups;
        QVariantMap typeMismatch;
        QVERIFY( groups.isEmpty() );
        typeMismatch.insert( "defaultGroups", 1 );
        setConfigurationDefaultGroups( typeMismatch, groups );
        QCOMPARE( groups.count(), 6 );  // because of fallback!
        QVERIFY( groups.contains( "lp" ) );
    }
}

void
UserTests::testHostActions_data()
{
    QTest::addColumn< bool >( "set" );
    QTest::addColumn< QString >( "string" );
    QTest::addColumn< int >( "result" );

    QTest::newRow( "unset  " ) << false << QString() << int( HostNameAction::EtcHostname );
    QTest::newRow( "empty  " ) << true << QString() << int( HostNameAction::EtcHostname );
    QTest::newRow( "bad    " ) << true << QString( "derp" ) << int( HostNameAction::EtcHostname );
    QTest::newRow( "none   " ) << true << QString( "none" ) << int( HostNameAction::None );
    QTest::newRow( "systemd" ) << true << QString( "Hostnamed" ) << int( HostNameAction::SystemdHostname );
}

void
UserTests::testHostActions()
{
    QFETCH( bool, set );
    QFETCH( QString, string );
    QFETCH( int, result );

    QVariantMap m;
    if ( set )
    {
        m.insert( "setHostname", string );
    }
    QCOMPARE( getHostNameActions( m ), HostNameActions( result ) | HostNameAction::WriteEtcHosts );  // write bits default to true
    m.insert( "writeHostsFile", false );
    QCOMPARE( getHostNameActions( m ), HostNameActions( result ) );
    m.insert( "writeHostsFile", true );
    QCOMPARE( getHostNameActions( m ), HostNameActions( result ) | HostNameAction::WriteEtcHosts );
}

void
UserTests::testPasswordChecks()
{
    {
        PasswordCheckList l;
        QCOMPARE( l.length(), 0 );
        QVERIFY( !addPasswordCheck( "nonempty", QVariant(false), l ) );  // a silly setting
        QCOMPARE( l.length(), 0 );
        QVERIFY( addPasswordCheck( "nonempty", QVariant(true), l ) );
        QCOMPARE( l.length(), 1 );
    }
}


QTEST_GUILESS_MAIN( UserTests )

#include "utils/moc-warnings.h"

#include "Tests.moc"
