/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    using Type = Calamares::ModuleSystem::Type;
    using Interface = Calamares::ModuleSystem::Interface;

    std::unique_ptr< Module > m;

    if ( !moduleDescriptor.isValid() )
    {
        cError() << "Bad module descriptor format" << instanceId;
        return nullptr;
    }
    if ( moduleDescriptor.type() == Type::View )
    {
        if ( moduleDescriptor.interface() == Interface::QtPlugin )
        {
            m.reset( new ViewModule() );
        }
        else
        {
            cError() << "Bad interface"
                     << Calamares::ModuleSystem::interfaceNames().find( moduleDescriptor.interface() )
                     << "for module type" << Calamares::ModuleSystem::typeNames().find( moduleDescriptor.type() );
        }
    }
    else if ( moduleDescriptor.type() == Type::Job )
    {
        if ( moduleDescriptor.interface() == Interface::QtPlugin )
        {
            m.reset( new CppJobModule() );
        }
        else if ( moduleDescriptor.interface() == Interface::Process )
        {
            m.reset( new ProcessJobModule() );
        }
        else if ( moduleDescriptor.interface() == Interface::Python )
        {
#ifdef WITH_PYTHON
            m.reset( new PythonJobModule() );
#else
            cError() << "Python modules are not supported in this version of Calamares.";
#endif
        }
        else
        {
            cError() << "Bad interface"
                     << Calamares::ModuleSystem::interfaceNames().find( moduleDescriptor.interface() )
                     << "for module type" << Calamares::ModuleSystem::typeNames().find( moduleDescriptor.type() );
        }
    }
    else
    {
        cError() << "Bad module type" << Calamares::ModuleSystem::typeNames().find( moduleDescriptor.type() );
    }

    if ( !m )
    {
        cError() << "Bad module type (" << Calamares::ModuleSystem::typeNames().find( moduleDescriptor.type() )
                 << ") or interface string ("
                 << Calamares::ModuleSystem::interfaceNames().find( moduleDescriptor.interface() ) << ") for module "
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
