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

#include <CreateUserJob.h>

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>


CreateUserJob::CreateUserJob( const QString& userName, const QString& fullName, bool autologin )
    : Calamares::Job()
    , m_userName( userName )
    , m_fullName( fullName )
    , m_autologin( autologin )
{
}


QString
CreateUserJob::prettyName() const
{
    return tr( "Create user %1" ).arg( m_userName );
}


Calamares::JobResult
CreateUserJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir destDir( gs->value( "rootMountPoint" ).toString() );
    QFileInfo sudoersFi( destDir.absoluteFilePath( "etc/sudoers.d/10-installer" ) );

    if ( !sudoersFi.exists() || !sudoersFi.isWritable() )
        return Calamares::JobResult::error( tr( "Sudoers file is not writable." ) );

    QFile sudoersFile( sudoersFi.absoluteFilePath() );
    if (!sudoersFile.open( QIODevice::Append | QIODevice::Text ) )
        return Calamares::JobResult::error( tr( "Cannot open sudoers file for writing." ) );

    QTextStream sudoersOut( &sudoersFile );
    sudoersOut << QString( "%1 ALL=(ALL) ALL\n" ).arg( m_userName );

    if ( QProcess::execute( "chmod", { "440", sudoersFi.absoluteFilePath() } ) )
        return Calamares::JobResult::error( tr( "Cannot chmod sudoers file." ) );


    QString defaultGroups( "lp,video,network,storage,wheel,audio" );
    if ( m_autologin )
    {
        CalamaresUtils::chrootCall( { "groupadd", "autologin" } );
        defaultGroups.append( ",autologin" );
    }

    int ec = CalamaresUtils::chrootCall( { "useradd",
                                           "-m",
                                           "-s",
                                           "/bin/bash",
                                           "-g",
                                           "users",
                                           "-G",
                                           defaultGroups,
                                           m_userName } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot create user %1." )
                                                .arg( m_userName ),
                                            tr( "useradd terminated with error code %1." )
                                                .arg( ec ) );

    ec = CalamaresUtils::chrootCall( { "chfn", "-f", m_fullName, m_userName } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot set full name for user %1." )
                                                .arg( m_userName ),
                                            tr( "chfn terminated with error code %1." )
                                                .arg( ec ) );

    ec = CalamaresUtils::chrootCall( { "chown",
                                       "-R",
                                       QString( "%1:users" ).arg( m_userName ),
                                       QString( "/home/%1" ).arg( m_userName ) } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot set home directory ownership for user %1." )
                                                .arg( m_userName ),
                                            tr( "chown terminated with error code %1." )
                                                .arg( ec ) );

    return Calamares::JobResult::ok();
}
