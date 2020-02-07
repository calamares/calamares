/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
 *   Copyright 2016, Philip Müller <philm@manjaro.org>
 *   Copyright 2017, Alf Gaida <agaida@siduction.org>
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "MachineIdJob.h"
#include "Workers.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QFile>

MachineIdJob::MachineIdJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


MachineIdJob::~MachineIdJob() {}


QString
MachineIdJob::prettyName() const
{
    return tr( "Generate machine-id." );
}

Calamares::JobResult
MachineIdJob::exec()
{
    QString root;

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( gs && gs->contains( "rootMountPoint" ) )
    {
        root = gs->value( "rootMountPoint" ).toString();
    }
    else
    {
        cWarning() << "No *rootMountPoint* defined.";
        return Calamares::JobResult::internalError( tr( "Configuration Error" ),
                                                    tr( "No root mount point is set for MachineId." ),
                                                    Calamares::JobResult::InvalidConfiguration );
    }

    QString target_systemd_machineid_file = QStringLiteral( "/etc/machine-id" );
    QString target_dbus_machineid_file = QStringLiteral( "/var/lib/dbus/machine-id" );
    QString target_entropy_file = QStringLiteral( "/var/lib/urandom/random-seed" );

    const CalamaresUtils::System* system = CalamaresUtils::System::instance();

    // Clear existing files
    if ( m_entropy )
    {
        system->removeTargetFile( target_entropy_file );
    }
    if ( m_dbus )
    {
        system->removeTargetFile( target_dbus_machineid_file );
    }
    if ( m_systemd )
    {
        system->removeTargetFile( target_systemd_machineid_file );
    }

    //Create new files
    if ( m_entropy )
    {
        auto r = MachineId::createEntropy( m_entropy_copy ? MachineId::EntropyGeneration::CopyFromHost
                                                          : MachineId::EntropyGeneration::New,
                                           root,
                                           target_entropy_file );
        if ( !r )
        {
            return r;
        }
    }
    if ( m_systemd )
    {
        auto r = MachineId::createSystemdMachineId( root, target_systemd_machineid_file );
        if ( !r )
        {
            return r;
        }
    }
    if ( m_dbus )
    {
        if ( !system->createTargetParentDirs( target_dbus_machineid_file ) )
        {
            cWarning() << "Could not create DBus data-directory.";
        }
        if ( m_dbus_symlink && QFile::exists( root + target_systemd_machineid_file ) )
        {
            auto r = MachineId::createDBusLink( root, target_dbus_machineid_file, target_systemd_machineid_file );
            if ( !r )
            {
                return r;
            }
        }
        else
        {
            auto r = MachineId::createDBusMachineId( root, target_dbus_machineid_file );
            if ( !r )
            {
                return r;
            }
        }
    }

    return Calamares::JobResult::ok();
}


void
MachineIdJob::setConfigurationMap( const QVariantMap& map )
{
    m_systemd = CalamaresUtils::getBool( map, "systemd", false );

    m_dbus = CalamaresUtils::getBool( map, "dbus", false );
    if ( map.contains( "dbus-symlink" ) )
    {
        m_dbus_symlink = CalamaresUtils::getBool( map, "dbus-symlink", false );
    }
    else if ( map.contains( "symlink" ) )
    {
        m_dbus_symlink = CalamaresUtils::getBool( map, "symlink", false );
        cWarning() << "MachineId: configuration setting *symlink* is deprecated, use *dbus-symlink*.";
    }
    // else it's still false from the constructor

    // ignore it, though, if dbus is false
    m_dbus_symlink = m_dbus && m_dbus_symlink;

    m_entropy = CalamaresUtils::getBool( map, "entropy", false );
    m_entropy_copy = CalamaresUtils::getBool( map, "entropy-copy", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( MachineIdJobFactory, registerPlugin< MachineIdJob >(); )
