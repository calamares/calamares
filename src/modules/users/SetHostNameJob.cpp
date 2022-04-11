/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Rohan Garg <rohan@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SetHostNameJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDir>
#include <QFile>

using WriteMode = CalamaresUtils::System::WriteMode;

SetHostNameJob::SetHostNameJob( const Config* c )
    : Calamares::Job()
    , m_config( c )
{
}

QString
SetHostNameJob::prettyName() const
{
    return tr( "Set hostname %1" ).arg( m_config->hostname() );
}


QString
SetHostNameJob::prettyDescription() const
{
    return tr( "Set hostname <strong>%1</strong>." ).arg( m_config->hostname() );
}


QString
SetHostNameJob::prettyStatusMessage() const
{
    return tr( "Setting hostname %1." ).arg( m_config->hostname() );
}

STATICTEST bool
setFileHostname( const QString& hostname )
{
    return CalamaresUtils::System::instance()->createTargetFile(
        QStringLiteral( "/etc/hostname" ), ( hostname + '\n' ).toUtf8(), WriteMode::Overwrite );
}

STATICTEST bool
writeFileEtcHosts( const QString& hostname )
{
    // The actual hostname gets substituted in at %1
    const QString standard_hosts = QStringLiteral( R"(# Standard host addresses
127.0.0.1  localhost
::1        localhost ip6-localhost ip6-loopback
ff02::1    ip6-allnodes
ff02::2    ip6-allrouters
)" );
    const QString this_host = QStringLiteral( R"(# This host address
127.0.1.1  %1
)" );

    const QString etc_hosts = standard_hosts + ( hostname.isEmpty() ? QString() : this_host.arg( hostname ) );
    return CalamaresUtils::System::instance()->createTargetFile(
        QStringLiteral( "/etc/hosts" ), etc_hosts.toUtf8(), WriteMode::Overwrite );
}

STATICTEST bool
setSystemdHostname( const QString& hostname )
{
    QDBusInterface hostnamed( "org.freedesktop.hostname1",
                              "/org/freedesktop/hostname1",
                              "org.freedesktop.hostname1",
                              QDBusConnection::systemBus() );
    if ( !hostnamed.isValid() )
    {
        cWarning() << "Interface" << hostnamed.interface() << "is not valid.";
        return false;
    }

    bool success = true;
    // Static, writes /etc/hostname
    {
        QDBusReply< void > r = hostnamed.call( "SetStaticHostname", hostname, false );
        if ( !r.isValid() )
        {
            cWarning() << "Could not set hostname through org.freedesktop.hostname1.SetStaticHostname." << r.error();
            success = false;
        }
    }
    // Dynamic, updates kernel
    {
        QDBusReply< void > r = hostnamed.call( "SetHostname", hostname, false );
        if ( !r.isValid() )
        {
            cWarning() << "Could not set hostname through org.freedesktop.hostname1.SetHostname." << r.error();
            success = false;
        }
    }

    return success;
}


Calamares::JobResult
SetHostNameJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    if ( !gs || !gs->contains( "rootMountPoint" ) )
    {
        cError() << "No rootMountPoint in global storage";
        return Calamares::JobResult::error( tr( "Internal Error" ) );
    }

    QString destDir = gs->value( "rootMountPoint" ).toString();
    if ( !QDir( destDir ).exists() )
    {
        cError() << "rootMountPoint points to a dir which does not exist";
        return Calamares::JobResult::error( tr( "Internal Error" ) );
    }

    switch ( m_config->hostnameAction() )
    {
    case HostNameAction::None:
        break;
    case HostNameAction::EtcHostname:
        if ( !setFileHostname( m_config->hostname() ) )
        {
            cError() << "Can't write to hostname file";
            return Calamares::JobResult::error( tr( "Cannot write hostname to target system" ) );
        }
        break;
    case HostNameAction::SystemdHostname:
        // Does its own logging
        setSystemdHostname( m_config->hostname() );
        break;
    case HostNameAction::Transient:
        CalamaresUtils::System::instance()->removeTargetFile( QStringLiteral( "/etc/hostname" ) );
        break;
    }

    if ( m_config->writeEtcHosts() )
    {
        if ( !writeFileEtcHosts( m_config->hostname() ) )
        {
            cError() << "Can't write to hosts file";
            return Calamares::JobResult::error( tr( "Cannot write hostname to target system" ) );
        }
    }


    return Calamares::JobResult::ok();
}
