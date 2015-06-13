/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Rohan Garg <rohan@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#include "SetHostNameJob.h"

#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "JobQueue.h"

#include <QFile>
#include <QDir>

SetHostNameJob::SetHostNameJob( const QString& hostname )
    : Calamares::Job()
    , m_hostname( hostname )
{
}

QString SetHostNameJob::prettyName() const
{
    return tr( "Set hostname %1" ).arg( m_hostname );
}


QString
SetHostNameJob::prettyDescription() const
{
    return tr( "Set hostname <strong>%1</strong>." ).arg( m_hostname );
}


QString
SetHostNameJob::prettyStatusMessage() const
{
    return tr( "Setting hostname %1." ).arg( m_hostname );
}

Calamares::JobResult SetHostNameJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    if ( !gs || !gs->contains( "rootMountPoint" ) )
    {
        cLog() << "No rootMountPoint in global storage";
        return Calamares::JobResult::error( tr( "Internal Error" ) );
    }

    QString destDir = gs->value( "rootMountPoint" ).toString();
    if ( !QDir( destDir ).exists() )
    {
        cLog() << "rootMountPoint points to a dir which does not exist";
        return Calamares::JobResult::error( tr( "Internal Error" ) );
    }

    QFile hostfile( destDir + "/etc/hostname" );
    if ( !hostfile.open( QFile::WriteOnly ) )
    {
        cLog() << "Can't write to hostname file";
        return Calamares::JobResult::error( tr( "Cannot write hostname to target system" ) );
    }

    QTextStream hostfileout( &hostfile );
    hostfileout << m_hostname << "\n";
    hostfile.close();

    QFile hostsfile( destDir + "/etc/hosts" );
    if ( !hostsfile.open( QFile::WriteOnly ) )
    {
        cLog() << "Can't write to hosts file";
        return Calamares::JobResult::error( tr( "Cannot write hostname to target system" ) );
    }

    // We also need to write the appropriate entries for /etc/hosts
    QTextStream hostsfileout( &hostsfile );
    // ipv4 support
    hostsfileout << "127.0.0.1" << "\t" << "localhost" << "\n";
    hostsfileout << "127.0.1.1" << "\t" << m_hostname << "\n";
    // ipv6 support
    hostsfileout << "::1" << "\t" << "localhost ip6-localhost ip6-loopback" << "\n";
    hostsfileout << "ff02::1 ip6-allnodes" << "\n" << "ff02::2 ip6-allrouters" << "\n";
    hostsfile.close();

    return Calamares::JobResult::ok();
}
