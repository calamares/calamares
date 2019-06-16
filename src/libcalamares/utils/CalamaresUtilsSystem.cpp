/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "CalamaresUtilsSystem.h"

#include "utils/Logger.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QRegularExpression>

#ifdef Q_OS_LINUX
#include <sys/sysinfo.h>
#endif

#ifdef Q_OS_FREEBSD
#include <sys/types.h>
#include <sys/sysctl.h>
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
        : list(l)
    {
    }

    const QStringList& list;
} ;

QDebug&
operator<<( QDebug& s, const RedactedList& l )
{
    // Special case logging: don't log the (encrypted) password.
    if ( l.list.contains( "usermod" ) )
    {
        for ( const auto& item : l.list )
            if ( item.startsWith( "$6$" ) )
                s << "<password>";
            else
                s << item;
    }
    else
        s << l.list;

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
    if ( !doChroot )
        Calamares::JobQueue::instance()->globalStorage()->insert( "rootMountPoint", "/" );
}


System::~System()
{}


System*
System::instance()
{
    if ( !s_instance )
    {
        cError() << "No Calamares system-object has been created.";
        cError() << Logger::SubEntry << "using a bogus instance instead.";
        return new System( true, nullptr );
    }
    return s_instance;
}


int
System::mount( const QString& devicePath,
       const QString& mountPoint,
       const QString& filesystemName,
       const QString& options )
{
    if ( devicePath.isEmpty() || mountPoint.isEmpty() )
    {
        if ( devicePath.isEmpty() )
            cWarning() << "Can't mount an empty device.";
        if ( mountPoint.isEmpty() )
            cWarning() << "Can't mount on an empty mountpoint.";

        return static_cast<int>(ProcessResult::Code::NoWorkingDirectory);
    }

    QDir mountPointDir( mountPoint );
    if ( !mountPointDir.exists() )
    {
        bool ok = mountPointDir.mkpath( mountPoint );
        if ( !ok )
        {
            cWarning() << "Could not create mountpoint" << mountPoint;
            return static_cast<int>(ProcessResult::Code::NoWorkingDirectory);
        }
    }

    QString program( "mount" );
    QStringList args = { devicePath, mountPoint };

    if ( !filesystemName.isEmpty() )
        args << "-t" << filesystemName;

    if ( !options.isEmpty() )
        args << "-o" << options;

    return QProcess::execute( program, args );
}

ProcessResult
System::runCommand(
    System::RunLocation location,
    const QStringList& args,
    const QString& workingPath,
    const QString& stdInput,
    int timeoutSec )
{
    QString output;

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;

    if ( ( location == System::RunLocation::RunInTarget ) &&
         ( !gs || !gs->contains( "rootMountPoint" ) ) )
    {
        cWarning() << "No rootMountPoint in global storage";
        return ProcessResult::Code::NoWorkingDirectory;
    }

    QProcess process;
    QString program;
    QStringList arguments;

    if ( location == System::RunLocation::RunInTarget )
    {
        QString destDir = gs->value( "rootMountPoint" ).toString();
        if ( !QDir( destDir ).exists() )
        {
            cWarning() << "rootMountPoint points to a dir which does not exist";
            return ProcessResult::Code::NoWorkingDirectory;
        }

        program = "chroot";
        arguments = QStringList( { destDir } );
        arguments << args;
    }
    else
    {
        program = "env";
        arguments << args;
    }

    process.setProgram( program );
    process.setArguments( arguments );
    process.setProcessChannelMode( QProcess::MergedChannels );

    if ( !workingPath.isEmpty() )
    {
        if ( QDir( workingPath ).exists() )
            process.setWorkingDirectory( QDir( workingPath ).absolutePath() );
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
        cWarning() << "Process failed to start" << process.error();
        return ProcessResult::Code::FailedToStart;
    }

    if ( !stdInput.isEmpty() )
    {
        process.write( stdInput.toLocal8Bit() );
    }
    process.closeWriteChannel();

    if ( !process.waitForFinished( timeoutSec ? ( timeoutSec * 1000 ) : -1 ) )
    {
        cWarning().noquote().nospace() << "Timed out. Output so far:\n" <<
            process.readAllStandardOutput();
        return ProcessResult::Code::TimedOut;
    }

    output.append( QString::fromLocal8Bit( process.readAllStandardOutput() ).trimmed() );

    if ( process.exitStatus() == QProcess::CrashExit )
    {
        cWarning().noquote().nospace() << "Process crashed. Output so far:\n" << output;
        return ProcessResult::Code::Crashed;
    }

    auto r = process.exitCode();
    cDebug() << "Finished. Exit code:" << r;
    bool showDebug = ( !Calamares::Settings::instance() ) || ( Calamares::Settings::instance()->debugMode() );
    if ( ( r != 0 ) || showDebug )
    {
        cDebug() << "Target cmd:" << RedactedList( args );
        cDebug().noquote().nospace() << "Target output:\n" << output;
    }
    return ProcessResult(r, output);
}


