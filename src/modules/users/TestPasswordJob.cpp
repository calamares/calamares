/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SetPasswordJob.h"

#include <QtTest/QtTest>

class PasswordTests : public QObject
{
    Q_OBJECT
public:
    PasswordTests();
    ~PasswordTests() override;

private Q_SLOTS:
    void initTestCase();
    void testSalt();
};

PasswordTests::PasswordTests() {}

PasswordTests::~PasswordTests() {}

void
PasswordTests::initTestCase()
{
}

void
PasswordTests::testSalt()
{
    QString s = SetPasswordJob::make_salt( 8 );
    QCOMPARE( s.length(), 4 + 8 );  // 8 salt chars, plus $6$, plus trailing $
    QVERIFY( s.startsWith( "$6$" ) );
    QVERIFY( s.endsWith( '$' ) );
    qDebug() << "Obtained salt" << s;

    s = SetPasswordJob::make_salt( 11 );
    QCOMPARE( s.length(), 4 + 11 );
    QVERIFY( s.startsWith( "$6$" ) );
    QVERIFY( s.endsWith( '$' ) );
    qDebug() << "Obtained salt" << s;
}

QTEST_GUILESS_MAIN( PasswordTests )

#include "utils/moc-warnings.h"

#include "TestPasswordJob.moc"
