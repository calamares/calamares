/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "HostInfoJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <QDir>
#include <QFile>

#ifdef WITH_KOSRelease
#include <KOSRelease>
#endif

#ifdef Q_OS_FREEBSD
#include <sys/types.h>

#include <sys/sysctl.h>
#endif

HostInfoJob::HostInfoJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

HostInfoJob::~HostInfoJob() {}


QString
HostInfoJob::prettyName() const
{
    return tr( "Collecting information about your machine." );
}

QString
hostOS()
{
#if defined( Q_OS_FREEBSD )
    return QStringLiteral( "FreeBSD" );
#elif defined( Q_OS_LINUX )
    return QStringLiteral( "Linux" );
#else
    return QStringLiteral( "<unknown>" );
#endif
}

QString
hostOSName()
{
#ifdef WITH_KOSRelease
    KOSRelease r;
    if ( !r.name().isEmpty() )
    {
        return r.name();
    }
#endif
    return hostOS();
}

static QString
hostCPUmatch( const QString& s )
{
    const QString line = s.toLower();
    if ( line.contains( "intel" ) )
    {
        return QStringLiteral( "Intel" );
    }
    else if ( line.contains( "amd" ) )
    {
        return QStringLiteral( "AMD" );
    }
    return QString();
}

#if defined( Q_OS_FREEBSD )
QString
hostCPU_FreeBSD()
{
    constexpr const size_t sysctl_buffer_size = 128;
    char sysctl_buffer[ sysctl_buffer_size ];
    size_t s = sysctl_buffer_size;

    memset( sysctl_buffer, 0, sizeof( sysctl_buffer ) );
    int r = sysctlbyname( "hw.model", &sysctl_buffer, &s, NULL, 0 );
    if ( r )
    {
        return QString();
    }

    sysctl_buffer[ sysctl_buffer_size - 1 ] = 0;
    QString model( sysctl_buffer );
    return hostCPUmatch( model );
}
#endif

#if defined( Q_OS_LINUX )
QString
hostCPU_Linux()
{
    QFile cpuinfo( "/proc/cpuinfo" );
    if ( cpuinfo.open( QIODevice::ReadOnly ) )
    {
        QTextStream in( &cpuinfo );
        QString line;
        while ( in.readLineInto( &line ) )
        {
            if ( line.startsWith( "vendor_id" ) )
            {
                return hostCPUmatch( line );
            }
        }
    }
    return QString();  // Not open, or not found
}
#endif

QString
hostCPU()
{
#if defined( Q_OS_FREEBSD )
    return hostCPU_FreeBSD();
#elif defined( Q_OS_LINUX )
    return hostCPU_Linux();
#else
    return QString();
#endif
}


Calamares::JobResult
HostInfoJob::exec()
{
    cDebug() << "Collecting host information...";

    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    gs->insert( "hostOS", hostOS() );
    gs->insert( "hostOSName", hostOSName() );
    gs->insert( "hostCPU", hostCPU() );

    // Memory can't be negative, so it's reported as unsigned long.
    auto ram = CalamaresUtils::BytesToMiB( qint64( CalamaresUtils::System::instance()->getTotalMemoryB().first ) );
    if ( ram )
    {
        gs->insert( "hostRAMMiB", ram );
    }

    return Calamares::JobResult::ok();
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( HostInfoJobFactory, registerPlugin< HostInfoJob >(); )
