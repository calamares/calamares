/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "CreateUserJob.h"

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

STATICTEST QStringList
groupsInTargetSystem( const QDir& targetRoot )
{
    QFileInfo groupsFi( targetRoot.absoluteFilePath( "etc/group" ) );
    QFile groupsFile( groupsFi.absoluteFilePath() );
    if ( !groupsFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return QStringList();
    }
    QString groupsData = QString::fromLocal8Bit( groupsFile.readAll() );
    QStringList groupsLines = groupsData.split( '\n' );
    QStringList::iterator it = groupsLines.begin();
    while ( it != groupsLines.end() )
    {
        if ( it->startsWith( '#' ) )
        {
            it = groupsLines.erase( it );
            continue;
        }
        int indexOfFirstToDrop = it->indexOf( ':' );
        if ( indexOfFirstToDrop < 1 )
        {
            it = groupsLines.erase( it );
            continue;
        }
        it->truncate( indexOfFirstToDrop );
        ++it;
    }
    return groupsLines;
}

static void
ensureGroupsExistInTarget( const QStringList& wantedGroups, const QStringList& availableGroups )
{
    for ( const QString& group : wantedGroups )
    {
        if ( !availableGroups.contains( group ) )
        {
#ifdef __FreeBSD__
            CalamaresUtils::System::instance()->targetEnvCall( { "pw", "groupadd", "-n", group } );
#else
            CalamaresUtils::System::instance()->targetEnvCall( { "groupadd", group } );
#endif
        }
    }
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
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir destDir( gs->value( "rootMountPoint" ).toString() );

    if ( gs->contains( "sudoersGroup" ) && !gs->value( "sudoersGroup" ).toString().isEmpty() )
    {
        cDebug() << "[CREATEUSER]: preparing sudoers";

        QString sudoersLine = QString( "%%1 ALL=(ALL) ALL\n" ).arg( gs->value( "sudoersGroup" ).toString() );
        auto fileResult
            = CalamaresUtils::System::instance()->createTargetFile( QStringLiteral( "/etc/sudoers.d/10-installer" ),
                                                                    sudoersLine.toUtf8().constData(),
                                                                    CalamaresUtils::System::WriteMode::Overwrite );

        if ( fileResult )
        {
            if ( !CalamaresUtils::Permissions::apply( fileResult.path(), 0440 ) )
            {
                return Calamares::JobResult::error( tr( "Cannot chmod sudoers file." ) );
            }
        }
        else
        {
            return Calamares::JobResult::error( tr( "Cannot create sudoers file for writing." ) );
        }
    }

    cDebug() << "[CREATEUSER]: preparing groups";

    QStringList availableGroups = groupsInTargetSystem( destDir );
    QStringList groupsForThisUser = m_defaultGroups;
    if ( m_autologin && gs->contains( "autologinGroup" ) && !gs->value( "autologinGroup" ).toString().isEmpty() )
    {
        groupsForThisUser << gs->value( "autologinGroup" ).toString();
    }
    ensureGroupsExistInTarget( groupsForThisUser, availableGroups );

    // If we're looking to reuse the contents of an existing /home.
    // This GS setting comes from the **partitioning** module.
    if ( gs->value( "reuseHome" ).toBool() )
    {
        QString shellFriendlyHome = "/home/" + m_userName;
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

    auto useraddResult = createUser( m_userName, m_fullName, gs->value( "userShell" ).toString() );
    if ( !useraddResult )
    {
        return useraddResult;
    }

    auto usergroupsResult = setUserGroups( m_userName, groupsForThisUser );
    if ( !usergroupsResult )
    {
        return usergroupsResult;
    }

    QString userGroup = QString( "%1:%2" ).arg( m_userName ).arg( m_userName );
    QString homeDir = QString( "/home/%1" ).arg( m_userName );
    auto commandResult = CalamaresUtils::System::instance()->targetEnvCommand( { "chown", "-R", userGroup, homeDir } );
    if ( commandResult.getExitCode() )
    {
        cError() << "chown failed" << commandResult.getExitCode();
        return commandResult.explainProcess( "chown", std::chrono::seconds( 10 ) /* bogus timeout */ );
    }

    return Calamares::JobResult::ok();
}
