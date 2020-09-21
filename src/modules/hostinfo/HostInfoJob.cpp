/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
static QString
hostCPUmatchARM( const QString& s )
{
    /* The "CPU implementer" line is for ARM CPUs in general.
     *
     * The specific value given distinguishes *which designer*
     * (or architecture licensee, who cares) produced the current
     * silicon. For instance, a list from lscpu-arm.c (Linux kernel)
     * shows this:
     *
    static const struct hw_impl hw_implementer[] = {
    { 0x41, arm_part,     "ARM" },
    { 0x42, brcm_part,    "Broadcom" },
    { 0x43, cavium_part,  "Cavium" },
    { 0x44, dec_part,     "DEC" },
    { 0x48, hisi_part,    "HiSilicon" },
    { 0x4e, nvidia_part,  "Nvidia" },
    { 0x50, apm_part,     "APM" },
    { 0x51, qcom_part,    "Qualcomm" },
    { 0x53, samsung_part, "Samsung" },
    { 0x56, marvell_part, "Marvell" },
    { 0x66, faraday_part, "Faraday" },
    { 0x69, intel_part,   "Intel" },
    { -1,   unknown_part, "unknown" },
    };
     *
     * Since the specific implementor isn't interesting, just
     * map everything to "ARM".
     */
    return QStringLiteral( "ARM" );
}

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
            if ( line.startsWith( "CPU implementer" ) )
            {
                return hostCPUmatchARM( line );
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
