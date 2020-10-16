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

#include "utils/Logger.h"

#include <kpmcore/core/partitiontable.h>

#include <QtTest/QtTest>

class KPMTests : public QObject
{
    Q_OBJECT
public:
    KPMTests();
    ~KPMTests() override;
private Q_SLOTS:
    void initTestCase();

    void testFlagNames();
};

KPMTests::KPMTests() {}

KPMTests::~KPMTests() {}

void
KPMTests::initTestCase()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
KPMTests::testFlagNames()
{
    int f = 1;
    QStringList names;
    QString s;
    while ( !( s = PartitionTable::flagName( static_cast< PartitionTable::Flag >( f ) ) ).isEmpty() )
    {
        cDebug() << f << s;
        names.append( s );

        f <<= 1;
    }

    QCOMPARE( PartitionTable::flagName( static_cast< PartitionTable::Flag >( 1 ) ), QStringLiteral( "boot" ) );

#ifdef WITH_KPMCORE4API
    // KPMCore 4 unifies the flags and handles them internally
    QCOMPARE( PartitionTable::flagName( PartitionTable::Flag::Boot ), QStringLiteral( "boot" ) );
    QVERIFY( names.contains( QStringLiteral( "boot" ) ) );
    QVERIFY( !names.contains( QStringLiteral( "esp" ) ) );
#else
    // KPMCore 3 has separate flags
    QCOMPARE( PartitionTable::flagName( PartitionTable::FlagBoot ), QStringLiteral( "boot" ) );
    QCOMPARE( PartitionTable::flagName( PartitionTable::FlagEsp ), QStringLiteral( "esp" ) );
    QVERIFY( names.contains( QStringLiteral( "boot" ) ) );
    QVERIFY( names.contains( QStringLiteral( "esp" ) ) );
#endif
}


QTEST_GUILESS_MAIN( KPMTests )

#include "utils/moc-warnings.h"

#include "KPMTests.moc"
