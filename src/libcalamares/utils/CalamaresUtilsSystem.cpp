/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "CalamaresUtilsSystem.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "utils/Logger.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>

#ifdef Q_OS_LINUX
#include <sys/sysinfo.h>
#endif

#ifdef Q_OS_FREEBSD
// clang-format off
// these includes need to stay in-order (that's a FreeBSD thing)
#include <sys/types.h>
#include <sys/sysctl.h>
// clang-format on
#endif

/** @brief When logging commands, don't log everything.
 *
 * The command-line arguments to some commands may contain the
 * encrypted password set by the user. Don't log that password,
 * since the log may get posted to bug reports, or stored in
 * the target system.
 */
struct RedactedList
{
    RedactedList( const QStringList& l )
        : list( l )
    {
    }

    const QStringList& list;
};

QDebug&
operator<<( QDebug& s, const RedactedList& l )
{
    // Special case logging: don't log the (encrypted) password.
    if ( l.list.contains( "usermod" ) )
    {
        for ( const auto& item : l.list )
            if ( item.startsWith( "$6$" ) )
            {
                s << "<password>";
            }
            else
            {
                s << item;
            }
    }
    else
    {
        s << l.list;
    }

    return s;
}

namespace CalamaresUtils
{

System* System::s_instance = nullptr;


System::System( bool doChroot, QObject* parent )
    : QObject( parent )
    , m_doChroot( doChroot )
{
    Q_ASSERT( !s_instance );
    s_instance = this;
    if ( !doChroot && Calamares::JobQueue::instance() && Calamares::JobQueue::instance()->globalStorage() )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert( "rootMountPoint", "/" );
    }
}


System::~System() {}


System*
System::instance()
{
    if ( !s_instance )
    {
        cError() << "No Calamares system-object has been created.";
        cDebug() << Logger::SubEntry << "using a bogus instance instead.";
        return new System( true, nullptr );
    }
    return s_instance;
}


