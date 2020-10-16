/* === This file is part of Calamares - <https://github.com/calamares> ===
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

    m_job = Calamares::job_ptr( new PythonJob( instanceKey(), m_scriptFileName, m_workingPath, m_configurationMap ) );
    m_loaded = true;
}


JobList
PythonJobModule::jobs() const
{
    return JobList() << m_job;
}


void
PythonJobModule::initFrom( const QVariantMap& moduleDescriptor )
{
    QDir directory( location() );
    m_workingPath = directory.absolutePath();

    if ( !moduleDescriptor.value( "script" ).toString().isEmpty() )
    {
        m_scriptFileName = moduleDescriptor.value( "script" ).toString();
    }
}


PythonJobModule::PythonJobModule()
    : Module()
{
}


PythonJobModule::~PythonJobModule() { }


}  // namespace Calamares
