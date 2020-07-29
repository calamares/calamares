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
#include "CreateUserJob.h"

#include "utils/Logger.h"

#include <QDir>
#include <QtTest/QtTest>

// Implementation details
extern QStringList groupsInTargetSystem( const QDir& targetRoot );  // CreateUserJob
extern void setConfigurationDefaultGroups( const QVariantMap& map, QStringList& defaultGroups );

class CreateUserTests : public QObject
{
    Q_OBJECT
public:
    CreateUserTests();
    virtual ~CreateUserTests() {}

private Q_SLOTS:
    void initTestCase();

    void testReadGroup();
    void testDefaultGroups();
};

CreateUserTests::CreateUserTests() {}

void
CreateUserTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
    cDebug() << "Users test started.";
}

void
CreateUserTests::testReadGroup()
{
    QDir root( "/" );
    QVERIFY( root.exists() );

    // Get the groups in the host system
    QStringList groups = groupsInTargetSystem( root );
    QVERIFY( groups.count() > 2 );
#ifdef __FreeBSD__
    QVERIFY( groups.contains( QStringLiteral( "wheel" ) ) );
#else
    QVERIFY( groups.contains( QStringLiteral( "root" ) ) );
#endif
    QVERIFY( groups.contains( QStringLiteral( "sys" ) ) );

    for ( const QString& s : groups )
    {
        QVERIFY( !s.isEmpty() );
        QVERIFY( !s.contains( '#' ) );
    }
}

void
CreateUserTests::testDefaultGroups()
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


QTEST_GUILESS_MAIN( CreateUserTests )

#include "utils/moc-warnings.h"

#include "TestCreateUserJob.moc"
