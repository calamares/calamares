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

#include "ViewModule.h"

#include "utils/Logger.h"
#include "viewpages/ViewStep.h"
#include "ViewManager.h"

#include <yaml-cpp/yaml.h>

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
    return QtPlugin;
}


void
ViewModule::loadSelf()
{
    cDebug() << Q_FUNC_INFO << "for module" << name();
    if ( m_loader )
    {
        m_viewStep = qobject_cast< ViewStep* >( m_loader->instance() );
        m_viewStep->setConfigurationMap( m_configurationMap );
        if ( m_viewStep )
        {
            ViewManager::instance()->addViewStep( m_viewStep );
            m_loaded = true;
        }
        else
        {
            cDebug() << Q_FUNC_INFO << m_loader->errorString();
        }
    }
}


QList< job_ptr >
ViewModule::jobs() const
{
    return m_viewStep->jobs();
}


void
ViewModule::initFrom( const YAML::Node& node )
{
    Module::initFrom( node );
    QDir directory( location() );
    QString load;
    if ( node[ "load" ] )
    {
        load = QString::fromStdString( node[ "load" ].as< std::string >() );
        load = directory.absoluteFilePath( load );
    }
    // If a load path is not specified, we look for a plugin to load in the directory.
    if ( load.isEmpty() || !QLibrary::isLibrary( load ) )
    {
        QStringList ls = directory.entryList( QStringList() = { "*.so" } );
        if ( !ls.isEmpty() )
        {
            foreach ( QString entry, ls )
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
