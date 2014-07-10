/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include <QProcess>

namespace Calamares {


ProcessJob::ProcessJob( const QString& command,
                        const QString& workingPath,
                        int secondsTimeout,
                        QObject* parent )
    : Job( parent )
    , m_command( command )
    , m_workingPath( workingPath )
    , m_timeoutSec( secondsTimeout )
{}


ProcessJob::~ProcessJob()
{}


QString
ProcessJob::prettyName() const
{
    //TODO: show something more meaningful
    return tr( "Run %1" ).arg( m_command );
}


JobResult
ProcessJob::exec()
{
    QProcess p;
    p.setProcessChannelMode( QProcess::MergedChannels );
    p.setWorkingDirectory( m_workingPath );
    p.start( m_command );

    // It's ok to block here because JobQueue runs this method in a separate thread.
    if ( !p.waitForStarted() )
        return JobResult::error( tr( "External command failed to start" ),
                                 tr( "Command %1 failed to start in 30s." )
                                    .arg( m_command ) );

    if ( !p.waitForFinished( m_timeoutSec * 1000/*msec*/ ) )
        return JobResult::error( tr( "External command failed to finish" ),
                                 tr( "Command %1 failed to finish in %2s." )
                                    .arg( m_command )
                                    .arg( m_timeoutSec ) );

    if ( p.exitStatus() == QProcess::NormalExit && p.exitCode() == 0 )
    {
        return JobResult::ok();
    }
    else if ( p.exitStatus() == QProcess::CrashExit )
    {
        return JobResult::error( tr( "External command crashed" ),
                                 tr( "Command %1 crashed.\nOutput:\n%2" )
                                    .arg( m_command )
                                    .arg( QString::fromLocal8Bit( p.readAll() ) ) );
    }
    else //NormalExit with non-zero exit code
    {
        return JobResult::error( tr( "External command finished with errors" ),
                                 tr( "Command %1 finished with exit code %2.\nOutput:\n%3" )
                                    .arg( m_command )
                                    .arg( p.exitCode() )
                                    .arg( QString::fromLocal8Bit( p.readAll() ) ) );
    }
}

} // namespace Calamares
