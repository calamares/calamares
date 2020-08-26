/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ViewModule.h"

#include "ViewManager.h"
#include "utils/Logger.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QDir>
#include <QPluginLoader>

namespace Calamares
{


Module::Type
ViewModule::type() const
{
    return Module::Type::View;
}


Module::Interface
ViewModule::interface() const
{
    return Module::Interface::QtPlugin;
}


void
ViewModule::loadSelf()
{
    if ( m_loader )
    {
        CalamaresPluginFactory* pf = qobject_cast< CalamaresPluginFactory* >( m_loader->instance() );
        if ( !pf )
        {
            cWarning() << "No factory:" << m_loader->errorString();
            return;
        }

        m_viewStep = pf->create< Calamares::ViewStep >();
        if ( !m_viewStep )
        {
            cWarning() << "create() failed" << m_loader->errorString();
            return;
        }
    }

    // If any method created the view step, use it now.
    if ( m_viewStep )
    {
        m_viewStep->setModuleInstanceKey( instanceKey() );
        m_viewStep->setConfigurationMap( m_configurationMap );
        ViewManager::instance()->addViewStep( m_viewStep );
        m_loaded = true;
        cDebug() << "ViewModule" << instanceKey() << "loading complete.";
    }
    else
    {
        cWarning() << "No view step was created";
    }
}


JobList
ViewModule::jobs() const
{
    return m_viewStep->jobs();
}


void
ViewModule::initFrom( const ModuleSystem::Descriptor& moduleDescriptor )
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

ViewModule::ViewModule()
    : Module()
    , m_loader( nullptr )
{
}

ViewModule::~ViewModule()
{
    delete m_loader;
}

RequirementsList
ViewModule::checkRequirements()
{
    return m_viewStep->checkRequirements();
}

}  // namespace Calamares
