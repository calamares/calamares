/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "ExecutionViewStep.h"
#include "Module.h"
#include "utils/Logger.h"
#include "utils/YamlUtils.h"
#include "Settings.h"
#include "ViewManager.h"

#include <yaml-cpp/yaml.h>

#include <QApplication>
#include <QDir>
#include <QTimer>

#define MODULE_CONFIG_FILENAME "module.desc"

namespace Calamares
{


ModuleManager* ModuleManager::s_instance = nullptr;


ModuleManager*
ModuleManager::instance()
{
    return s_instance;
}


ModuleManager::ModuleManager( const QStringList& paths, QObject* parent )
    : QObject( parent )
    , m_paths( paths )
{
    Q_ASSERT( !s_instance );
    s_instance = this;
}


ModuleManager::~ModuleManager()
{
    // The map is populated with Module::fromDescriptor(), which allocates on the heap.
    for ( auto moduleptr : m_loadedModulesByInstanceKey )
        delete moduleptr;
}


void
ModuleManager::init()
{
    QTimer::singleShot( 0, this, &ModuleManager::doInit );
}


void
ModuleManager::doInit()
{
    // We start from a list of paths in m_paths. Each of those is a directory that
    // might (should) contain Calamares modules of any type/interface.
    // For each modules search path (directory), it is expected that each module
    // lives in its own subdirectory. This subdirectory must have the same name as
    // the module name, and must contain a settings file named module.desc.
    // If at any time the module loading procedure finds something unexpected, it
    // silently skips to the next module or search path. --Teo 6/2014
    for ( const QString& path : m_paths )
    {
        QDir currentDir( path );
        if ( currentDir.exists() && currentDir.isReadable() )
        {
            const QStringList subdirs = currentDir.entryList( QDir::AllDirs | QDir::NoDotAndDotDot );
            for ( const QString& subdir : subdirs )
            {
                currentDir.setPath( path );
                bool success = currentDir.cd( subdir );
                if ( success )
                {
                    QFileInfo descriptorFileInfo( currentDir.absoluteFilePath( MODULE_CONFIG_FILENAME ) );
                    if ( ! ( descriptorFileInfo.exists() && descriptorFileInfo.isReadable() ) )
                    {
                        cDebug() << Q_FUNC_INFO << "unreadable file: "
                                 << descriptorFileInfo.absoluteFilePath();
                        continue;
                    }

                    bool ok = false;
                    QVariantMap moduleDescriptorMap = CalamaresUtils::loadYaml( descriptorFileInfo, &ok );
                    QString moduleName = ok ? moduleDescriptorMap.value( "name" ).toString() : QString();

                    if ( ok && ( moduleName == currentDir.dirName() ) &&
                            !m_availableDescriptorsByModuleName.contains( moduleName ) )
                    {
                        m_availableDescriptorsByModuleName.insert( moduleName, moduleDescriptorMap );
                        m_moduleDirectoriesByModuleName.insert( moduleName,
                                                                descriptorFileInfo.absoluteDir().absolutePath() );
                    }
                }
                else
                {
                    cWarning() << "Cannot cd into module directory "
                               << path << "/" << subdir;
                }
            }
        }
        else
            cDebug() << "ModuleManager bad search path" << path;
    }
    // At this point m_availableModules is filled with whatever was found in the
    // search paths.
    emit initDone();
}


QStringList
ModuleManager::loadedInstanceKeys()
{
    return m_loadedModulesByInstanceKey.keys();
}


QVariantMap
ModuleManager::moduleDescriptor( const QString& name )
{
    return m_availableDescriptorsByModuleName.value( name );
}

Module*
ModuleManager::moduleInstance( const QString& instanceKey )
{
    return m_loadedModulesByInstanceKey.value( instanceKey );
}


/**
 * @brief Search a list of instance descriptions for one matching @p module and @p id
 *
 * @return -1 on failure, otherwise index of the instance that matches.
 */
static int findCustomInstance( const Settings::InstanceDescriptionList& customInstances,
                               const QString& module,
                               const QString& id )
{
    for ( int i = 0; i < customInstances.count(); ++i )
    {
        const auto& thisInstance = customInstances[ i ];
        if ( thisInstance.value( "module" ) == module &&
                thisInstance.value( "id" ) == id )
            return i;
    }
    return -1;
}


void
ModuleManager::loadModules()
{
    QTimer::singleShot( 0, this, [ this ]()
    {
        QStringList failedModules = checkDependencies();
        Settings::InstanceDescriptionList customInstances =
            Settings::instance()->customModuleInstances();

        const auto modulesSequence = failedModules.isEmpty() ? Settings::instance()->modulesSequence() : Settings::ModuleSequence();
        for ( const auto& modulePhase : modulesSequence )
        {
            ModuleAction currentAction = modulePhase.first;

            foreach ( const QString& moduleEntry,
                      modulePhase.second )
            {
                QStringList moduleEntrySplit = moduleEntry.split( '@' );
                QString moduleName;
                QString instanceId;
                QString configFileName;
                if ( moduleEntrySplit.length() < 1 ||
                        moduleEntrySplit.length() > 2 )
                {
                    cError() << "Wrong module entry format for module" << moduleEntry;
                    failedModules.append( moduleEntry );
                    continue;
                }
                moduleName = moduleEntrySplit.first();
                instanceId = moduleEntrySplit.last();
                configFileName = QString( "%1.conf" ).arg( moduleName );

                if ( !m_availableDescriptorsByModuleName.contains( moduleName ) ||
                        m_availableDescriptorsByModuleName.value( moduleName ).isEmpty() )
                {
                    cError() << "Module" << moduleName << "not found in module search paths."
                             << Logger::DebugList( m_paths );
                    failedModules.append( moduleName );
                    continue;
                }

                if ( moduleName != instanceId ) //means this is a custom instance
                {
                    int found = findCustomInstance( customInstances, moduleName, instanceId );

                    if ( found > -1 )
                        configFileName = customInstances[ found ].value( "config" );
                    else //ought to be a custom instance, but cannot find instance entry
                    {
                        cError() << "Custom instance" << moduleEntry << "not found in custom instances section.";
                        failedModules.append( moduleEntry );
                        continue;
                    }
                }

                // So now we can assume that the module entry is at least valid,
                // that we have a descriptor on hand (and therefore that the
                // module exists), and that the instance is either default or
                // defined in the custom instances section.
                // We still don't know whether the config file for the entry
                // exists and is valid, but that's the only thing that could fail
                // from this point on. -- Teo 8/2015

                QString instanceKey = QString( "%1@%2" )
                                      .arg( moduleName )
                                      .arg( instanceId );

                Module* thisModule =
                    m_loadedModulesByInstanceKey.value( instanceKey, nullptr );
                if ( thisModule && !thisModule->isLoaded() )
                {
                    cError() << "Module" << instanceKey << "exists but not loaded.";
                    failedModules.append( instanceKey );
                    continue;
                }

                if ( thisModule && thisModule->isLoaded() )
                    cDebug() << "Module" << instanceKey << "already loaded.";
                else
                {
                    thisModule =
                        Module::fromDescriptor( m_availableDescriptorsByModuleName.value( moduleName ),
                                                instanceId,
                                                configFileName,
                                                m_moduleDirectoriesByModuleName.value( moduleName ) );
                    if ( !thisModule )
                    {
                        cError() << "Module" << instanceKey << "cannot be created from descriptor" << configFileName;
                        failedModules.append( instanceKey );
                        continue;
                    }

                    if ( !checkDependencies( *thisModule ) )
                    {
                        // Error message is already printed
                        failedModules.append( instanceKey );
                        continue;
                    }

                    // If it's a ViewModule, it also appends the ViewStep to the ViewManager.
                    thisModule->loadSelf();
                    m_loadedModulesByInstanceKey.insert( instanceKey, thisModule );
                    if ( !thisModule->isLoaded() )
                    {
                        cError() << "Module" << instanceKey << "loading FAILED.";
                        failedModules.append( instanceKey );
                        continue;
                    }
                }

                // At this point we most certainly have a pointer to a loaded module in
                // thisModule. We now need to enqueue jobs info into an EVS.
                if ( currentAction == Calamares::Exec )
                {
                    ExecutionViewStep* evs =
                        qobject_cast< ExecutionViewStep* >(
                            Calamares::ViewManager::instance()->viewSteps().last() );
                    if ( !evs ) // If the last step is not an EVS, we must create it.
                    {
                        evs = new ExecutionViewStep( ViewManager::instance() );
                        ViewManager::instance()->addViewStep( evs );
                    }

                    evs->appendJobModuleInstanceKey( instanceKey );
                }
            }
        }
        if ( !failedModules.isEmpty() )
        {
            ViewManager::instance()->onInitFailed( failedModules );
            emit modulesFailed( failedModules );
        }
        else
            emit modulesLoaded();
    } );
}


QStringList
ModuleManager::checkDependencies()
{
    QStringList failed;

    // This goes through the map of available modules, and deletes those whose
    // dependencies are not met, if any.
    forever
    {
        bool somethingWasRemovedBecauseOfUnmetDependencies = false;
        for ( auto it = m_availableDescriptorsByModuleName.begin();
                it != m_availableDescriptorsByModuleName.end(); ++it )
        {
            foreach ( const QString& depName,
                      it->value( "requiredModules" ).toStringList() )
            {
                if ( !m_availableDescriptorsByModuleName.contains( depName ) )
                {
                    QString moduleName = it->value( "name" ).toString();
                    somethingWasRemovedBecauseOfUnmetDependencies = true;
                    m_availableDescriptorsByModuleName.erase( it );
                    failed << moduleName;
                    cWarning() << "Module" << moduleName << "has unknown requirement" << depName;
                    break;
                }
            }
            if ( somethingWasRemovedBecauseOfUnmetDependencies )
                break;
        }
        if ( !somethingWasRemovedBecauseOfUnmetDependencies )
            break;
    }

    return failed;
}

bool
ModuleManager::checkDependencies( const Module& m )
{
    bool allRequirementsFound = true;
    QStringList requiredModules = m_availableDescriptorsByModuleName[ m.name() ].value( "requiredModules" ).toStringList();

    for ( const QString& required : requiredModules )
    {
        bool requirementFound = false;
        for( const Module* v : m_loadedModulesByInstanceKey )
            if ( required == v->name() )
            {
                requirementFound = true;
                break;
            }
        if ( !requirementFound )
        {
            cError() << "Module" << m.name() << "requires" << required << "before it in sequence.";
            allRequirementsFound = false;
        }
    }

    return allRequirementsFound;
}

}
