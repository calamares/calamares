/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#include "Tests.h"

#include "PartitionSize.h"

using SizeUnit = CalamaresUtils::Partition::SizeUnit;
using PartitionSize = CalamaresUtils::Partition::PartitionSize;

Q_DECLARE_METATYPE( SizeUnit )

#include "utils/Logger.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( PartitionSizeTests )

PartitionSizeTests::PartitionSizeTests() {}

PartitionSizeTests::~PartitionSizeTests() {}

void
PartitionSizeTests::initTestCase()
{
}

void
PartitionSizeTests::testUnitComparison_data()
{
    QTest::addColumn< SizeUnit >( "u1" );
    QTest::addColumn< SizeUnit >( "u2" );
    QTest::addColumn< bool >( "comparable" );

    QTest::newRow( "nones" ) << SizeUnit::None << SizeUnit::None << false;
    QTest::newRow( "none+%" ) << SizeUnit::None << SizeUnit::Percent << false;
    QTest::newRow( "%+none" ) << SizeUnit::Percent << SizeUnit::None << false;
    QTest::newRow( "KiB+none" ) << SizeUnit::KiB << SizeUnit::None << false;
    QTest::newRow( "none+MiB" ) << SizeUnit::None << SizeUnit::MiB << false;

    QTest::newRow( "KiB+KiB" ) << SizeUnit::KiB << SizeUnit::KiB << true;
    QTest::newRow( "KiB+MiB" ) << SizeUnit::KiB << SizeUnit::MiB << true;
    QTest::newRow( "KiB+GiB" ) << SizeUnit::KiB << SizeUnit::GiB << true;
    QTest::newRow( "MiB+MiB" ) << SizeUnit::MiB << SizeUnit::MiB << true;
    QTest::newRow( "MiB+GiB" ) << SizeUnit::MiB << SizeUnit::GiB << true;
    QTest::newRow( "GiB+GiB" ) << SizeUnit::GiB << SizeUnit::GiB << true;

    QTest::newRow( "%+None" ) << SizeUnit::Percent << SizeUnit::None << false;
    QTest::newRow( "%+%" ) << SizeUnit::Percent << SizeUnit::Percent << true;
    QTest::newRow( "%+KiB" ) << SizeUnit::Percent << SizeUnit::KiB << false;
}


static bool
original_compare( SizeUnit m_unit, SizeUnit other_m_unit )
{
    if ( ( m_unit == SizeUnit::None || other_m_unit == SizeUnit::None )
         || ( m_unit == SizeUnit::Percent && other_m_unit != SizeUnit::Percent )
         || ( m_unit != SizeUnit::Percent && other_m_unit == SizeUnit::Percent ) )
    {
        return false;
    }
    return true;
}

void
PartitionSizeTests::testUnitComparison()
{
    QFETCH( SizeUnit, u1 );
    QFETCH( SizeUnit, u2 );
    QFETCH( bool, comparable );

    if ( comparable )
    {
        QVERIFY( PartitionSize::unitsComparable( u1, u2 ) );
        QVERIFY( PartitionSize::unitsComparable( u2, u1 ) );
    }
    else
    {
        QVERIFY( !PartitionSize::unitsComparable( u1, u2 ) );
        QVERIFY( !PartitionSize::unitsComparable( u2, u1 ) );
    }

    QCOMPARE( original_compare( u1, u2 ), PartitionSize::unitsComparable( u1, u2 ) );
}

/* Operator to make the table in testUnitNormalisation_data easier to write */
constexpr qint64 operator""_qi( unsigned long long m )
{
    return qint64( m );
}

void
PartitionSizeTests::testUnitNormalisation_data()
{
    QTest::addColumn< SizeUnit >( "u1" );
    QTest::addColumn< int >( "v" );
    QTest::addColumn< qint64 >( "bytes" );

    QTest::newRow( "none" ) << SizeUnit::None << 16 << -1_qi;
    QTest::newRow( "none" ) << SizeUnit::None << 0 << -1_qi;
    QTest::newRow( "none" ) << SizeUnit::None << -2 << -1_qi;

    QTest::newRow( "percent" ) << SizeUnit::Percent << 0 << -1_qi;
    QTest::newRow( "percent" ) << SizeUnit::Percent << 16 << -1_qi;
    QTest::newRow( "percent" ) << SizeUnit::Percent << -2 << -1_qi;

    QTest::newRow( "KiB" ) << SizeUnit::KiB << 0 << -1_qi;
    QTest::newRow( "KiB" ) << SizeUnit::KiB << 1 << 1024_qi;
    QTest::newRow( "KiB" ) << SizeUnit::KiB << 1000 << 1024000_qi;
    QTest::newRow( "KiB" ) << SizeUnit::KiB << 1024 << 1024 * 1024_qi;
    QTest::newRow( "KiB" ) << SizeUnit::KiB << -2 << -1_qi;

    QTest::newRow( "MiB" ) << SizeUnit::MiB << 0 << -1_qi;
    QTest::newRow( "MiB" ) << SizeUnit::MiB << 1 << 1024 * 1024_qi;
    QTest::newRow( "MiB" ) << SizeUnit::MiB << 1000 << 1024 * 1024000_qi;
    QTest::newRow( "MiB" ) << SizeUnit::MiB << 1024 << 1024 * 1024 * 1024_qi;
    QTest::newRow( "MiB" ) << SizeUnit::MiB << -2 << -1_qi;

    QTest::newRow( "GiB" ) << SizeUnit::GiB << 0 << -1_qi;
    QTest::newRow( "GiB" ) << SizeUnit::GiB << 1 << 1024_qi * 1024 * 1024_qi;
    // This one overflows 32-bits, which is why we want 64-bits for the whole table
    QTest::newRow( "GiB" ) << SizeUnit::GiB << 2 << 2048_qi * 1024 * 1024_qi;
}

void
PartitionSizeTests::testUnitNormalisation()
{
    QFETCH( SizeUnit, u1 );
    QFETCH( int, v );
    QFETCH( qint64, bytes );

    QCOMPARE( PartitionSize( v, u1 ).toBytes(), bytes );
}
