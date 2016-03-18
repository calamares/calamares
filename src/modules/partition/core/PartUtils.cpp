/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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

#include "PartUtils.h"

#include "PartitionCoreModule.h"

#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"

#include <kpmcore/core/partition.h>

#include <utils/Logger.h>
#include <JobQueue.h>
#include <GlobalStorage.h>

#include <QProcess>

namespace PartUtils
{

bool
canBeReplaced( Partition* candidate )
{
    bool ok = false;
    double requiredStorageGB = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "requiredStorageGB" )
                                    .toDouble( &ok );

    qint64 availableStorageB = candidate->capacity();
    qint64 requiredStorageB = ( requiredStorageGB + 0.5 ) * 1024 * 1024 * 1024;
    cDebug() << "Required  storage B:" << requiredStorageB
             << QString( "(%1GB)" ).arg( requiredStorageB / 1024 / 1024 / 1024 );
    cDebug() << "Available storage B:" << availableStorageB
             << QString( "(%1GB)" ).arg( availableStorageB / 1024 / 1024 / 1024 );

    if ( ok &&
         availableStorageB > requiredStorageB )
    {
        cDebug() << "Partition" << candidate->partitionPath() << "authorized for replace install.";

        return true;
    }
    return false;
}


bool
canBeResized( Partition* candidate )
{
    if ( !candidate->fileSystem().supportGrow() ||
         !candidate->fileSystem().supportShrink() )
        return false;

    if ( KPMHelpers::isPartitionFreeSpace( candidate ) )
        return false;

    if ( candidate->roles().has( PartitionRole::Primary ) )
    {
        PartitionTable* table = dynamic_cast< PartitionTable* >( candidate->parent() );
        if ( !table )
            return false;

        if ( table->numPrimaries() >= table->maxPrimaries() )
            return false;
    }

    bool ok = false;
    double requiredStorageGB = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "requiredStorageGB" )
                                    .toDouble( &ok );

    qint64 availableStorageB = candidate->available();

    // We require a little more for partitioning overhead and swap file
    // TODO: maybe make this configurable?
    qint64 requiredStorageB = ( requiredStorageGB + 0.5 + 2.0 ) * 1024 * 1024 * 1024;
    cDebug() << "Required  storage B:" << requiredStorageB
             << QString( "(%1GB)" ).arg( requiredStorageB / 1024 / 1024 / 1024 );
    cDebug() << "Available storage B:" << availableStorageB
             << QString( "(%1GB)" ).arg( availableStorageB / 1024 / 1024 / 1024 );

    if ( ok &&
         availableStorageB > requiredStorageB )
    {
        cDebug() << "Partition" << candidate->partitionPath() << "authorized for resize + autopartition install.";

        return true;
    }
    return false;
}


bool
canBeResized( PartitionCoreModule* core, const QString& partitionPath )
{
    //FIXME: check for max partitions count on DOS MBR
    cDebug() << "checking if" << partitionPath << "can be resized.";
    QString partitionWithOs = partitionPath;
    if ( partitionWithOs.startsWith( "/dev/" ) )
    {
        cDebug() << partitionWithOs << "seems like a good path";
        bool canResize = false;
        DeviceModel* dm = core->deviceModel();
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            Partition* candidate = KPMHelpers::findPartitionByPath( { dev }, partitionWithOs );
            if ( candidate )
            {
                cDebug() << "found Partition* for" << partitionWithOs;
                return canBeResized( candidate );
            }
        }
    }

    cDebug() << "Partition" << partitionWithOs << "CANNOT BE RESIZED FOR AUTOINSTALL.";
    return false;
}


OsproberEntryList
runOsprober( PartitionCoreModule* core )
{
    QString osproberOutput;
    QProcess osprober;
    osprober.setProgram( "os-prober" );
    osprober.setProcessChannelMode( QProcess::SeparateChannels );
    osprober.start();
    if ( !osprober.waitForStarted() )
    {
        cDebug() << "ERROR: os-prober cannot start.";
    }
    else if ( !osprober.waitForFinished( 60000 ) )
    {
        cDebug() << "ERROR: os-prober timed out.";
    }
    else
    {
        osproberOutput.append(
            QString::fromLocal8Bit(
                osprober.readAllStandardOutput() ).trimmed() );
    }

    QString osProberReport( "Osprober lines, clean:\n" );
    QStringList osproberCleanLines;
    OsproberEntryList osproberEntries;
    foreach ( const QString& line, osproberOutput.split( '\n' ) )
    {
        if ( !line.simplified().isEmpty() )
        {
            QStringList lineColumns = line.split( ':' );
            QString prettyName;
            if ( !lineColumns.value( 1 ).simplified().isEmpty() )
                prettyName = lineColumns.value( 1 ).simplified();
            else if ( !lineColumns.value( 2 ).simplified().isEmpty() )
                prettyName = lineColumns.value( 2 ).simplified();

            QString path = lineColumns.value( 0 ).simplified();
            if ( !path.startsWith( "/dev/" ) ) //basic sanity check
                continue;

            osproberEntries.append( { prettyName,
                                      path,
                                      canBeResized( core, path ),
                                      lineColumns } );
            osproberCleanLines.append( line );
        }
    }
    osProberReport.append( osproberCleanLines.join( '\n' ) );
    cDebug() << osProberReport;

    Calamares::JobQueue::instance()->globalStorage()->insert( "osproberLines", osproberCleanLines );

    return osproberEntries;
}


}
