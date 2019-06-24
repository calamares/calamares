/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "ClearMountsJobTests.h"

#include "utils/Logger.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( ClearMountsJobTests )


/* Not exactly public API */
QStringList
getPartitionsForDevice( const QString& deviceName );

QStringList
getPartitionsForDevice_other(const QString& deviceName)
{
    QProcess process;
    process.setProgram( "sh" );
    process.setArguments( {
                              "-c",
                              QString( "echo $(awk '{print $4}' /proc/partitions | sed -e '/name/d' -e '/^$/d' -e '/[1-9]/!d' | grep %1)" )
                                      .arg( deviceName )
                          } );
    process.start();
    process.waitForFinished();

    const QString partitions = process.readAllStandardOutput();
    const QStringList partitionsList = partitions.simplified().split( ' ' );

    return partitionsList;
}


ClearMountsJobTests::ClearMountsJobTests()
{
    Logger::setupLogLevel(6);
}

void ClearMountsJobTests::testFindPartitions()
{
    QStringList partitions = getPartitionsForDevice( "sda" );
    QStringList other_part = getPartitionsForDevice_other( "sda" );

    cDebug() << "Initial implementation:" << Logger::DebugList( partitions );
    cDebug() << "Other implementation:" << Logger::DebugList( other_part );

    QCOMPARE( partitions, other_part );
}
