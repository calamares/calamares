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

#include "ModuleManager.h"

#include "utils/Logger.h"

#include <yaml-cpp/yaml.h>

#include <QDir>
#include <QTimer>

#define MODULE_CONFIG_FILENAME "module.conf"

namespace Calamares
{

ModuleManager::ModuleManager( const QStringList& paths, QObject* parent )
    : QObject( parent )
    , m_paths( paths )
{
}

ModuleManager::~ModuleManager()
{
    foreach ( Module* m, m_availableModules )
    {
        delete m;
    }
}


void
ModuleManager::start()
{
    QTimer::singleShot( 0, this, SLOT( doWork() ) );
}


QStringList
ModuleManager::availableModules()
{
    return m_availableModules.keys();
}


Module*
ModuleManager::module( const QString& name )
{
    return m_availableModules.value( name );
}


void
ModuleManager::doWork()
{
    // We start from a list of paths in m_paths. Each of those is a directory that
    // might (should) contain Calamares modules of any type/interface.
    // For each modules search path (directory), it is expected that each module
    // lives in its own subdirectory. This subdirectory must have the same name as
    // the module name, and must contain a settings file named module.conf.
    // If at any time the module loading procedure finds something unexpected, it
    // silently skips to the next module or search path. --Teo 6/2014
    foreach ( const QString& path, m_paths )
    {
        QDir currentDir( path );
        if ( currentDir.exists() && currentDir.isReadable() )
        {
            QStringList subdirs = currentDir.entryList( QDir::AllDirs | QDir::NoDotAndDotDot );
            foreach ( const QString& subdir, subdirs )
            {
                currentDir.setPath( path );
                bool success = currentDir.cd( subdir );
                if ( success )
                {
                    QFileInfo metadataFileInfo( currentDir.absoluteFilePath( MODULE_CONFIG_FILENAME ) );
                    if ( ! ( metadataFileInfo.exists() && metadataFileInfo.isReadable() ) )
                    {
                        cDebug() << Q_FUNC_INFO << "unreadable file: "
                                 << metadataFileInfo.absoluteFilePath();
                        continue;
                    }

                    Module* moduleInfo = Module::fromConfigFile( metadataFileInfo.absoluteFilePath() );

                    if ( moduleInfo &&
                         ( moduleInfo->name() == currentDir.dirName() ) &&
                         ( !m_availableModules.contains( moduleInfo->name() ) ) )
                    {
                        m_availableModules.insert( moduleInfo->name(), moduleInfo );
                    }
                }
                else
                {
                    cDebug() << Q_FUNC_INFO << "cannot cd into module directory "
                             << path << "/" << subdir;
                }
            }
        }
        else
        {
            cDebug() << Q_FUNC_INFO << "bad search path " << path;
        }
    }
    // At this point m_availableModules is filled with whatever was found in the
    // search paths.
    checkDependencies();
    emit ready();
}


void
ModuleManager::checkDependencies()
{
    // This goes through the map of available modules, and deletes those whose
    // dependencies are not met, if any.
    bool somethingWasRemovedBecauseOfUnmetDependencies = false;
    forever
    {
        for ( auto it = m_availableModules.begin();
              it != m_availableModules.end(); ++it )
        {
            foreach ( QString depName, (*it)->requiredModules() )
            {
                if ( !m_availableModules.contains( depName ) )
                {
                    somethingWasRemovedBecauseOfUnmetDependencies = true;
                    m_availableModules.erase( it );
                    break;
                }
            }
            if ( somethingWasRemovedBecauseOfUnmetDependencies )
                break;
        }
        if ( !somethingWasRemovedBecauseOfUnmetDependencies )
            break;
    }
}

}
