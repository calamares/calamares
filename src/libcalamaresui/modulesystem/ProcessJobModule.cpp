/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ProcessJobModule.h"

#include "ProcessJob.h"

#include <QDir>

namespace Calamares
{


Module::Type
ProcessJobModule::type() const
{
    return Module::Type::Job;
}


Module::Interface
ProcessJobModule::interface() const
{
    return Module::Interface::Process;
}


void
ProcessJobModule::loadSelf()
{
    if ( m_loaded )
    {
        return;
    }

    m_job = job_ptr( new ProcessJob( m_command, m_workingPath, m_runInChroot, m_secondsTimeout ) );
    m_loaded = true;
}


JobList
ProcessJobModule::jobs() const
{
    return JobList() << m_job;
}


void
ProcessJobModule::initFrom( const ModuleSystem::Descriptor& moduleDescriptor )
{
    QDir directory( location() );
    m_workingPath = directory.absolutePath();

    m_command = moduleDescriptor.command();
    m_secondsTimeout = std::chrono::seconds( moduleDescriptor.timeout() );
    m_runInChroot = moduleDescriptor.chroot();
}


ProcessJobModule::ProcessJobModule()
    : Module()
    , m_secondsTimeout( std::chrono::seconds( 30 ) )
    , m_runInChroot( false )
{
}


ProcessJobModule::~ProcessJobModule() {}


}  // namespace Calamares
