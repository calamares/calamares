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

#include <SetPasswordJob.h>

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDir>

#include <crypt.h>


SetPasswordJob::SetPasswordJob( const QString& userName, const QString& newPassword )
    : Calamares::Job()
    , m_userName( userName )
    , m_newPassword( newPassword )
{
}


QString
SetPasswordJob::prettyName() const
{
    return tr( "Set password for user %1" ).arg( m_userName );
}


QString
SetPasswordJob::prettyStatusMessage() const
{
    return tr( "Setting password for user %1." ).arg( m_userName );
}


Calamares::JobResult
SetPasswordJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir destDir( gs->value( "rootMountPoint" ).toString() );
    if ( !destDir.exists() )
        return Calamares::JobResult::error( tr( "Bad destination system path." ),
                                            tr( "rootMountPoint is %1" ).arg( destDir.absolutePath() ) );

    QString encrypted = QString::fromLatin1(
                            crypt( m_newPassword.toLatin1(),
                                   QString( "$6$%1$" )
                                .arg( m_userName )
                                .toLatin1() ) );

    int ec = CalamaresUtils::System::instance()->
                          targetEnvCall( { "usermod",
                                           "-p",
                                           encrypted,
                                           m_userName } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot set password for user %1." )
                                                .arg( m_userName ),
                                            tr( "usermod terminated with error code %1." )
                                                .arg( ec ) );

    return Calamares::JobResult::ok();
}
