/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "ViewModule.h"

#include "utils/PluginFactory.h"
#include "utils/Logger.h"
#include "viewpages/ViewStep.h"
#include "ViewManager.h"

#include <QDir>
#include <QPluginLoader>

namespace Calamares {


Module::Type
ViewModule::type() const
{
    return View;
}


Module::Interface
ViewModule::interface() const
{
    return QtPluginInterface;
}


void
ViewModule::loadSelf()
{
    if ( m_loader )
    {
        PluginFactory* pf = qobject_cast< PluginFactory* >( m_loader->instance() );
        if ( !pf )
        {
            cDebug() << Q_FUNC_INFO << "No factory:" << m_loader->errorString();
            return;
        }

        m_viewStep = pf->create< Calamares::ViewStep >();
        if ( !m_viewStep )
        {
            cDebug() << Q_FUNC_INFO << "create() failed" << m_loader->errorString();
            return;
        }
//        cDebug() << "ViewModule loading self for instance" << instanceKey()
//                 << "\nViewModule at address" << this
//                 << "\nCalamares::PluginFactory at address" << pf
//                 << "\nViewStep at address" << m_viewStep;

        m_viewStep->setModuleInstanceKey( instanceKey() );
        m_viewStep->setConfigurationMap( m_configurationMap );
        ViewManager::instance()->addViewStep( m_viewStep );
        m_loaded = true;
        cDebug() << "ViewModule" << instanceKey() << "loading complete.";
    }
}


QList< job_ptr >
ViewModule::jobs() const
{
    return m_viewStep->jobs();
}


void
ViewModule::initFrom( const QVariantMap& moduleDescriptor )
{
    Module::initFrom( moduleDescriptor );
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
        const QStringList ls = directory.entryList( QStringList{ "*.so" } );
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

} // namespace Calamares
