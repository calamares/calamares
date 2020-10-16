/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
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

#include "CppJobModule.h"

#include "CppJob.h"
#include "utils/Logger.h"
#include "utils/PluginFactory.h"

#include <QDir>
#include <QPluginLoader>

namespace Calamares
{


Module::Type
CppJobModule::type() const
{
    return Module::Type::Job;
}


Module::Interface
CppJobModule::interface() const
{
    return Module::Interface::QtPlugin;
}


void
CppJobModule::loadSelf()
{
    if ( m_loader )
    {
        CalamaresPluginFactory* pf = qobject_cast< CalamaresPluginFactory* >( m_loader->instance() );
        if ( !pf )
        {
            cDebug() << "Could not load module:" << m_loader->errorString();
            return;
        }

        CppJob* cppJob = pf->create< Calamares::CppJob >();
        if ( !cppJob )
        {
            cDebug() << "Could not load module:" << m_loader->errorString();
            return;
        }
        //        cDebug() << "CppJobModule loading self for instance" << instanceKey()
        //                 << "\nCppJobModule at address" << this
        //                 << "\nCalamares::PluginFactory at address" << pf
        //                 << "\nCppJob at address" << cppJob;

        cppJob->setModuleInstanceKey( instanceKey() );
        cppJob->setConfigurationMap( m_configurationMap );
        m_job = Calamares::job_ptr( static_cast< Calamares::Job* >( cppJob ) );
        m_loaded = true;
        cDebug() << "CppJobModule" << instanceKey() << "loading complete.";
    }
}


JobList
CppJobModule::jobs() const
{
    return JobList() << m_job;
}


void
CppJobModule::initFrom( const QVariantMap& moduleDescriptor )
{
    QDir directory( location() );
    QString load;
    if ( !moduleDescriptor.value( "load" ).toString().isEmpty() )
    {
        load = moduleDescriptor.value( "load" ).toString();
        load = directory.absoluteFilePath( load );
    }
    // If a load path is not specified, we look for a plugin to load in the directory.
    if ( load.isEmpty() || !QLibrary::isLibrary( load ) )
    {
        const QStringList ls = directory.entryList( QStringList { "*.so" } );
        if ( !ls.isEmpty() )
        {
            for ( QString entry : ls )
            {
                entry = directory.absoluteFilePath( entry );
                if ( QLibrary::isLibrary( entry ) )
                {
                    load = entry;
                    break;
                }
            }
        }
    }

    m_loader = new QPluginLoader( load );
}

CppJobModule::CppJobModule()
    : Module()
    , m_loader( nullptr )
{
}

CppJobModule::~CppJobModule()
{
    delete m_loader;
}

}  // namespace Calamares
