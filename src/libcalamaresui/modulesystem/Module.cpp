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

#include "Module.h"

#include "ProcessJobModule.h"
#include "ViewModule.h"
#include "utils/CalamaresUtils.h"
#include "utils/YamlUtils.h"
#include "utils/Logger.h"
#include "Settings.h"
#include "CalamaresConfig.h"

#ifdef WITH_PYTHON
#include "PythonJobModule.h"
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

void
operator>>( const YAML::Node& node, Calamares::Module* m )
{
    m->m_name = QString::fromStdString( node[ "name" ].as< std::string >() );
}

namespace Calamares
{

Module::~Module()
{}

Module*
Module::fromDescriptorFile( const QString& path )
{
    Module* m = nullptr;
    QFile descriptorFile( path );
    if ( descriptorFile.exists() && descriptorFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = descriptorFile.readAll();
        cDebug() << Q_FUNC_INFO << "module descriptor file"
                 << path << ":\n" << ba;

        try
        {
            YAML::Node doc = YAML::Load( ba.constData() );
            if ( !doc.IsMap() )
            {
                cDebug() << Q_FUNC_INFO << "bad module descriptor format"
                         << path;
                return nullptr;
            }

            if ( !doc[ "type" ] ||
                 !doc[ "interface" ] )
            {
                cDebug() << Q_FUNC_INFO << "bad module descriptor format"
                         << path;
                return nullptr;
            }

            QString typeString = QString::fromStdString( doc[ "type" ].as< std::string >() );
            QString intfString = QString::fromStdString( doc[ "interface" ].as< std::string >() );

            if ( typeString == "view" && intfString == "qtplugin" )
            {
                m = new ViewModule();
            }
            else if ( typeString == "job" )
            {
                if ( intfString == "process" )
                {
                    m = new ProcessJobModule();
                }
#ifdef WITH_PYTHON
                else if ( intfString == "python" )
                {
                    m = new PythonJobModule();
                }
#endif
            }

            if ( !m )
            {
                cDebug() << Q_FUNC_INFO << "bad module type or interface string"
                         << path << typeString << intfString;
                return nullptr;
            }

            QFileInfo mfi( path );
            m->m_directory = mfi.absoluteDir().absolutePath();

            m->loadConfigurationFile();

            m->initFrom( doc );
            return m;
        }
        catch ( YAML::Exception& e )
        {
            cDebug() << "WARNING: YAML parser error " << e.what();
            delete m;
            return nullptr;
        }
    }

    return nullptr;
}


void
Module::loadConfigurationFile() //throws YAML::Exception
{
    QStringList configFilesByPriority;
    configFilesByPriority.append(
        QString( "/etc/calamares/modules/%1.conf" ).arg( m_name ) );
    configFilesByPriority.append(
        CalamaresUtils::appDataDir().absoluteFilePath(
            QString( "modules/%1.conf" ).arg( m_name ) ) );

    if ( Settings::instance()->debugMode() )
    {
        configFilesByPriority.append(
            QDir( QDir::currentPath() ).absoluteFilePath(
                QString( "src/modules/%1/%1.conf" ).arg( m_name ) ) );
    }

    foreach ( const QString& path, configFilesByPriority )
    {
        QFile configFile( path );
        if ( configFile.exists() && configFile.open( QFile::ReadOnly | QFile::Text ) )
        {
            QByteArray ba = configFile.readAll();
            cDebug() << Q_FUNC_INFO << "module configuration file"
                     << path << ":\n" << ba;

            YAML::Node doc = YAML::Load( ba.constData() );
            if ( !doc.IsMap() )
            {
                cDebug() << Q_FUNC_INFO << "bad module configuration format"
                         << path;
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


bool
Module::isLoaded() const
{
    return m_loaded;
}


Module::Module()
    : m_loaded( false )
{}


void
Module::initFrom( const YAML::Node& node )
{
    node >> this;
}

} //ns
