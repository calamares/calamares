/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "PythonQtViewModule.h"

#include "utils/Logger.h"
#include "viewpages/ViewStep.h"
#include "ViewManager.h"
#include "PythonQtConsoleViewStep.h"

#include <PythonQt.h>
#include <extensions/PythonQt_QtAll/PythonQt_QtAll.h>

#include <QDir>

namespace Calamares {


Module::Type
PythonQtViewModule::type() const
{
    return View;
}


Module::Interface
PythonQtViewModule::interface() const
{
    return PythonQtInterface;
}


void
PythonQtViewModule::loadSelf()
{
    if ( !m_scriptFileName.isEmpty() )
    {
        if ( PythonQt::self() == nullptr )
        {
            PythonQt::init();
            PythonQt_QtAll::init();
        }

        PythonQtObjectPtr cxt =
                PythonQt::self()->
                createModuleFromFile( name(),
                                      m_workingPath +
                                      QDir::separator() +
                                      m_scriptFileName );
        cDebug() << "Creating viewstep for script at"
                 << m_workingPath +
                    QDir::separator() +
                    m_scriptFileName;

        m_viewStep = new PythonQtConsoleViewStep( cxt );

//        m_viewStep = reinterpret_cast< ViewStep* >(
//                         PythonQt::self()->
//                         lookupObject( cxt,
//                                       "_calamares_module" ).object() );

//        if ( !m_viewStep )
//        {
//            cDebug() << Q_FUNC_INFO << m_loader->errorString();
//            return;
//        }


//        cDebug() << "PythonQtViewModule loading self for instance" << instanceKey()
//                 << "\nPythonQtViewModule at address" << this
//                 << "\nCalamares::PluginFactory at address" << pf
//                 << "\nViewStep at address" << m_viewStep;

        m_viewStep->setModuleInstanceKey( instanceKey() );
        m_viewStep->setConfigurationMap( m_configurationMap );
        ViewManager::instance()->addViewStep( m_viewStep );
        m_loaded = true;
        cDebug() << "PythonQtViewModule" << instanceKey() << "loading complete.";
    }
}


QList< job_ptr >
PythonQtViewModule::jobs() const
{
    return m_viewStep->jobs();
}


void
PythonQtViewModule::initFrom( const QVariantMap& moduleDescriptor )
{
    Module::initFrom( moduleDescriptor );
    QDir directory( location() );
    m_workingPath = directory.absolutePath();

    if ( !moduleDescriptor.value( "script" ).toString().isEmpty() )
    {
        m_scriptFileName = moduleDescriptor.value( "script" ).toString();
    }
}

PythonQtViewModule::PythonQtViewModule()
    : Module()
{
}

PythonQtViewModule::~PythonQtViewModule()
{
}

} // namespace Calamares
