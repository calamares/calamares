/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
#include "JobQueue.h"
#include "GlobalStorage.h"

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


System*System::instance()
{
    return s_instance;
}


int
System::mount( const QString& devicePath,
       const QString& mountPoint,
       const QString& filesystemName,
       const QString& options )
{
    if ( devicePath.isEmpty() || mountPoint.isEmpty() )
        return -3;

    QDir mountPointDir( mountPoint );
    if ( !mountPointDir.exists() )
    {
        bool ok = mountPointDir.mkpath( mountPoint );
        if ( !ok )
            return -3;
    }

    QString program( "mount" );
    QStringList args = { devicePath, mountPoint };

    if ( !filesystemName.isEmpty() )
        args << "-t" << filesystemName;

    if ( !options.isEmpty() )
        args << "-o" << options;

    return QProcess::execute( program, args );
}

int
System::targetEnvCall( const QStringList& args,
            const QString& workingPath,
            const QString& stdInput,
            int timeoutSec )
{
    QString discard;
    return targetEnvOutput( args,
                         discard,
                         workingPath,
                         stdInput,
                         timeoutSec );
}


int
System::targetEnvCall( const QString& command,
            const QString& workingPath,
            const QString& stdInput,
            int timeoutSec )
{
    return targetEnvCall( QStringList{ command },
                       workingPath,
                       stdInput,
                       timeoutSec );
}


int
System::targetEnvOutput( const QStringList& args,
              QString& output,
              const QString& workingPath,
              const QString& stdInput,
              int timeoutSec )
{
    output.clear();

    if ( !Calamares::JobQueue::instance() )
        return -3;

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs ||
         ( m_doChroot && !gs->contains( "rootMountPoint" ) ) )
    {
        cLog() << "No rootMountPoint in global storage";
        return -3;
    }

    QProcess process;
    QString program;
    QStringList arguments;

    if ( m_doChroot )
    {
        QString destDir = gs->value( "rootMountPoint" ).toString();
        if ( !QDir( destDir ).exists() )
        {
            cLog() << "rootMountPoint points to a dir which does not exist";
            return -3;
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
            cLog() << "Invalid working directory:" << workingPath;
            return -3;
    }

    cLog() << "Running" << program << arguments;
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

    auto r = process.exitCode();
    cLog() << "Finished. Exit code:" << r;
    if ( r != 0 )
    {
        cLog() << "Target cmd" << args;
        cLog() << "Target out" << output;
    }
    return r;
}


int
System::targetEnvOutput( const QString& command,
              QString& output,
              const QString& workingPath,
              const QString& stdInput,
              int timeoutSec )
{
    return targetEnvOutput( QStringList{ command },
                         output,
                         workingPath,
                         stdInput,
                         timeoutSec );
}


QPair<quint64, float>
System::getTotalMemoryB()
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


}
