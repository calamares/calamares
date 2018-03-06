/* === This file is part of Calamares - <https://github.com/calamares> ===
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

    return CalamaresUtils::ProcessResult::explainProcess( ec, m_command, output, m_timeoutSec );
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
            cWarning() << "Invalid working directory:" << workingPath;
            return -3;
        }
    }

    cDebug() << "Running" << command;
    process.start();
    if ( !process.waitForStarted() )
    {
        cWarning() << "Process failed to start" << process.error();
        return -2;
    }

    if ( !stdInput.isEmpty() )
    {
        process.write( stdInput.toLocal8Bit() );
        process.closeWriteChannel();
    }

    if ( !process.waitForFinished( timeoutSec ? ( timeoutSec * 1000 ) : -1 ) )
    {
        cWarning() << "Timed out. output so far:";
        output.append( QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed() );
        cWarning() << output;
        return -4;
    }

    output.append( QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed() );

    if ( process.exitStatus() == QProcess::CrashExit )
    {
        cWarning() << "Process crashed";
        return -1;
    }

    cDebug() << "Finished. Exit code:" << process.exitCode();
    return process.exitCode();
}

} // namespace Calamares
