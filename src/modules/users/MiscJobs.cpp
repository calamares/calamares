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

SetupSudoJob::SetupSudoJob( const QString& group, Config::SudoStyle style )
    : m_sudoGroup( group )
    , m_sudoStyle( style )
{
}

QString
SetupSudoJob::prettyName() const
{
    return tr( "Configure <pre>sudo</pre> users." );
}

static QString
designatorForStyle( Config::SudoStyle style )
{
    switch ( style )
    {
    case Config::SudoStyle::UserOnly:
        return QStringLiteral( "(ALL)" );
    case Config::SudoStyle::UserAndGroup:
        return QStringLiteral( "(ALL:ALL)" );
    }
    __builtin_unreachable();
}

Calamares::JobResult
SetupSudoJob::exec()
{
    if ( m_sudoGroup.isEmpty() )
    {
        cDebug() << "Skipping sudo 10-installer because the sudoGroup is empty.";
        return Calamares::JobResult::ok();
    }

    // One % for the sudo format, keep it outside of the string to avoid accidental replacement
    QString sudoersLine
        = QChar( '%' ) + QString( "%1 ALL=%2 ALL\n" ).arg( m_sudoGroup, designatorForStyle( m_sudoStyle ) );
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
    if ( !gs )
    {
        return QStringList();
    }
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
        if ( group.isValid() && !availableGroups.contains( group.name() ) )
        {
            if ( group.mustAlreadyExist() )
            {
                // Should have been there already: don't create it
                missingGroups.append( group.name() );
                continue;
            }

            QStringList cmd;
#ifdef __FreeBSD__
            if ( group.isSystemGroup() )
            {
                cWarning() << "Ignoring must-be-a-system group for" << group.name() << "on FreeBSD";
            }
            cmd = QStringList { "pw", "groupadd", "-n", group.name() };
#else
            cmd << QStringLiteral( "groupadd" );
            if ( group.isSystemGroup() )
            {
                cmd << "--system";
            }
            cmd << group.name();
#endif
            if ( CalamaresUtils::System::instance()->targetEnvCall( cmd ) )
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

SetupGroupsJob::SetupGroupsJob( const Config* config )
    : m_config( config )
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

    if ( m_config->doAutoLogin() && !m_config->autoLoginGroup().isEmpty() )
    {
        const QString autoLoginGroup = m_config->autoLoginGroup();
        (void)ensureGroupsExistInTarget(
            QList< GroupDescription >() << GroupDescription( autoLoginGroup ), availableGroups, missingGroups );
    }

    return Calamares::JobResult::ok();
}
