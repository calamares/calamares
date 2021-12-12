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

#include "utils/CalamaresUtilsSystem.h"
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