ProcessResult
System::runCommand( System::RunLocation location,
                    const QStringList& args,
                    const QString& workingPath,
                    const QString& stdInput,
                    std::chrono::seconds timeoutSec )
{
    if ( args.isEmpty() )
    {
        cWarning() << "Cannot run an empty program list";
        return ProcessResult::Code::FailedToStart;
    }

    Calamares::GlobalStorage* gs
        = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;

    if ( ( location == System::RunLocation::RunInTarget ) && ( !gs || !gs->contains( "rootMountPoint" ) ) )
    {
        cWarning() << "No rootMountPoint in global storage, while RunInTarget is specified";
        return ProcessResult::Code::NoWorkingDirectory;
    }

    QString program;
    QStringList arguments( args );

    if ( location == System::RunLocation::RunInTarget )
    {
        QString destDir = gs->value( "rootMountPoint" ).toString();
        if ( !QDir( destDir ).exists() )
        {
            cWarning() << "rootMountPoint points to a dir which does not exist";
            return ProcessResult::Code::NoWorkingDirectory;
        }

        program = "chroot";
        arguments.prepend( destDir );
    }
    else
    {
        program = "env";
    }

    QProcess process;
    process.setProgram( program );
    process.setArguments( arguments );
    process.setProcessChannelMode( QProcess::MergedChannels );

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

    cDebug() << "Running" << program << RedactedList( arguments );
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
        else
        {
            cDebug() << Logger::SubEntry << "Finished. Exit code:" << r;
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
}

/// @brief Cheap check if a path is absolute.
static inline bool
isAbsolutePath( const QString& path )
{
    return path.startsWith( '/' );
}

QString
System::targetPath( const QString& path ) const
{
    if ( doChroot() )
    {
        Calamares::GlobalStorage* gs
            = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;

        if ( !gs || !gs->contains( "rootMountPoint" ) )
        {
            cWarning() << "No rootMountPoint in global storage, cannot name target file" << path;
            return QString();
        }

        QString root = gs->value( "rootMountPoint" ).toString();
        return isAbsolutePath( path ) ? ( root + path ) : ( root + '/' + path );
    }
    else
    {
        return isAbsolutePath( path ) ? path : ( QStringLiteral( "/" ) + path );
    }
}

CreationResult
System::createTargetFile( const QString& path, const QByteArray& contents, WriteMode mode ) const
{
    QString completePath = targetPath( path );
    if ( completePath.isEmpty() )
    {
        return CreationResult( CreationResult::Code::Invalid );
    }

    QFile f( completePath );
    if ( ( mode == WriteMode::KeepExisting ) && f.exists() )
    {
        return CreationResult( CreationResult::Code::AlreadyExists );
    }

    QIODevice::OpenMode m =
#if QT_VERSION >= QT_VERSION_CHECK( 5, 11, 0 )
        // New flag from Qt 5.11, implies WriteOnly
        ( mode == WriteMode::KeepExisting ? QIODevice::NewOnly : QIODevice::WriteOnly ) |
#endif
        QIODevice::WriteOnly | QIODevice::Truncate;

    if ( !f.open( m ) )
    {
        return CreationResult( CreationResult::Code::Failed );
    }

    if ( f.write( contents ) != contents.size() )
    {
        f.close();
        f.remove();
        return CreationResult( CreationResult::Code::Failed );
    }

    f.close();
    return CreationResult( QFileInfo( f ).canonicalFilePath() );
}

void
System::removeTargetFile( const QString& path ) const
{
    if ( !isAbsolutePath( path ) )
    {
        cWarning() << "Will not remove non-absolute path" << path;
        return;
    }
    QString target = targetPath( path );
    if ( !target.isEmpty() )
    {
        QFile::remove( target );
    }
    // If it was empty, a warning was already printed
}

bool
System::createTargetDirs( const QString& path ) const
{
    if ( !isAbsolutePath( path ) )
    {
        cWarning() << "Will not create basedirs for non-absolute path" << path;
        return false;
    }

    QString target = targetPath( path );
    if ( target.isEmpty() )
    {
        // If it was empty, a warning was already printed
        return false;
    }

    QString root = Calamares::JobQueue::instance()->globalStorage()->value( "rootMountPoint" ).toString();
    if ( root.isEmpty() )
    {
        return false;
    }

    QDir d( root );
    if ( !d.exists() )
    {
        cWarning() << "Root mountpoint" << root << "does not exist.";
        return false;
    }
    return d.mkpath( target );  // This re-does everything starting from the **host** /
}

bool
System::createTargetParentDirs( const QString& filePath ) const
{
    return createTargetDirs( QFileInfo( filePath ).dir().path() );
}


QPair< quint64, float >
System::getTotalMemoryB() const
{
#ifdef Q_OS_LINUX
    struct sysinfo i;
    int r = sysinfo( &i );

    if ( r )
    {
        return qMakePair( 0, 0.0 );
    }

    return qMakePair( quint64( i.mem_unit ) * quint64( i.totalram ), 1.1 );
#elif defined( Q_OS_FREEBSD )
    unsigned long memsize;
    size_t s = sizeof( memsize );

    int r = sysctlbyname( "vm.kmem_size", &memsize, &s, NULL, 0 );
    if ( r )
    {
        return qMakePair( 0, 0.0 );
    }

    return qMakePair( memsize, 1.01 );
#else
    return qMakePair( 0, 0.0 );  // Unsupported
#endif
}


QString
System::getCpuDescription() const
{
    QString model;

#ifdef Q_OS_LINUX
    QFile file( "/proc/cpuinfo" );
    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        while ( !file.atEnd() )
        {
            QByteArray line = file.readLine();
            if ( line.startsWith( "model name" ) && ( line.indexOf( ':' ) > 0 ) )
            {
                model = QString::fromLatin1( line.right( line.length() - line.indexOf( ':' ) ) );
                break;
            }
        }
#elif defined( Q_OS_FREEBSD )
    // This would use sysctl "hw.model", which has a string value
#endif
    return model.simplified();
}

quint64
System::getTotalDiskB() const
{
    return 0;
}

bool
System::doChroot() const
{
    return m_doChroot;
}

Calamares::JobResult
ProcessResult::explainProcess( int ec, const QString& command, const QString& output, std::chrono::seconds timeout )
{
    using Calamares::JobResult;

    if ( ec == 0 )
    {
        return JobResult::ok();
    }

    QString outputMessage = output.isEmpty()
        ? QCoreApplication::translate( "ProcessResult", "\nThere was no output from the command." )
        : ( QCoreApplication::translate( "ProcessResult", "\nOutput:\n" ) + output );

    if ( ec == static_cast< int >( ProcessResult::Code::Crashed ) )  //Crash!
        return JobResult::error(
            QCoreApplication::translate( "ProcessResult", "External command crashed." ),
            QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> crashed." ).arg( command )
                + outputMessage );

    if ( ec == static_cast< int >( ProcessResult::Code::FailedToStart ) )
        return JobResult::error(
            QCoreApplication::translate( "ProcessResult", "External command failed to start." ),
            QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> failed to start." ).arg( command ) );

    if ( ec == static_cast< int >( ProcessResult::Code::NoWorkingDirectory ) )
        return JobResult::error(
            QCoreApplication::translate( "ProcessResult", "Internal error when starting command." ),
            QCoreApplication::translate( "ProcessResult", "Bad parameters for process job call." ) );

    if ( ec == static_cast< int >( ProcessResult::Code::TimedOut ) )
        return JobResult::error(
            QCoreApplication::translate( "ProcessResult", "External command failed to finish." ),
            QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> failed to finish in %2 seconds." )
                    .arg( command )
                    .arg( timeout.count() )
                + outputMessage );

    //Any other exit code
    return JobResult::error(
        QCoreApplication::translate( "ProcessResult", "External command finished with errors." ),
        QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> finished with exit code %2." )
                .arg( command )
                .arg( ec )
            + outputMessage );
}

}  // namespace CalamaresUtils
