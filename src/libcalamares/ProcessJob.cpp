/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ProcessJob.h"

#include "utils/CommandList.h"
#include "utils/Logger.h"

#include <QDir>

namespace Calamares
{

ProcessJob::ProcessJob( const QString& command,
                        const QString& workingPath,
                        bool runInChroot,
                        std::chrono::seconds secondsTimeout,
                        QObject* parent )
    : Job( parent )
    , m_command( command )
    , m_workingPath( workingPath )
    , m_runInChroot( runInChroot )
    , m_timeoutSec( secondsTimeout )
{
}

ProcessJob::~ProcessJob() = default;

QString
ProcessJob::prettyName() const
{
    return ( m_runInChroot ? QStringLiteral( "Run command '%1' in target system" )
                           : QStringLiteral( "Run command '%1'" ) )
        .arg( m_command );
}

QString
ProcessJob::prettyStatusMessage() const
{
    if ( m_runInChroot )
    {
        return tr( "Running command %1 in target system…", "@status" ).arg( m_command );
    }
    else
    {
        return tr( "Running command %1…", "@status" ).arg( m_command );
    }
}

JobResult
ProcessJob::exec()
{
    Calamares::CommandList l( m_runInChroot, m_timeoutSec );
    l.push_back( Calamares::CommandLine { m_command } );
    return l.run();
}

}  // namespace Calamares
