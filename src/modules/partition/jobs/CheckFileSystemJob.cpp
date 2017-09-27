/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "jobs/CheckFileSystemJob.h"

#include <utils/Logger.h>

// KPMcore
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/util/report.h>

#include <QThread>

CheckFileSystemJob::CheckFileSystemJob( Partition* partition )
    : PartitionJob( partition )
{}

QString
CheckFileSystemJob::prettyName() const
{
    QString path = partition()->partitionPath();
    return tr( "Checking file system on partition %1." ).arg( path );
}


QString
CheckFileSystemJob::prettyStatusMessage() const
{
    return prettyName();
}


Calamares::JobResult
CheckFileSystemJob::exec()
{
    FileSystem& fs = partition()->fileSystem();

    // if we cannot check, assume everything is fine
    if ( fs.supportCheck() != FileSystem::cmdSupportFileSystem )
        return Calamares::JobResult::ok();

    Report report( nullptr );
    bool ok = fs.check( report, partition()->partitionPath() );
    int retries = 0;
    const int MAX_RETRIES = 10;
    while ( !ok )
    {
        cDebug() << "Partition" << partition()->partitionPath()
                 << "might not be ready yet, retrying (" << ++retries
                 << "/" << MAX_RETRIES << ") ...";
        QThread::sleep( 2 /*seconds*/ );
        ok = fs.check( report, partition()->partitionPath() );

        if ( retries == MAX_RETRIES )
            break;
    }

    if ( !ok )
        return Calamares::JobResult::error(
                   tr( "The file system check on partition %1 failed." )
                   .arg( partition()->partitionPath() ),
                   report.toText()
               );

    return Calamares::JobResult::ok();
}
