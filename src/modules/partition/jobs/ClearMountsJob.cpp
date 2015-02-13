/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "ClearMountsJob.h"

#include <core/device.h>
#include <core/partition.h>
#include <core/PartitionInfo.h>
#include <core/PartitionIterator.h>
#include <util/report.h>
#include <utils/Logger.h>

#include <QProcess>
#include <QStringList>


ClearMountsJob::ClearMountsJob( Device* device )
    : Calamares::Job()
    , m_device( device )
{
}


QString
ClearMountsJob::prettyName() const
{
    return tr( "Clear mounts for partitioning operations on %1" )
            .arg( m_device->deviceNode() );
}


Calamares::JobResult
ClearMountsJob::exec()
{
    QStringList goodNews;

    QProcess process;
    process.setProgram( "sh" );
    process.setArguments( {
                              "-c",
                              QString( "echo $(awk '{print $4}' /proc/partitions | sed -e '/name/d' -e '/^$/d' -e '/[1-9]/!d' | grep %1)" )
                                      .arg( m_device->deviceNode().split( '/' ).last() )
                          } );
    process.start();
    process.waitForFinished();

    QString partitions = process.readAllStandardOutput();
    QStringList partitionsList = partitions.simplified().split( ' ' );

    foreach ( QString p, partitionsList )
    {
        QString partPath = QString( "/dev/%1" ).arg( p );

        process.start( "umount", { partPath } );
        process.waitForFinished();
        if ( process.exitCode() == 0 )
            goodNews.append( QString( "Successfully unmounted %1." ).arg( partPath ) );

        process.start( "swapoff", { partPath } );
        process.waitForFinished();
        if ( process.exitCode() == 0 )
            goodNews.append( QString( "Successfully disabled swap %1." ).arg( partPath ) );
    }

    Calamares::JobResult ok = Calamares::JobResult::ok();
    ok.setMessage( tr( "Cleared all mounts for %1" )
                        .arg( m_device->deviceNode() ) );
    ok.setDetails( goodNews.join( "\n" ) );

    return ok;
}
