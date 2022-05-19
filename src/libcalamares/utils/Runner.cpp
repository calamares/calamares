/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Runner.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "utils/Logger.h"

#include <QProcess>

/** @brief Descend from directory, always relative
 *
 * If @p subdir begins with a "/" or "../" or "./" those are stripped
 * until none are left, then changes @p directory into that
 * subdirectory.
 *
 * Returns @c false if the @p subdir doesn't make sense.
 */
STATICTEST bool
relativeChangeDirectory( QDir& directory, const QString& subdir )
{
    const QString rootPath = directory.absolutePath();
    const QString concatenatedPath = rootPath + '/' + subdir;
    const QString relPath = QDir::cleanPath( concatenatedPath );

    if ( !relPath.startsWith( rootPath ) )
    {
        cWarning() << "Relative path" << subdir << "escapes from" << rootPath;
        return false;
    }

    return directory.cd( relPath );
}


STATICTEST std::pair< bool, QDir >
calculateWorkingDirectory( Calamares::Utils::RunLocation location, const QString& directory )
{
    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;

    if ( location == Calamares::Utils::RunLocation::RunInTarget )
    {
        if ( !gs || !gs->contains( "rootMountPoint" ) )
        {
            cWarning() << "No rootMountPoint in global storage, while RunInTarget is specified";
            return std::make_pair( false, QDir() );
        }

        QDir rootMountPoint( gs->value( "rootMountPoint" ).toString() );
        if ( !rootMountPoint.exists() )
        {
            cWarning() << "rootMountPoint points to a dir which does not exist";
            return std::make_pair( false, QDir() );
        }

        if ( !directory.isEmpty() )
        {

            if ( !relativeChangeDirectory( rootMountPoint, directory ) || !rootMountPoint.exists() )
            {
                cWarning() << "Working directory" << directory << "does not exist in target";
                return std::make_pair( false, QDir() );
            }
        }
        return std::make_pair( true, rootMountPoint );  // Now changed to subdir
    }
    else
    {
        QDir root;
        if ( !directory.isEmpty() )
        {
            root = QDir::root();

            if ( !relativeChangeDirectory( root, directory ) || !root.exists() )
            {
                cWarning() << "Working directory" << directory << "does not exist in host";
                return std::make_pair( false, QDir() );
            }
        }
        return std::make_pair( true, root );  // Now changed to subdir
    }
}

namespace Calamares
{
namespace Utils
{

Runner::Runner() {}


}  // namespace Utils
}  // namespace Calamares


Calamares::Utils::Runner::Runner( const QStringList& command )
{
    setCommand( command );
}

Calamares::Utils::Runner::~Runner() {}

Calamares::Utils::ProcessResult
Calamares::Utils::Runner::run()
{
    if ( m_command.isEmpty() )
    {
        cWarning() << "Cannot run an empty program list";
        return ProcessResult::Code::FailedToStart;
    }

    auto [ ok, workingDirectory ] = calculateWorkingDirectory( m_location, m_directory );
    if ( !ok || !workingDirectory.exists() )
    {
        // Warnings have already been printed
        return ProcessResult::Code::NoWorkingDirectory;
    }

    QProcess process;
    // Make the process run in "C" locale so we don't get issues with translation
    {
        auto env = QProcessEnvironment::systemEnvironment();
        env.insert( "LC_ALL", "C" );
        process.setProcessEnvironment( env );
    }
    process.setProcessChannelMode( QProcess::MergedChannels );
    if ( !m_directory.isEmpty() )
    {
        process.setWorkingDirectory( workingDirectory.absolutePath() );
    }
    if ( m_location == RunLocation::RunInTarget )
    {
        process.setProgram( "chroot" );
        process.setArguments( QStringList { workingDirectory.absolutePath() } << m_command );
    }
    else
    {
        process.setProgram( "env" );
        process.setArguments( m_command );
    }

    if ( m_output )
    {
        connect( &process,
                 &QProcess::readyReadStandardOutput,
                 [ this, &process ]()
                 {
                     do
                     {
                         QString s = process.readLine();
                         if ( !s.isEmpty() )
                         {
                             Q_EMIT this->output( s );
                         }
                     } while ( process.canReadLine() );
                 } );
    }

    cDebug() << Logger::SubEntry << "Running" << Logger::RedactedCommand( m_command );
    process.start();
    if ( !process.waitForStarted() )
    {
        cWarning() << "Process" << m_command.first() << "failed to start" << process.error();
        return ProcessResult::Code::FailedToStart;
    }

    if ( !m_input.isEmpty() )
    {
        process.write( m_input.toLocal8Bit() );
    }
    process.closeWriteChannel();

    if ( !process.waitForFinished( m_timeout > std::chrono::seconds::zero()
                                       ? ( static_cast< int >( std::chrono::milliseconds( m_timeout ).count() ) )
                                       : -1 ) )
    {
        cWarning() << "Process" << m_command.first() << "timed out after" << m_timeout.count() << "ms. Output so far:\n"
                   << Logger::NoQuote << process.readAllStandardOutput();
        return ProcessResult::Code::TimedOut;
    }

    QString output = m_output ? QString() : QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed();
    if ( m_output )
    {
        // Try to read trailing output, if any
        do
        {
            output = process.readLine();
            if ( !output.isEmpty() )
            {
                Q_EMIT this->output( output );
            }
        } while ( !output.isEmpty() );
        output = process.readAllStandardOutput();
        if ( !output.isEmpty() )
        {
            cWarning() << "Some process output left-over";
            Q_EMIT this->output( output );
        }
    }

    if ( process.exitStatus() == QProcess::CrashExit )
    {
        cWarning() << "Process" << m_command.first() << "crashed. Output so far:\n" << Logger::NoQuote << output;
        return ProcessResult::Code::Crashed;
    }

    auto r = process.exitCode();
    const bool showDebug = ( !Calamares::Settings::instance() ) || ( Calamares::Settings::instance()->debugMode() );
    if ( r == 0 )
    {
        if ( showDebug && !output.isEmpty() )
        {
            cDebug() << Logger::SubEntry << "Finished. Exit code:" << r << "output:\n" << Logger::NoQuote << output;
        }
    }
    else  // if ( r != 0 )
    {
        if ( !output.isEmpty() )
        {
            cDebug() << Logger::SubEntry << "Target cmd:" << Logger::RedactedCommand( m_command ) << "Exit code:" << r
                     << "output:\n"
                     << Logger::NoQuote << output;
        }
        else
        {
            cDebug() << Logger::SubEntry << "Target cmd:" << Logger::RedactedCommand( m_command ) << "Exit code:" << r
                     << "(no output)";
        }
    }
    return ProcessResult( r, output );
}
