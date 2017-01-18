/*******************************************************************************
 * Copyright (c) 2016-2017, Kyle Robbertze (AIMS, South Africa)
 *
 * This project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * It is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this project. If not, see <http://www.gnu.org/licenses/>.
 *
 *    Description:  Module for installing select packages in the installed
 *                  system
 *
 *        Created:  09/12/2016 09:35:39
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), kyle@aims.ac.za
 *******************************************************************************/

#include "SetSourcesJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QFile>
#include <QTextStream>

SetSourcesJob::SetSourcesJob( const QString& source ) :
    Calamares::Job(),
    m_source( source )
{ }

QString
SetSourcesJob::prettyName() const
{
    return tr( "Add source %1" ).arg( m_source );
}

QString
SetSourcesJob::prettyDescription() const
{
    return tr( "Add <strong>%1</strong> to apt sources list" ).arg( m_source );
}

QString
SetSourcesJob::prettyStatusMessage() const
{
    return tr( "Adding %1 to sources list" ).arg( m_source );
}

Calamares::JobResult
SetSourcesJob::exec()
{
    QString rmp = Calamares::JobQueue::instance()->globalStorage()->value( "rootMountPoint" ).toString();
    QString sourceListPath = rmp + "/etc/apt/sources.list";
    QFile sourceList( sourceListPath );
    if ( !sourceList.exists() )
        return Calamares::JobResult::error( tr( "Unable to read sources.list" ),
                                            tr( "%1 does not exist" ).arg( sourceListPath ) );
    if ( sourceList.open( QIODevice::Append ) )
    {
        QTextStream stream( &sourceList );
        stream << m_source << "\n";
        stream.flush();
        sourceList.close();
    }
    else
    {
        return Calamares::JobResult::error( tr( "Unable to open sources.list" ),
                                            tr( "Cannot open %1 for appending" ).arg( sourceListPath ) );
    }
    int result = CalamaresUtils::System::instance()->
                 targetEnvCall( {"apt",
                                 "--allow-insecure-repositories", // File deb source on the installer is not signed
                                 "update"
                                } );
    if ( result )
        return Calamares::JobResult::error( tr( "Unable to update package cache" ),
                                            tr( "apt terminated with error code %1." ).arg( result ) );
    return Calamares::JobResult::ok();
}
