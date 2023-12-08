/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-FileCopyrightText: 2016 Philip Müller <philm@manjaro.org>
 *   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "MachineIdJob.h"
#include "Workers.h"

#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/System.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QFile>

const NamedEnumTable< MachineId::SystemdMachineIdStyle >&
styleNames()
{
    using T = MachineId::SystemdMachineIdStyle;
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< MachineId::SystemdMachineIdStyle > names {
        { QStringLiteral( "none" ), T::Blank },
        { QStringLiteral( "blank" ), T::Blank },
        { QStringLiteral( "uuid" ), T::Uuid },
        { QStringLiteral( "systemd" ), T::Uuid },
        { QStringLiteral( "literal-uninitialized" ), T::Uninitialized },
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

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

    const Calamares::System* system = Calamares::System::instance();

    // Clear existing files
    for ( const auto& entropy_file : m_entropy_files )
    {
        system->removeTargetFile( entropy_file );
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
    for ( const auto& entropy_file : m_entropy_files )
    {
        if ( !Calamares::System::instance()->createTargetParentDirs( entropy_file ) )
        {
            return Calamares::JobResult::error(
                QObject::tr( "Directory not found" ),
                QObject::tr( "Could not create new random file <pre>%1</pre>." ).arg( entropy_file ) );
        }
        auto r = MachineId::createEntropy( m_entropy_copy ? MachineId::EntropyGeneration::CopyFromHost
                                                          : MachineId::EntropyGeneration::New,
                                           root,
                                           entropy_file );
        if ( !r )
        {
            return r;
        }
    }
    if ( m_systemd )
    {
        if ( !system->createTargetParentDirs( target_systemd_machineid_file ) )
        {
            cWarning() << "Could not create systemd data-directory.";
        }
        auto r = MachineId::createSystemdMachineId( m_systemd_style, root, target_systemd_machineid_file );
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
    m_systemd = Calamares::getBool( map, "systemd", false );

    const auto style = Calamares::getString( map, "systemd-style", QString() );
    if ( !style.isEmpty() )
    {
        m_systemd_style = styleNames().find( style, MachineId::SystemdMachineIdStyle::Uuid );
    }

    m_dbus = Calamares::getBool( map, "dbus", false );
    if ( map.contains( "dbus-symlink" ) )
    {
        m_dbus_symlink = Calamares::getBool( map, "dbus-symlink", false );
    }
    else if ( map.contains( "symlink" ) )
    {
        m_dbus_symlink = Calamares::getBool( map, "symlink", false );
        cWarning() << "MachineId: configuration setting *symlink* is deprecated, use *dbus-symlink*.";
    }
    // else it's still false from the constructor

    // ignore it, though, if dbus is false
    m_dbus_symlink = m_dbus && m_dbus_symlink;

    m_entropy_copy = Calamares::getBool( map, "entropy-copy", false );
    m_entropy_files = Calamares::getStringList( map, "entropy-files" );
    if ( Calamares::getBool( map, "entropy", false ) )
    {
        cWarning() << "MachineId:: configuration setting *entropy* is deprecated, use *entropy-files* instead.";
        m_entropy_files.append( QStringLiteral( "/var/lib/urandom/random-seed" ) );
    }
    m_entropy_files.removeDuplicates();
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( MachineIdJobFactory, registerPlugin< MachineIdJob >(); )
