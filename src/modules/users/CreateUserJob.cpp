/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "CreateUserJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>


CreateUserJob::CreateUserJob( const QString& userName,
                              const QString& fullName,
                              bool autologin,
                              const QStringList& defaultGroups )
    : Calamares::Job()
    , m_userName( userName )
    , m_fullName( fullName )
    , m_autologin( autologin )
    , m_defaultGroups( defaultGroups )
{
}


QString
CreateUserJob::prettyName() const
{
    return tr( "Create user %1" ).arg( m_userName );
}


QString
CreateUserJob::prettyDescription() const
{
    return tr( "Create user <strong>%1</strong>." ).arg( m_userName );
}


QString
CreateUserJob::prettyStatusMessage() const
{
    return tr( "Creating user %1." ).arg( m_userName );
}


Calamares::JobResult
CreateUserJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir destDir( gs->value( "rootMountPoint" ).toString() );

    if ( gs->contains( "sudoersGroup" ) && !gs->value( "sudoersGroup" ).toString().isEmpty() )
    {
        cDebug() << "[CREATEUSER]: preparing sudoers";

        QFileInfo sudoersFi( destDir.absoluteFilePath( "etc/sudoers.d/10-installer" ) );

        if ( !sudoersFi.absoluteDir().exists() )
        {
            return Calamares::JobResult::error( tr( "Sudoers dir is not writable." ) );
        }

        QFile sudoersFile( sudoersFi.absoluteFilePath() );
        if ( !sudoersFile.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            return Calamares::JobResult::error( tr( "Cannot create sudoers file for writing." ) );
        }

        QString sudoersGroup = gs->value( "sudoersGroup" ).toString();

        QTextStream sudoersOut( &sudoersFile );
        sudoersOut << QString( "%%1 ALL=(ALL) ALL\n" ).arg( sudoersGroup );

        if ( QProcess::execute( "chmod", { "440", sudoersFi.absoluteFilePath() } ) )
            return Calamares::JobResult::error( tr( "Cannot chmod sudoers file." ) );
    }

    cDebug() << "[CREATEUSER]: preparing groups";

    QFileInfo groupsFi( destDir.absoluteFilePath( "etc/group" ) );
    QFile groupsFile( groupsFi.absoluteFilePath() );
    if ( !groupsFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return Calamares::JobResult::error( tr( "Cannot open groups file for reading." ) );
    }
    QString groupsData = QString::fromLocal8Bit( groupsFile.readAll() );
    QStringList groupsLines = groupsData.split( '\n' );
    for ( QStringList::iterator it = groupsLines.begin(); it != groupsLines.end(); ++it )
    {
        int indexOfFirstToDrop = it->indexOf( ':' );
        it->truncate( indexOfFirstToDrop );
    }

    foreach ( const QString& group, m_defaultGroups )
        if ( !groupsLines.contains( group ) )
            CalamaresUtils::System::instance()->targetEnvCall( { "groupadd", group } );

    QString defaultGroups = m_defaultGroups.join( ',' );
    if ( m_autologin )
    {
        QString autologinGroup;
        if ( gs->contains( "autologinGroup" ) && !gs->value( "autologinGroup" ).toString().isEmpty() )
        {
            autologinGroup = gs->value( "autologinGroup" ).toString();
            CalamaresUtils::System::instance()->targetEnvCall( { "groupadd", autologinGroup } );
            defaultGroups.append( QString( ",%1" ).arg( autologinGroup ) );
        }
    }

    // If we're looking to reuse the contents of an existing /home
    if ( gs->value( "reuseHome" ).toBool() )
    {
        QString shellFriendlyHome = "/home/" + m_userName;
        QDir existingHome( destDir.absolutePath() + shellFriendlyHome );
        if ( existingHome.exists() )
        {
            QString backupDirName = "dotfiles_backup_" + QDateTime::currentDateTime().toString( "yyyy-MM-dd_HH-mm-ss" );
            existingHome.mkdir( backupDirName );

            CalamaresUtils::System::instance()->targetEnvCall(
                { "sh", "-c", "mv -f " + shellFriendlyHome + "/.* " + shellFriendlyHome + "/" + backupDirName } );
        }
    }

    cDebug() << "[CREATEUSER]: creating user";

    QStringList useradd { "useradd", "-m", "-U" };
    QString shell = gs->value( "userShell" ).toString();
    if ( !shell.isEmpty() )
    {
        useradd << "-s" << shell;
    }
    useradd << "-c" << m_fullName;
    useradd << m_userName;

    auto commandResult = CalamaresUtils::System::instance()->targetEnvCommand( useradd );
    if ( commandResult.getExitCode() )
    {
        cError() << "useradd failed" << commandResult.getExitCode();
        return commandResult.explainProcess( useradd, std::chrono::seconds( 10 ) /* bogus timeout */ );
    }

    commandResult
        = CalamaresUtils::System::instance()->targetEnvCommand( { "usermod", "-aG", defaultGroups, m_userName } );
    if ( commandResult.getExitCode() )
    {
        cError() << "usermod failed" << commandResult.getExitCode();
        return commandResult.explainProcess( "usermod", std::chrono::seconds( 10 ) /* bogus timeout */ );
    }

    QString userGroup = QString( "%1:%2" ).arg( m_userName ).arg( m_userName );
    QString homeDir = QString( "/home/%1" ).arg( m_userName );
    commandResult = CalamaresUtils::System::instance()->targetEnvCommand( { "chown", "-R", userGroup, homeDir } );
    if ( commandResult.getExitCode() )
    {
        cError() << "chown failed" << commandResult.getExitCode();
        return commandResult.explainProcess( "chown", std::chrono::seconds( 10 ) /* bogus timeout */ );
    }

    return Calamares::JobResult::ok();
}
