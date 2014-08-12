/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "ProcessJobModule.h"

#include "ProcessJob.h"

#include <QDir>

#include <yaml-cpp/yaml.h>

namespace Calamares {


Module::Type
ProcessJobModule::type() const
{
    return Job;
}


Module::Interface
ProcessJobModule::interface() const
{
    return Process;
}


void
ProcessJobModule::loadSelf()
{
    if ( m_loaded )
        return;

    m_job = Calamares::job_ptr( new ProcessJob( m_command,
                                                m_workingPath,
                                                m_runInChroot,
                                                m_secondsTimeout ) );
    m_loaded = true;
}


QList< job_ptr >
ProcessJobModule::jobs() const
{
    return QList< job_ptr >() << m_job;
}


void
ProcessJobModule::initFrom( const YAML::Node& node )
{
    Module::initFrom( node );
    QDir directory( location() );
    m_workingPath = directory.absolutePath();

    if ( node[ "command" ] )
    {
        m_command = QString::fromStdString( node[ "command" ].as< std::string >() );
    }

    m_secondsTimeout = 30;
    if ( node[ "timeout" ] )
    {
        m_secondsTimeout = node[ "timeout" ].as< int >();
    }

    m_runInChroot = false;
    if ( node[ "chroot" ] )
    {
        m_runInChroot = node[ "chroot" ].as< bool >();
    }
}


ProcessJobModule::ProcessJobModule()
    : Module()
{}


ProcessJobModule::~ProcessJobModule()
{}


} // namespace Calamares
