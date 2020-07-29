/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
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
