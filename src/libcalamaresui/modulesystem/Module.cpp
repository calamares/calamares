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

#include "ViewModule.h"
#include "utils/YamlUtils.h"
#include "utils/Logger.h"

#include <yaml-cpp/yaml.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>


// Example module.conf
/*
---
type:      "core"     #core or view
name:      "foo"      #the module name. must be unique and same as the parent directory
interface: "qtplugin" #can be: qtplugin, python, process, ...
requires:  []         #list of module names that must also be loaded. only applies to
                      #binary plugins! these are actual link-time dependencies, not
                      #conceptual dependencies for the setup procedure
*/

void
operator>>( const YAML::Node& node, Calamares::Module* m )
{
    m->m_name = QString::fromStdString( node[ "name" ].as< std::string >() );

    QString typeString = QString::fromStdString( node[ "type" ].as< std::string >() );
    if ( typeString == "core" )
    {
        m->m_type = Calamares::Module::Core;
    }
    else if ( typeString == "view" )
    {
        m->m_type = Calamares::Module::View;
        m->m_interface = Calamares::Module::QtPlugin;
    }

    if ( m->m_type != Calamares::Module::View )
    {
        QString interfaceString = QString::fromStdString( node[ "interface" ].as< std::string >() );
        if ( interfaceString == "qtplugin" )
        {
            m->m_interface = Calamares::Module::QtPlugin;
        }
        else if ( interfaceString == "python" )
        {
            m->m_interface = Calamares::Module::Python;
        }
        else if ( interfaceString == "process" )
        {
            m->m_interface = Calamares::Module::Process;
        }
    }

    if ( node[ "requires" ] && node[ "requires" ].IsSequence() )
    {
        node[ "requires" ] >> m->m_requiredModules;
    }

}

namespace Calamares
{

Module::~Module()
{}

Module*
Module::fromConfigFile( const QString& path )
{
    Module* m = nullptr;
    QFile metadataFile( path );
    if ( metadataFile.exists() && metadataFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = metadataFile.readAll();
        cDebug() << Q_FUNC_INFO << "module metadata file: " << ba;

        try
        {
            YAML::Node moduleDocument = YAML::Load( ba.constData() );
            if ( !moduleDocument.IsMap() )
            {
                cDebug() << Q_FUNC_INFO << "bad module metadata format"
                         << path;
                return nullptr;
            }

            m = new ViewModule();

            QFileInfo mfi( path );
            m->m_directory = mfi.absoluteDir().absolutePath();

            m->initFrom( moduleDocument );
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

QString
Module::name()
{
    return m_name;
}


QStringList
Module::requiredModules()
{
    return m_requiredModules;
}


QString
Module::location()
{
    return m_directory;
}


bool
Module::isLoaded()
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
