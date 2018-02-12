/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "Module.h"

#include "ProcessJobModule.h"
#include "CppJobModule.h"
#include "ViewModule.h"
#include "utils/CalamaresUtils.h"
#include "utils/YamlUtils.h"
#include "utils/Logger.h"
#include "Settings.h"
#include "CalamaresConfig.h"

#ifdef WITH_PYTHON
#include "PythonJobModule.h"
#endif

#ifdef WITH_PYTHONQT
#include "PythonQtViewModule.h"
#endif

#include <yaml-cpp/yaml.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>


// Example module.desc
/*
---
type:      "view"      #job or view
name:      "foo"      #the module name. must be unique and same as the parent directory
interface: "qtplugin" #can be: qtplugin, python, process, ...
*/

namespace Calamares
{

Module::~Module()
{}

Module*
Module::fromDescriptor( const QVariantMap& moduleDescriptor,
                        const QString& instanceId,
                        const QString& configFileName,
                        const QString& moduleDirectory )
{
    Module* m = nullptr;

    QString typeString = moduleDescriptor.value( "type" ).toString();
    QString intfString = moduleDescriptor.value( "interface" ).toString();

    if ( typeString.isEmpty() ||
         intfString.isEmpty() )
    {
        cLog() << Q_FUNC_INFO << "bad module descriptor format"
               << instanceId;
        return nullptr;
    }
    if ( ( typeString == "view" ) || ( typeString == "viewmodule" ) )
    {
        if ( intfString == "qtplugin" )
        {
            m = new ViewModule();
        }
        else if ( intfString == "pythonqt" )
        {
#ifdef WITH_PYTHONQT
            m = new PythonQtViewModule();
#else
            cLog() << "PythonQt modules are not supported in this version of Calamares.";
#endif
        }
        else
            cLog() << "Bad interface" << intfString << "for module type" << typeString;
    }
    else if ( typeString == "job" )
    {
        if ( intfString == "qtplugin" )
        {
            m = new CppJobModule();
        }
        else if ( intfString == "process" )
        {
            m = new ProcessJobModule();
        }
        else if ( intfString == "python" )
        {
#ifdef WITH_PYTHON
            m = new PythonJobModule();
#else
            cLog() << "Python modules are not supported in this version of Calamares.";
#endif
        }
        else
            cLog() << "Bad interface" << intfString << "for module type" << typeString;
    }
    else
        cLog() << "Bad module type" << typeString;

    if ( !m )
    {
        cLog() << "Bad module type (" << typeString
            << ") or interface string (" << intfString
            << ") for module " << instanceId;
        return nullptr;
    }

    QDir moduleDir( moduleDirectory );
    if ( moduleDir.exists() && moduleDir.isReadable() )
        m->m_directory = moduleDir.absolutePath();
    else
    {
        cLog() << Q_FUNC_INFO << "bad module directory"
               << instanceId;
        delete m;
        return nullptr;
    }

    m->m_instanceId = instanceId;

    m->initFrom( moduleDescriptor );
    try
    {
        m->loadConfigurationFile( configFileName );
    }
    catch ( YAML::Exception& e )
    {
        cWarning() << "YAML parser error " << e.what();
        delete m;
        return nullptr;
    }
    return m;
}


void
Module::loadConfigurationFile( const QString& configFileName ) //throws YAML::Exception
{
    QStringList configFilesByPriority;

    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        configFilesByPriority.append(
            CalamaresUtils::appDataDir().absoluteFilePath(
                QString( "modules/%1" ).arg( configFileName ) ) );
    }
    else
    {
        if ( Settings::instance()->debugMode() )
        {
            configFilesByPriority.append(
                QDir( QDir::currentPath() ).absoluteFilePath(
                    QString( "src/modules/%1/%2" ).arg( m_name )
                                                  .arg( configFileName ) ) );
        }

        configFilesByPriority.append(
            QString( "/etc/calamares/modules/%1" ).arg( configFileName ) );
        configFilesByPriority.append(
            CalamaresUtils::appDataDir().absoluteFilePath(
                QString( "modules/%2" ).arg( configFileName ) ) );
    }

    foreach ( const QString& path, configFilesByPriority )
    {
        QFile configFile( path );
        if ( configFile.exists() && configFile.open( QFile::ReadOnly | QFile::Text ) )
        {
            QByteArray ba = configFile.readAll();

            YAML::Node doc = YAML::Load( ba.constData() );
            if ( doc.IsNull() )
            {
                // Special case: empty config files are valid,
                // but aren't a map.
                return;
            }
            if ( !doc.IsMap() )
            {
                cWarning() << "Bad module configuration format" << path;
                return;
            }

            m_configurationMap = CalamaresUtils::yamlMapToVariant( doc ).toMap();
            return;
        }
        else
            continue;
    }
}


QString
Module::name() const
{
    return m_name;
}


QString
Module::instanceId() const
{
    return m_instanceId;
}


QString
Module::instanceKey() const
{
    return QString( "%1@%2" ).arg( m_name )
                             .arg( m_instanceId );
}


QStringList
Module::requiredModules() const
{
    return m_requiredModules;
}


QString
Module::location() const
{
    return m_directory;
}


QString
Module::typeString() const
{
    switch ( type() )
    {
    case Job:
        return "Job Module";
    case View:
        return "View Module";
    }
    return QString();
}


QString
Module::interfaceString() const
{
    switch ( interface() )
    {
    case ProcessInterface:
        return "External process";
    case PythonInterface:
        return "Python (Boost.Python)";
    case PythonQtInterface:
        return "Python (experimental)";
    case QtPluginInterface:
        return "Qt Plugin";
    }
    return QString();
}


bool
Module::isLoaded() const
{
    return m_loaded;
}


QVariantMap
Module::configurationMap()
{
    return m_configurationMap;
}


Module::Module()
    : m_loaded( false )
{}


void
Module::initFrom( const QVariantMap& moduleDescriptor )
{
    m_name = moduleDescriptor.value( "name" ).toString();
}

} //ns
