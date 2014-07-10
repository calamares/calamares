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

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "utils/YamlUtils.h"

#include <QDir>
#include <QFile>

#include <yaml-cpp/yaml.h>


namespace Calamares
{

Settings* Settings::s_instance = nullptr;

Settings*
Settings::instance()
{
    return s_instance;
}


Settings::Settings( bool debugMode, QObject* parent )
    : QObject( parent )
{
    QFileInfo settingsFile( CalamaresUtils::appDataDir().absoluteFilePath( "settings.conf" ) );
    if ( debugMode )
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
                {
                    // If we're running in debug mode, we assume we might also be
                    // running from the build dir, so we add a maximum priority
                    // module search path in the build dir.
                    if ( debugMode )
                    {
                        QString buildDirModules = QDir::current().absolutePath() +
                                                  QDir::separator() + "src" +
                                                  QDir::separator() + "modules";
                        if ( QDir( buildDirModules ).exists() )
                            m_modulesSearchPaths.append( buildDirModules );
                    }

                    // Install path is set in CalamaresAddPlugin.cmake
                    m_modulesSearchPaths.append( CalamaresUtils::systemLibDir().absolutePath() +
                                                 QDir::separator() + "calamares" +
                                                 QDir::separator() + "modules" );
                }
                else
                {
                    QDir path( rawPaths[ i ] );
                    if ( path.exists() && path.isReadable() )
                        m_modulesSearchPaths.append( path.absolutePath() );
                }
            }

            config[ "prepare" ] >> m_modulesPrepareList;
            config[ "install" ] >> m_modulesInstallList;
            config[ "postinstall" ] >> m_modulesPostInstallList;
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
Settings::modulesPrepare()
{
    return m_modulesPrepareList;
}


QStringList
Settings::modulesInstall()
{
    return m_modulesInstallList;
}


QStringList
Settings::modulesPostInstall()
{
    return m_modulesPostInstallList;
}


}
