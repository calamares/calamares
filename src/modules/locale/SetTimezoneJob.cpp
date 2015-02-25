/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include <SetTimezoneJob.h>

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDir>
#include <QFileInfo>


SetTimezoneJob::SetTimezoneJob( const QString& region, const QString& zone )
    : Calamares::Job()
    , m_region( region )
    , m_zone( zone )
{
}


QString
SetTimezoneJob::prettyName() const
{
    return tr( "Set timezone to %1/%2" ).arg( m_region ).arg( m_zone );
}


Calamares::JobResult
SetTimezoneJob::exec()
{
    QString localtimeSlink( "/etc/localtime" );
    QString zoneinfoPath( "/usr/share/zoneinfo" );
    zoneinfoPath.append( QDir::separator() + m_region );
    zoneinfoPath.append( QDir::separator() + m_zone );

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QFileInfo zoneFile( gs->value( "rootMountPoint" ).toString() + zoneinfoPath );
    if ( !zoneFile.exists() || !zoneFile.isReadable() )
        return Calamares::JobResult::error( tr( "Cannot access selected timezone path." ),
                                            tr( "Bad path: %1" ).arg( zoneFile.absolutePath() ) );

    // Make sure /etc/localtime doesn't exist, otherwise symlinking will fail
    CalamaresUtils::chrootCall( { "rm",
                                  "-f",
                                  localtimeSlink
                                } );

    int ec = CalamaresUtils::chrootCall( { "ln",
                                           "-s",
                                           zoneinfoPath,
                                           localtimeSlink
                                         } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot set timezone." ),
                                            tr( "Link creation failed, target: %1; link name: %2" )
                                            .arg( zoneinfoPath )
                                            .arg( "/etc/localtime" ) );

    return Calamares::JobResult::ok();
}
