/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CreateUserJob.h"

#include "utils/Logger.h"

#include <QDir>
#include <QtTest/QtTest>

// Implementation details
extern QStringList groupsInTargetSystem( const QDir& targetRoot );  // CreateUserJob

class CreateUserTests : public QObject
{
    Q_OBJECT
public:
    CreateUserTests();
    ~CreateUserTests() override {}

private Q_SLOTS:
    void initTestCase();

    void testReadGroup();
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
    // openSUSE doesn't have "sys"
    // QVERIFY( groups.contains( QStringLiteral( "sys" ) ) );
    QVERIFY( groups.contains( QStringLiteral( "nogroup" ) ) );
    QVERIFY( groups.contains( QStringLiteral( "tty" ) ) );

    for ( const QString& s : groups )
    {
        QVERIFY( !s.isEmpty() );
        QVERIFY( !s.contains( '#' ) );
    }
}

QTEST_GUILESS_MAIN( CreateUserTests )

#include "utils/moc-warnings.h"

#include "TestCreateUserJob.moc"
