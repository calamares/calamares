/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "ModuleFactory.h"

#include "CalamaresConfig.h"
#include "CppJobModule.h"
#include "ProcessJobModule.h"
#include "ViewModule.h"

#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Yaml.h"

#ifdef WITH_PYTHON
#include "PythonJobModule.h"
#endif

#ifdef WITH_PYTHONQT
#include "PythonQtViewModule.h"
#endif

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>


namespace Calamares
{

Module*
moduleFromDescriptor( const Calamares::ModuleSystem::Descriptor& moduleDescriptor,
                      const QString& instanceId,
                      const QString& configFileName,
                      const QString& moduleDirectory )
{
    std::unique_ptr< Module > m;

    QString typeString = moduleDescriptor.value( "type" ).toString();
    QString intfString = moduleDescriptor.value( "interface" ).toString();

    if ( typeString.isEmpty() || intfString.isEmpty() )
    {
        cError() << "Bad module descriptor format" << instanceId;
        return nullptr;
    }
    if ( ( typeString == "view" ) || ( typeString == "viewmodule" ) )
    {
        if ( intfString == "qtplugin" )
        {
            m.reset( new ViewModule() );
        }
        else if ( intfString == "pythonqt" )
        {
#ifdef WITH_PYTHONQT
            m.reset( new PythonQtViewModule() );
#else
            cError() << "PythonQt view modules are not supported in this version of Calamares.";
#endif
        }
        else
        {
            cError() << "Bad interface" << intfString << "for module type" << typeString;
        }
    }
    else if ( typeString == "job" )
    {
        if ( intfString == "qtplugin" )
        {
            m.reset( new CppJobModule() );
        }
        else if ( intfString == "process" )
        {
            m.reset( new ProcessJobModule() );
        }
        else if ( intfString == "python" )
        {
#ifdef WITH_PYTHON
            m.reset( new PythonJobModule() );
#else
            cError() << "Python modules are not supported in this version of Calamares.";
#endif
        }
        else
        {
            cError() << "Bad interface" << intfString << "for module type" << typeString;
        }
    }
    else
    {
        cError() << "Bad module type" << typeString;
    }

    if ( !m )
    {
        cError() << "Bad module type (" << typeString << ") or interface string (" << intfString << ") for module "
                 << instanceId;
        return nullptr;
    }

    QDir moduleDir( moduleDirectory );
    if ( moduleDir.exists() && moduleDir.isReadable() )
    {
        m->m_directory = moduleDir.absolutePath();
    }
    else
    {
        cError() << "Bad module directory" << moduleDirectory << "for" << instanceId;
        return nullptr;
    }

    m->initFrom( moduleDescriptor, instanceId );
    if ( !m->m_key.isValid() )
    {
        cError() << "Module" << instanceId << "invalid ID";
        return nullptr;
    }

    m->initFrom( moduleDescriptor );
    if ( !configFileName.isEmpty() )
    {
        try
        {
            m->loadConfigurationFile( configFileName );
        }
        catch ( YAML::Exception& e )
        {
            cError() << "YAML parser error " << e.what();
            return nullptr;
        }
    }
    return m.release();
}


}  // namespace Calamares
