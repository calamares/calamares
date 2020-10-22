/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "MiscJobs.h"

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Permissions.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

SetupSudoJob::SetupSudoJob( const QString& group )
    : m_sudoGroup( group )
{
}

QString
SetupSudoJob::prettyName() const
{
    return tr( "Configure <pre>sudo</pre> users." );
}

Calamares::JobResult
SetupSudoJob::exec()
{
    if ( m_sudoGroup.isEmpty() )
    {
        return Calamares::JobResult::ok();
    }

    QString sudoersLine = QString( "%%1 ALL=(ALL) ALL\n" ).arg( m_sudoGroup );
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

    return Calamares::JobResult::ok();
}

STATICTEST QStringList
groupsInTargetSystem()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir targetRoot( gs->value( "rootMountPoint" ).toString() );

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

/** @brief Create groups in target system as needed
 *
 * Given a list of groups that already exist, @p availableGroups,
 * go through the @p wantedGroups and create each of them. Groups that
 * fail, or which should have already been there, are added to
 * @p missingGroups by name.
 */
static bool
ensureGroupsExistInTarget( const QList< GroupDescription >& wantedGroups,
                           const QStringList& availableGroups,
                           QStringList& missingGroups )
{
    int failureCount = 0;

    for ( const auto& group : wantedGroups )
    {
        int groupaddResult = 0;
        if ( group.isValid() && !availableGroups.contains( group.name() ) )
        {
            if ( group.mustAlreadyExist() )
            {
                // Should have been there already: don't create it
                missingGroups.append( group.name() );
                continue;
            }

#ifdef __FreeBSD__
            groupaddResult
                = CalamaresUtils::System::instance()->targetEnvCall( { "pw", "groupadd", "-n", group.name() } );
#else
            groupaddResult = CalamaresUtils::System::instance()->targetEnvCall( { "groupadd", group.name() } );
#endif
            if ( groupaddResult )
            {
                failureCount++;
                missingGroups.append( group.name() + QChar( '*' ) );
            }
        }
    }
    if ( !missingGroups.isEmpty() )
    {
        cWarning() << "Missing groups in target system (* for groupadd failure):" << Logger::DebugList( missingGroups );
    }
    return failureCount == 0;
}

SetupGroupsJob::SetupGroupsJob( const Config* config, const QString& autologinGroup )
    : m_autologinGroup( autologinGroup )
    , m_config( config )
{
}

QString
SetupGroupsJob::prettyName() const
{
    return tr( "Preparing groups." );
}

Calamares::JobResult
SetupGroupsJob::exec()
{
    const auto& defaultGroups = m_config->defaultGroups();
    QStringList availableGroups = groupsInTargetSystem();
    QStringList missingGroups;

    if ( !ensureGroupsExistInTarget( defaultGroups, availableGroups, missingGroups ) )
    {
        return Calamares::JobResult::error( tr( "Could not create groups in target system" ) );
    }
    if ( !missingGroups.isEmpty() )
    {
        return Calamares::JobResult::error(
            tr( "Could not create groups in target system" ),
            tr( "These groups are missing in the target system: %1" ).arg( missingGroups.join( ',' ) ) );
    }

    if ( m_config->doAutoLogin() && !m_config->autologinGroup().isEmpty() )
    {
        const QString autologinGroup = m_config->autologinGroup();
        (void)ensureGroupsExistInTarget(
            QList< GroupDescription >() << GroupDescription( autologinGroup ), availableGroups, missingGroups );
    }

    return Calamares::JobResult::ok();
}
