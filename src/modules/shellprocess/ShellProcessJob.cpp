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

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QDateTime>
#include <QProcess>
#include <QThread>

ShellProcessJob::ShellProcessJob( QObject* parent )
    : Calamares::CppJob( parent )
    , m_commands( nullptr )
{
}


ShellProcessJob::~ShellProcessJob() {}


QString
ShellProcessJob::prettyName() const
{
    return tr( "Shell Processes Job" );
}


Calamares::JobResult
ShellProcessJob::exec()
{

    if ( !m_commands || m_commands->isEmpty() )
    {
        cWarning() << "No commands to execute" << moduleInstanceKey();
        return Calamares::JobResult::ok();
    }

    return m_commands->run();
}


void
ShellProcessJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool dontChroot = CalamaresUtils::getBool( configurationMap, "dontChroot", false );
    qint64 timeout = CalamaresUtils::getInteger( configurationMap, "timeout", 10 );
    if ( timeout < 1 )
    {
        timeout = 10;
    }

    if ( configurationMap.contains( "script" ) )
    {
        m_commands = std::make_unique< CalamaresUtils::CommandList >(
            configurationMap.value( "script" ), !dontChroot, std::chrono::seconds( timeout ) );
        if ( m_commands->isEmpty() )
        {
            cDebug() << "ShellProcessJob: \"script\" contains no commands for" << moduleInstanceKey();
        }
    }
    else
    {
        cWarning() << "No script given for ShellProcessJob" << moduleInstanceKey();
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ShellProcessJobFactory, registerPlugin< ShellProcessJob >(); )
