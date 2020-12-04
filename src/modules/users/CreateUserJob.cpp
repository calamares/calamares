/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "CreateUserJob.h"

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Permissions.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QTextStream>


CreateUserJob::CreateUserJob( const Config* config )
    : Calamares::Job()
    , m_config( config )
{
}


QString
CreateUserJob::prettyName() const
{
    return tr( "Create user %1" ).arg( m_config->loginName() );
}


QString
CreateUserJob::prettyDescription() const
{
    return tr( "Create user <strong>%1</strong>." ).arg( m_config->loginName() );
}


QString
CreateUserJob::prettyStatusMessage() const
{
    return m_status.isEmpty() ? tr( "Creating user %1" ).arg( m_config->loginName() ) : m_status;
}

static Calamares::JobResult
createUser( const QString& loginName, const QString& fullName, const QString& shell )
{
    QStringList useraddCommand;
#ifdef __FreeBSD__
    useraddCommand << "pw"
                   << "useradd"
                   << "-n" << loginName << "-m"
                   << "-c" << fullName;
    if ( !shell.isEmpty() )
    {
        useraddCommand << "-s" << shell;
    }
#else
    useraddCommand << "useradd"
                   << "-m"
                   << "-U";
    if ( !shell.isEmpty() )
    {
        useraddCommand << "-s" << shell;
    }
    useraddCommand << "-c" << fullName;
    useraddCommand << loginName;
#endif

    auto commandResult = CalamaresUtils::System::instance()->targetEnvCommand( useraddCommand );
    if ( commandResult.getExitCode() )
    {
        cError() << "useradd failed" << commandResult.getExitCode();
        return commandResult.explainProcess( useraddCommand, std::chrono::seconds( 10 ) /* bogus timeout */ );
    }
    return Calamares::JobResult::ok();
}

static Calamares::JobResult
setUserGroups( const QString& loginName, const QStringList& groups )
{
    QStringList setgroupsCommand;
#ifdef __FreeBSD__
    setgroupsCommand << "pw"
                     << "usermod"
                     << "-n" << loginName << "-G" << groups.join( ',' );
#else
    setgroupsCommand << "usermod"
                     << "-aG" << groups.join( ',' ) << loginName;
#endif

    auto commandResult = CalamaresUtils::System::instance()->targetEnvCommand( setgroupsCommand );
    if ( commandResult.getExitCode() )
    {
        cError() << "usermod failed" << commandResult.getExitCode();
        return commandResult.explainProcess( setgroupsCommand, std::chrono::seconds( 10 ) /* bogus timeout */ );
    }
    return Calamares::JobResult::ok();
}


Calamares::JobResult
CreateUserJob::exec()
{
    QDir destDir;
    bool reuseHome = false;

    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        destDir = QDir( gs->value( "rootMountPoint" ).toString() );
        reuseHome = gs->value( "reuseHome" ).toBool();
    }

    // If we're looking to reuse the contents of an existing /home.
    // This GS setting comes from the **partitioning** module.
    if ( reuseHome )
    {
        m_status = tr( "Preserving home directory" );
        emit progress( 0.2 );
        QString shellFriendlyHome = "/home/" + m_config->loginName();
        QDir existingHome( destDir.absolutePath() + shellFriendlyHome );
        if ( existingHome.exists() )
        {
            QString backupDirName = "dotfiles_backup_" + QDateTime::currentDateTime().toString( "yyyy-MM-dd_HH-mm-ss" );
            existingHome.mkdir( backupDirName );

            // We need the extra `sh -c` here to ensure that we can expand the shell globs
            CalamaresUtils::System::instance()->targetEnvCall(
                { "sh", "-c", "mv -f " + shellFriendlyHome + "/.* " + shellFriendlyHome + "/" + backupDirName } );
        }
    }

    cDebug() << "[CREATEUSER]: creating user";

    m_status = tr( "Creating user %1" ).arg( m_config->loginName() );
    emit progress( 0.5 );
    auto useraddResult = createUser( m_config->loginName(), m_config->fullName(), m_config->userShell() );
    if ( !useraddResult )
    {
        return useraddResult;
    }

    m_status = tr( "Configuring user %1" ).arg( m_config->loginName() );
    emit progress( 0.8 );
    auto usergroupsResult = setUserGroups( m_config->loginName(), m_config->groupsForThisUser() );
    if ( !usergroupsResult )
    {
        return usergroupsResult;
    }

    m_status = tr( "Setting file permissions" );
    emit progress( 0.9 );
    QString userGroup = QString( "%1:%2" ).arg( m_config->loginName() ).arg( m_config->loginName() );
    QString homeDir = QString( "/home/%1" ).arg( m_config->loginName() );
    auto commandResult = CalamaresUtils::System::instance()->targetEnvCommand( { "chown", "-R", userGroup, homeDir } );
    if ( commandResult.getExitCode() )
    {
        cError() << "chown failed" << commandResult.getExitCode();
        return commandResult.explainProcess( "chown", std::chrono::seconds( 10 ) /* bogus timeout */ );
    }

    return Calamares::JobResult::ok();
}
