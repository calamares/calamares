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
    return tr( "Creating user %1." ).arg( m_config->loginName() );
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
ensureGroupsExistInTarget( const QList< GroupDescription >& wantedGroups, const QStringList& availableGroups )
{
    for ( const auto& group : wantedGroups )
    {
        if ( group.isValid() && !availableGroups.contains( group.name() ) )
        {
#ifdef __FreeBSD__
            CalamaresUtils::System::instance()->targetEnvCall( { "pw", "groupadd", "-n", group.name() } );
#else
            CalamaresUtils::System::instance()->targetEnvCall( { "groupadd", group.name() } );
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

    // loginName(), fullName().isEmpty() ? loginName() : fullName(), doAutoLogin(), groupNames );
    const auto& defaultGroups = m_config->defaultGroups();
    QStringList groupsForThisUser = std::accumulate(
        defaultGroups.begin(),
        defaultGroups.end(),
        QStringList(),
        []( const QStringList& l, const GroupDescription& g ) { return QStringList( l ) << g.name(); } );

    QStringList availableGroups = groupsInTargetSystem( destDir );
    ensureGroupsExistInTarget( defaultGroups, availableGroups );

    if ( m_config->doAutoLogin() && !m_config->autologinGroup().isEmpty() )
    {
        const QString autologinGroup = m_config->autologinGroup();
        groupsForThisUser << autologinGroup;
        ensureGroupsExistInTarget( QList< GroupDescription >() << GroupDescription( autologinGroup ), availableGroups );
    }

    // If we're looking to reuse the contents of an existing /home.
    // This GS setting comes from the **partitioning** module.
    if ( gs->value( "reuseHome" ).toBool() )
    {
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

    auto useraddResult = createUser( m_config->loginName(), m_config->fullName(), m_config->userShell() );
    if ( !useraddResult )
    {
        return useraddResult;
    }

    auto usergroupsResult = setUserGroups( m_config->loginName(), groupsForThisUser );
    if ( !usergroupsResult )
    {
        return usergroupsResult;
    }

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
