/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Lisa Vitolo <shainer@chakralinux.org>
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

#include "SetAvatarJob.h"

#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "JobQueue.h"

#include <QFile>
#include <QDir>

SetAvatarJob::SetAvatarJob(const QString &avatarFile, const QString &destPath)
    : Calamares::Job()
    , m_avatarFile(avatarFile)
    , m_destPath(destPath)
{
}

QString SetAvatarJob::prettyName() const
{
    return tr( "Set avatar %1" ).arg( m_avatarFile );
}


QString
SetAvatarJob::prettyDescription() const
{
    return tr( "Set avatar from <strong>%1</strong>." ).arg( m_avatarFile );
}


QString
SetAvatarJob::prettyStatusMessage() const
{
    return tr( "Setting avatar from %1." ).arg( m_avatarFile );
}

Calamares::JobResult SetAvatarJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    if ( !gs || !gs->contains( "rootMountPoint" ) )
    {
        cLog() << "No rootMountPoint in global storage";
        return Calamares::JobResult::error( tr( "Internal Error" ) );
    }

    QString destDir = gs->value( "rootMountPoint" ).toString();
    if ( !QDir( destDir ).exists() )
    {
        cLog() << "rootMountPoint points to a dir which does not exist";
        return Calamares::JobResult::error( tr( "Internal Error" ) );
    }

    QString destination( destDir + m_destPath );
    QFile avatarFile( m_avatarFile );

    if (!avatarFile.exists()) {
        cLog() << "Avatar file does not exist";
        return Calamares::JobResult::error( tr("Avatar file does not exist") );
    }

    if (!avatarFile.copy(destination)) {
        cLog() << "Error copying:" << avatarFile.errorString();
        return Calamares::JobResult::error( tr("Error copying") );
    }

    return Calamares::JobResult::ok();
}
