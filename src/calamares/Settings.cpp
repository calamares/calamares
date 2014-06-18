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

#include "Settings.h"

#include "CalamaresApplication.h"
#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "YamlUtils.h"

#include <QDir>
#include <QFile>

#include <yaml-cpp/yaml.h>


namespace Calamares
{

Settings* Settings::s_instance = 0;

Settings*
Settings::instance()
{
    return s_instance;
}


Settings::Settings( QObject* parent )
    : QObject( parent )
{
    QFileInfo settingsFile( CalamaresUtils::appDataDir().absoluteFilePath( "settings.conf" ) );
    if ( APP->isDebug() )
    {
        QFileInfo localFile( QDir( QDir::currentPath() ).absoluteFilePath( "settings.conf" ) );
        if ( localFile.exists() && localFile.isReadable() )
            settingsFile.setFile( localFile.absoluteFilePath() );
    }
    QFile file( settingsFile.absoluteFilePath() );

    if ( file.exists() && file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = file.readAll();
        cDebug() << ba;

        try
        {
            YAML::Node config = YAML::Load( ba.constData() );
            Q_ASSERT( config.IsMap() );

            QStringList rawPaths;
            config[ "modules-search" ] >> rawPaths;
            for ( int i = 0; i < rawPaths.length(); ++i )
            {
                if ( rawPaths[ i ] == "local" )
                    m_modulesSearchPaths.append( CalamaresUtils::appDataDir().absolutePath() + QDir::separator() + "modules" );
                else
                {
                    QDir path( rawPaths[ i ] );
                    if ( path.exists() && path.isReadable() )
                        m_modulesSearchPaths.append( path.absolutePath() );
                }
            }

            config[ "modules-prepare" ] >> m_viewModulesPrepareList;
            config[ "modules-postinstall" ] >> m_viewModulesPostInstallList;
        }
        catch ( YAML::Exception& e )
        {
            cDebug() << "WARNING: YAML parser error " << e.what();
        }
    }
    else
    {
        cDebug() << "WARNING: Cannot read " << file.fileName();
    }

    s_instance = this;
}


QStringList
Settings::modulesSearchPaths()
{
    return m_modulesSearchPaths;
}


QStringList
Settings::viewModulesPrepare()
{
    return m_viewModulesPrepareList;
}


QStringList
Settings::viewModulesPostInstall()
{
    return m_viewModulesPostInstallList;
}


}
