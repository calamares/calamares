/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "ProcessJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QDir>
#include <QProcess>

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


ProcessJob::~ProcessJob() {}


QString
ProcessJob::prettyName() const
{
    return ( m_runInChroot ? tr( "Run command '%1' in target system." ) : tr( " Run command '%1'." ) ).arg( m_command );
}


QString
ProcessJob::prettyStatusMessage() const
{
    return tr( "Running command %1 %2" ).arg( m_command ).arg( m_runInChroot ? "in chroot." : " ." );
}


JobResult
ProcessJob::exec()
{
    using CalamaresUtils::System;

    if ( m_runInChroot )
        return CalamaresUtils::System::instance()
            ->targetEnvCommand( { m_command }, m_workingPath, QString(), m_timeoutSec )
            .explainProcess( m_command, m_timeoutSec );
    else
        return System::runCommand( System::RunLocation::RunInHost,
                                   { "/bin/sh", "-c", m_command },
                                   m_workingPath,
                                   QString(),
                                   m_timeoutSec )
            .explainProcess( m_command, m_timeoutSec );
}

}  // namespace Calamares
