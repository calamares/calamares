/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

namespace Calamares {


ProcessJob::ProcessJob( const QString& command,
                        const QString& workingPath,
                        bool runInChroot,
                        int secondsTimeout,
                        QObject* parent )
    : Job( parent )
    , m_command( command )
    , m_workingPath( workingPath )
    , m_runInChroot( runInChroot )
    , m_timeoutSec( secondsTimeout )
{}


ProcessJob::~ProcessJob()
{}


QString
ProcessJob::prettyName() const
{
    //TODO: show something more meaningful
    return tr( "Run command %1 %2" )
            .arg( m_command )
            .arg( m_runInChroot ? "in chroot." : " ." );
}


QString
ProcessJob::prettyStatusMessage() const
{
    return tr( "Running command %1 %2" )
            .arg( m_command )
            .arg( m_runInChroot ? "in chroot." : " ." );
}


JobResult
ProcessJob::exec()
{
    int ec = 0;
    QString output;
    if ( m_runInChroot )
        ec = CalamaresUtils::System::instance()->
             targetEnvOutput( m_command,
                              output,
                              m_workingPath,
                              QString(),
                              m_timeoutSec );
    else
        ec = callOutput( m_command,
                         output,
                         m_workingPath,
                         QString(),
                         m_timeoutSec );

    if ( ec == 0 )
        return JobResult::ok();

    if ( ec == -1 ) //Crash!
        return JobResult::error( tr( "External command crashed" ),
                                 tr( "Command %1 crashed.\nOutput:\n%2" )
                                        .arg( m_command )
                                        .arg( output ) );

    if ( ec == -2 )
        return JobResult::error( tr( "External command failed to start" ),
                                 tr( "Command %1 failed to start." )
                                    .arg( m_command ) );

    if ( ec == -3 )
        return JobResult::error( tr( "Internal error when starting command" ),
                                 tr( "Bad parameters for process job call." ) );

    if ( ec == -4 )
        return JobResult::error( tr( "External command failed to finish" ),
                                 tr( "Command %1 failed to finish in %2s.\nOutput:\n%3" )
                                    .arg( m_command )
                                    .arg( m_timeoutSec )
                                    .arg( output ) );

    //Any other exit code
    return JobResult::error( tr( "External command finished with errors" ),
                             tr( "Command %1 finished with exit code %2.\nOutput:\n%3" )
                                .arg( m_command )
                                .arg( ec )
                                .arg( output ) );
}


int
ProcessJob::callOutput( const QString& command,
                        QString& output,
                        const QString& workingPath,
                        const QString& stdInput,
                        int timeoutSec )
{
    output.clear();

    QProcess process;
    process.setProgram( "/bin/sh" );
    process.setArguments( { "-c", command } );
    process.setProcessChannelMode( QProcess::MergedChannels );

    if ( !workingPath.isEmpty() )
    {
        if ( QDir( workingPath ).exists() )
            process.setWorkingDirectory( QDir( workingPath ).absolutePath() );
        else
        {
            cLog() << "Invalid working directory:" << workingPath;
            return -3;
        }
    }

    cLog() << "Running" << command;
    process.start();
    if ( !process.waitForStarted() )
    {
        cLog() << "Process failed to start" << process.error();
        return -2;
    }

    if ( !stdInput.isEmpty() )
    {
        process.write( stdInput.toLocal8Bit() );
        process.closeWriteChannel();
    }

    if ( !process.waitForFinished( timeoutSec ? ( timeoutSec * 1000 ) : -1 ) )
    {
        cLog() << "Timed out. output so far:";
        cLog() << process.readAllStandardOutput();
        return -4;
    }

    output.append( QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed() );

    if ( process.exitStatus() == QProcess::CrashExit )
    {
        cLog() << "Process crashed";
        return -1;
    }

    cLog() << "Finished. Exit code:" << process.exitCode();
    return process.exitCode();
}


} // namespace Calamares
