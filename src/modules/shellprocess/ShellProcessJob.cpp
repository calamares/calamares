/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
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

#include "ShellProcessJob.h"

#include "CommandList.h"

#include <QProcess>
#include <QDateTime>
#include <QThread>

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/CalamaresUtils.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

class CommandList;

ShellProcessJob::ShellProcessJob( QObject* parent )
    : Calamares::CppJob( parent )
    , m_commands( nullptr )
    , m_dontChroot( false )
{
}


ShellProcessJob::~ShellProcessJob()
{
    delete m_commands;
    m_commands = nullptr;  // TODO: UniquePtr
}


QString
ShellProcessJob::prettyName() const
{
    return tr( "Shell Processes Job" );
}


Calamares::JobResult
ShellProcessJob::exec()
{
    using CalamaresUtils::System;
    System::RunLocation location = m_dontChroot ? System::RunLocation::RunInHost : System::RunLocation::RunInTarget;

    if ( ! m_commands || m_commands->isEmpty() )
    {
        cDebug() << "WARNING: No commands to execute";
        return Calamares::JobResult::ok();
    }

    /* Figure out the replacement for @@ROOT@@ */
    QString root = QStringLiteral( "/" );
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( location == System::RunLocation::RunInTarget )
    {
         if ( !gs || !gs->contains( "rootMountPoint" ) )
         {
             cDebug() << "ERROR: No rootMountPoint defined.";
             return Calamares::JobResult::error( tr( "Could not run command." ),
                                                 tr( "No rootMountPoint is defined, so command cannot be run in the target environment." ) );
         }
         root = gs->value( "rootMountPoint" ).toString();
    }

    for ( CommandList::const_iterator i = m_commands->cbegin(); i != m_commands->cend(); ++i )
    {
        QString processed_cmd = *i;
        processed_cmd.replace( "@@ROOT@@", root );  // FIXME?
        bool suppress_result = false;
        if ( processed_cmd.startsWith( '-' ) )
        {
            suppress_result = true;
            processed_cmd.remove( 0, 1 );  // Drop the -  // FIXME?
        }

        QStringList shell_cmd { "/bin/sh", "-c" };
        shell_cmd << processed_cmd;

        CalamaresUtils::ProcessResult r = System::runCommand(
            location, shell_cmd, QString(), QString(), 10 );

        if ( ( r.getExitCode() != 0 ) && !suppress_result )
        {
            return Calamares::JobResult::error( tr( "Could not run command." ), r.getOutput() );
        }
    }

    return Calamares::JobResult::ok();
}


void
ShellProcessJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_dontChroot = CalamaresUtils::getBool( configurationMap, "dontChroot", false );

    if ( configurationMap.contains( "script" ) )
    {
        m_commands = new CommandList( configurationMap.value( "script" ) );
        if ( m_commands->isEmpty() )
            cDebug() << "ShellProcessJob: \"script\" contains no commands.";
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ShellProcessJobFactory, registerPlugin<ShellProcessJob>(); )
