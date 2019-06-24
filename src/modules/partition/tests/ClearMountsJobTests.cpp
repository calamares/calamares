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
    QStringList partitions;

    QFile dev_partitions( "/proc/partitions" );
    if ( dev_partitions.open( QFile::ReadOnly ) )
    {
        cDebug() << "Reading from" << dev_partitions.fileName();
        QTextStream in( &dev_partitions );
        (void) in.readLine();  // That's the header line, skip it
        while ( !in.atEnd() )
        {
            // The fourth column (index from 0, so index 3) is the name of the device;
            // keep it if it is followed by something.
            QStringList columns = in.readLine().split( ' ', QString::SkipEmptyParts );
            if ( ( columns.count() >= 4 ) && ( columns[3].startsWith( deviceName ) )  && ( columns[3] != deviceName ) )
            {
                partitions.append( columns[3] );
            }
        }
    }
    else
    {
        cDebug() << "Could not open" << dev_partitions.fileName();
    }

    return partitions;
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