QPair<quint64, float>
System::getTotalMemoryB() const
{
#ifdef Q_OS_LINUX
    struct sysinfo i;
    int r = sysinfo( &i );

    if (r)
        return qMakePair(0, 0.0);

    return qMakePair(quint64( i.mem_unit ) * quint64( i.totalram ), 1.1);
#elif defined( Q_OS_FREEBSD )
    unsigned long memsize;
    size_t s = sizeof(memsize);

    int r = sysctlbyname("vm.kmem_size", &memsize, &s, NULL, 0);
    if (r)
        return qMakePair(0, 0.0);

    return qMakePair(memsize, 1.01);
#else
    return qMakePair(0, 0.0);  // Unsupported
#endif
}


QString
System::getCpuDescription() const
{
    QString model;

#ifdef Q_OS_LINUX
    QFile file("/proc/cpuinfo");
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
        while ( !file.atEnd() )
        {
            QByteArray line = file.readLine();
            if ( line.startsWith( "model name" ) && (line.indexOf( ':' ) > 0) )
            {
                model = QString::fromLatin1( line.right(line.length() - line.indexOf( ':' ) ) );
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
ProcessResult::explainProcess( int ec, const QString& command, const QString& output, int timeout )
{
    using Calamares::JobResult;

    if ( ec == 0 )
        return JobResult::ok();

    QString outputMessage = output.isEmpty()
        ? QCoreApplication::translate( "ProcessResult", "\nThere was no output from the command.")
        : (QCoreApplication::translate( "ProcessResult", "\nOutput:\n") + output);

    if ( ec == static_cast<int>(ProcessResult::Code::Crashed) ) //Crash!
        return JobResult::error( QCoreApplication::translate( "ProcessResult", "External command crashed." ),
                                 QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> crashed." )
                                        .arg( command )
                                        + outputMessage );

    if ( ec == static_cast<int>(ProcessResult::Code::FailedToStart) )
        return JobResult::error( QCoreApplication::translate( "ProcessResult", "External command failed to start." ),
                                 QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> failed to start." )
                                    .arg( command ) );

    if ( ec == static_cast<int>(ProcessResult::Code::NoWorkingDirectory) )
        return JobResult::error( QCoreApplication::translate( "ProcessResult", "Internal error when starting command." ),
                                 QCoreApplication::translate( "ProcessResult", "Bad parameters for process job call." ) );

    if ( ec == static_cast<int>(ProcessResult::Code::TimedOut) )
        return JobResult::error( QCoreApplication::translate( "ProcessResult", "External command failed to finish." ),
                                 QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> failed to finish in %2 seconds." )
                                    .arg( command )
                                    .arg( timeout )
                                    + outputMessage );

    //Any other exit code
    return JobResult::error( QCoreApplication::translate( "ProcessResult", "External command finished with errors." ),
                             QCoreApplication::translate( "ProcessResult", "Command <i>%1</i> finished with exit code %2." )
                                .arg( command )
                                .arg( ec )
                                + outputMessage );
}

}  // namespace
