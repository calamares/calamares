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
#include "utils/Logger.h"

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
calculateWorkingDirectory( Calamares::Utils::RunLocation location, QString directory )
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

struct Runner::Private
{
    QProcess m_process;
};


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
    process.setProcessChannelMode( QProcess::MergedChannels );
    process.setWorkingDirectory( workingDirectory.absolutePath() );
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

    return ProcessResult::Code::Crashed;
#if 0
    if ( !workingPath.isEmpty() )
    {
        if ( QDir( workingPath ).exists() )
        {
            process.setWorkingDirectory( QDir( workingPath ).absolutePath() );
        }
        else
        {
            cWarning() << "Invalid working directory:" << workingPath;
            return ProcessResult::Code::NoWorkingDirectory;
        }
    }

    cDebug() << Logger::SubEntry << "Running" << program << RedactedList( arguments );
    process.start();
    if ( !process.waitForStarted() )
    {
        cWarning() << "Process" << args.first() << "failed to start" << process.error();
        return ProcessResult::Code::FailedToStart;
    }

    if ( !stdInput.isEmpty() )
    {
        process.write( stdInput.toLocal8Bit() );
    }
    process.closeWriteChannel();

    if ( !process.waitForFinished( timeoutSec > std::chrono::seconds::zero()
                                   ? ( static_cast< int >( std::chrono::milliseconds( timeoutSec ).count() ) )
                                   : -1 ) )
    {
        cWarning() << "Process" << args.first() << "timed out after" << timeoutSec.count() << "s. Output so far:\n"
                   << Logger::NoQuote << process.readAllStandardOutput();
        return ProcessResult::Code::TimedOut;
    }

    QString output = QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed();

    if ( process.exitStatus() == QProcess::CrashExit )
    {
        cWarning() << "Process" << args.first() << "crashed. Output so far:\n" << Logger::NoQuote << output;
        return ProcessResult::Code::Crashed;
    }

    auto r = process.exitCode();
    bool showDebug = ( !Calamares::Settings::instance() ) || ( Calamares::Settings::instance()->debugMode() );
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
            cDebug() << Logger::SubEntry << "Target cmd:" << RedactedList( args ) << "Exit code:" << r << "output:\n"
                     << Logger::NoQuote << output;
        }
        else
        {
            cDebug() << Logger::SubEntry << "Target cmd:" << RedactedList( args ) << "Exit code:" << r << "(no output)";
        }
    }
    return ProcessResult( r, output );
#endif
}
