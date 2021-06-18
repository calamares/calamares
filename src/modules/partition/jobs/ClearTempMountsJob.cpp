/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ClearTempMountsJob.h"

#include "utils/Logger.h"
#include "utils/String.h"

#include <kpmcore/util/report.h>

#include <QFile>
#include <QProcess>
#include <QStringList>

#include <algorithm>

ClearTempMountsJob::ClearTempMountsJob()
    : Calamares::Job()
{
}


QString
ClearTempMountsJob::prettyName() const
{
    return tr( "Clear all temporary mounts." );
}


QString
ClearTempMountsJob::prettyStatusMessage() const
{
    return tr( "Clearing all temporary mounts." );
}


Calamares::JobResult
ClearTempMountsJob::exec()
{
    Logger::Once o;
    // Fetch a list of current mounts to Calamares temporary directories.
    QList< QPair< QString, QString > > lst;
    QFile mtab( "/etc/mtab" );
    if ( !mtab.open( QFile::ReadOnly | QFile::Text ) )
    {
        return Calamares::JobResult::error( tr( "Cannot get list of temporary mounts." ) );
    }

    cVerbose() << o << "Opened mtab. Lines:";
    QTextStream in( &mtab );
    QString lineIn = in.readLine();
    while ( !lineIn.isNull() )
    {
        QStringList line = lineIn.split( ' ', SplitSkipEmptyParts );
        cVerbose() << o << line.join( ' ' );
        QString device = line.at( 0 );
        QString mountPoint = line.at( 1 );
        if ( mountPoint.startsWith( "/tmp/calamares-" ) )
        {
            lst.append( qMakePair( device, mountPoint ) );
        }
        lineIn = in.readLine();
    }

    if ( lst.empty() )
    {
        return Calamares::JobResult::ok();
    }

    std::sort(
        lst.begin(), lst.end(), []( const QPair< QString, QString >& a, const QPair< QString, QString >& b ) -> bool {
            return a.first > b.first;
        } );

    QStringList goodNews;
    QProcess process;

    for ( const auto& line : qAsConst( lst ) )
    {
        QString partPath = line.second;
        cDebug() << o << "Will try to umount path" << partPath;
        process.start( "umount", { "-lv", partPath } );
        process.waitForFinished();
        if ( process.exitCode() == 0 )
        {
            goodNews.append( QString( "Successfully unmounted %1." ).arg( partPath ) );
        }
    }

    Calamares::JobResult ok = Calamares::JobResult::ok();
    ok.setMessage( tr( "Cleared all temporary mounts." ) );
    ok.setDetails( goodNews.join( "\n" ) );

    cDebug() << o << "ClearTempMountsJob finished. Here's what was done:\n" << Logger::DebugList( goodNews );

    return ok;
}
