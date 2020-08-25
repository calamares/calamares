/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
CppJobModule::initFrom( const ModuleSystem::Descriptor& moduleDescriptor )
{
    QDir directory( location() );
    QString load = moduleDescriptor.load();
    if ( !load.isEmpty() )
    {
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
