/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PythonJobModule.h"

#include "PythonJob.h"

#include <QDir>


namespace Calamares
{


Module::Type
PythonJobModule::type() const
{
    return Module::Type::Job;
}


Module::Interface
PythonJobModule::interface() const
{
    return Module::Interface::Python;
}


void
PythonJobModule::loadSelf()
{
    if ( m_loaded )
    {
        return;
    }

    m_job = Calamares::job_ptr( new PythonJob( m_scriptFileName, m_workingPath, m_configurationMap ) );
    m_loaded = true;
}


JobList
PythonJobModule::jobs() const
{
    return JobList() << m_job;
}


void
PythonJobModule::initFrom( const ModuleSystem::Descriptor& moduleDescriptor )
{
    QDir directory( location() );
    m_workingPath = directory.absolutePath();
    m_scriptFileName = moduleDescriptor.script();
}


PythonJobModule::PythonJobModule()
    : Module()
{
}


PythonJobModule::~PythonJobModule() {}


}  // namespace Calamares
