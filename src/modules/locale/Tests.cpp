/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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


#include "Tests.h"
#include "LocaleConfiguration.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( LocaleTests )


LocaleTests::LocaleTests()
{
}

LocaleTests::~LocaleTests()
{
}

void LocaleTests::initTestCase()
{
}

void LocaleTests::testEmptyLocaleConfiguration()
{
    LocaleConfiguration lc;

    QVERIFY( lc.isEmpty() );
    QCOMPARE( lc.toBcp47(), QString() );
}

void LocaleTests::testDefaultLocaleConfiguration()
{
    LocaleConfiguration lc( "en_US.UTF-8" );
    QVERIFY( !lc.isEmpty() );
    QCOMPARE( lc.toBcp47(), "en_US" );
}
