/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ClearMountsJobTests.h"

#include "utils/Logger.h"

#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( ClearMountsJobTests )


/* Not exactly public API */
QStringList getPartitionsForDevice( const QString& deviceName );

QStringList
getPartitionsForDevice_other( const QString& deviceName )
{
    QProcess process;
    process.setProgram( "sh" );
    process.setArguments(
        { "-c",
          QString( "echo $(awk '{print $4}' /proc/partitions | sed -e '/name/d' -e '/^$/d' -e '/[1-9]/!d' | grep %1)" )
              .arg( deviceName ) } );
    process.start();
    process.waitForFinished();

    const QString partitions = process.readAllStandardOutput().trimmed();
    if ( partitions.isEmpty() )
    {
        return QStringList();
    }
    const QStringList partitionsList = partitions.simplified().split( ' ' );

    return partitionsList;
}


ClearMountsJobTests::ClearMountsJobTests()
{
    Logger::setupLogLevel( Logger::LOGDEBUG );
}

void
ClearMountsJobTests::testFindPartitions()
{
    QStringList partitions = getPartitionsForDevice( "sda" );
    QStringList other_part = getPartitionsForDevice_other( "sda" );

    cDebug() << "Initial implementation:" << Logger::DebugList( partitions );
    cDebug() << "Other implementation:" << Logger::DebugList( other_part );

    QCOMPARE( partitions, other_part );
}
