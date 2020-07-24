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

#include "ViewManager.h"

#include "Settings.h"
#include "modulesystem/Module.h"
#include "modulesystem/RequirementsChecker.h"
#include "modulesystem/RequirementsModel.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"
#include "viewpages/ExecutionViewStep.h"

#include <QApplication>
#include <QDir>
#include <QTimer>

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
    , m_requirementsModel( new RequirementsModel( this ) )
{
    Q_ASSERT( !s_instance );
    s_instance = this;
}


ModuleManager::~ModuleManager()
{
    // The map is populated with Module::fromDescriptor(), which allocates on the heap.
    for ( auto moduleptr : m_loadedModulesByInstanceKey )
    {
        delete moduleptr;
    }
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
                    static const char bad_descriptor[] = "ModuleManager potential module descriptor is bad";
                    QFileInfo descriptorFileInfo( currentDir.absoluteFilePath( QLatin1String( "module.desc" ) ) );
                    if ( !descriptorFileInfo.exists() )
                    {
                        cDebug() << bad_descriptor << descriptorFileInfo.absoluteFilePath() << "(missing)";
                        continue;
                    }
                    if ( !descriptorFileInfo.isReadable() )
                    {
                        cDebug() << bad_descriptor << descriptorFileInfo.absoluteFilePath() << "(unreadable)";
                        continue;
                    }

                    bool ok = false;
                    QVariantMap moduleDescriptorMap = CalamaresUtils::loadYaml( descriptorFileInfo, &ok );
                    QString moduleName = ok ? moduleDescriptorMap.value( "name" ).toString() : QString();

                    if ( ok && !moduleName.isEmpty() && ( moduleName == currentDir.dirName() )
                         && !m_availableDescriptorsByModuleName.contains( moduleName ) )
                    {
                        m_availableDescriptorsByModuleName.insert( moduleName, moduleDescriptorMap );
                        m_moduleDirectoriesByModuleName.insert( moduleName,
                                                                descriptorFileInfo.absoluteDir().absolutePath() );
                    }
                }
                else
                {
                    cWarning() << "ModuleManager module directory is not accessible:" << path << "/" << subdir;
                }
            }
        }
        else
        {
            cDebug() << "ModuleManager module search path does not exist:" << path;
        }
    }
    // At this point m_availableDescriptorsByModuleName is filled with
    // the modules that were found in the search paths.
    cDebug() << "Found" << m_availableDescriptorsByModuleName.count() << "modules"
             << m_moduleDirectoriesByModuleName.count() << "names";
    emit initDone();
}


QList< ModuleSystem::InstanceKey >
ModuleManager::loadedInstanceKeys()
{
    return m_loadedModulesByInstanceKey.keys();
}


Calamares::ModuleSystem::Descriptor
ModuleManager::moduleDescriptor( const QString& name )
{
    return m_availableDescriptorsByModuleName.value( name );
}

Module*
ModuleManager::moduleInstance( const QString& instanceKey )
{
    return m_loadedModulesByInstanceKey.value( ModuleSystem::InstanceKey::fromString( instanceKey ) );
}


/**
 * @brief Search a list of instance descriptions for one matching @p module and @p id
 *
 * @return -1 on failure, otherwise index of the instance that matches.
 */
static int
findCustomInstance( const Settings::InstanceDescriptionList& customInstances, const ModuleSystem::InstanceKey& m )
{
    for ( int i = 0; i < customInstances.count(); ++i )
    {
        const auto& thisInstance = customInstances[ i ];
        if ( thisInstance.module == m.module() && thisInstance.id == m.id() )
        {
            return i;
        }
    }
    return -1;
}

/** @brief Returns the config file name for the fiven @p instanceKey
 *
 * Custom instances have custom config files, non-custom ones
 * have a <modulename>.conf file. Returns an empty QString on
 * errors.
 */
static QString
getConfigFileName( const Settings::InstanceDescriptionList& customInstances,
                   const ModuleSystem::InstanceKey& instanceKey,
                   const ModuleSystem::Descriptor& descriptor )
{
    if ( instanceKey.isCustom() )
    {
        int found = findCustomInstance( customInstances, instanceKey );

        if ( found < 0 )
        {
            // This should already have been checked and failed the module already
            return QString();
        }

        return customInstances[ found ].config;
    }
    else
    {
        if ( descriptor.value( "noconfig", false ).toBool() )
        {
            // Explicitly set to no-configuration. This doesn't apply
            // to custom instances (above) since the only reason to
            // **have** a custom instance is to specify a different
            // config file for more than one module.
            return QString();
        }
        return QString( "%1.conf" ).arg( instanceKey.module() );
    }
}

void
ModuleManager::loadModules()
{
    if ( checkDependencies() )
    {
        cWarning() << "Some installed modules have unmet dependencies.";
    }
    Settings::InstanceDescriptionList customInstances = Settings::instance()->customModuleInstances();

    QStringList failedModules;
    const auto modulesSequence = Settings::instance()->modulesSequence();
    for ( const auto& modulePhase : modulesSequence )
    {
        ModuleSystem::Action currentAction = modulePhase.first;

        foreach ( const QString& moduleEntry, modulePhase.second )
        {
            auto instanceKey = ModuleSystem::InstanceKey::fromString( moduleEntry );
            if ( !instanceKey.isValid() )
            {
                cError() << "Wrong module entry format for module" << moduleEntry;
                failedModules.append( moduleEntry );
                continue;
            }
            if ( instanceKey.isCustom() )
            {
                int found = findCustomInstance( customInstances, instanceKey );
                if ( found < 0 )
                {
                    cError() << "Custom instance" << moduleEntry << "not found in custom instances section.";
                    failedModules.append( moduleEntry );
                    continue;
                }
            }

            ModuleSystem::Descriptor descriptor
                = m_availableDescriptorsByModuleName.value( instanceKey.module(), ModuleSystem::Descriptor() );
            if ( descriptor.isEmpty() )
            {
                cError() << "Module" << instanceKey.toString() << "not found in module search paths."
                         << Logger::DebugList( m_paths );
                failedModules.append( instanceKey.toString() );
                continue;
            }

            QString configFileName = getConfigFileName( customInstances, instanceKey, descriptor );

            // So now we can assume that the module entry is at least valid,
            // that we have a descriptor on hand (and therefore that the
            // module exists), and that the instance is either default or
            // defined in the custom instances section.
            // We still don't know whether the config file for the entry
            // exists and is valid, but that's the only thing that could fail
            // from this point on. -- Teo 8/2015
            Module* thisModule = m_loadedModulesByInstanceKey.value( instanceKey, nullptr );
            if ( thisModule )
            {
                if ( thisModule->isLoaded() )
                {
                    // It's been listed before, don't bother loading again.
                    // This can happen for a module listed twice (e.g. with custom instances)
                    cDebug() << "Module" << instanceKey.toString() << "already loaded.";
                }
                else
                {
                    // An attempt was made, earlier, and that failed.
                    // This can happen for a module listed twice (e.g. with custom instances)
                    cError() << "Module" << instanceKey.toString() << "exists but not loaded.";
                    failedModules.append( instanceKey.toString() );
                    continue;
                }
            }
            else
            {
                thisModule
                    = Calamares::moduleFromDescriptor( descriptor,
                                                       instanceKey.id(),
                                                       configFileName,
                                                       m_moduleDirectoriesByModuleName.value( instanceKey.module() ) );
                if ( !thisModule )
                {
                    cError() << "Module" << instanceKey.toString() << "cannot be created from descriptor"
                             << configFileName;
                    failedModules.append( instanceKey.toString() );
                    continue;
                }

                if ( !addModule( thisModule ) )
                {
                    // Error message is already printed
                    failedModules.append( instanceKey.toString() );
                    continue;
                }
            }

            // At this point we most certainly have a pointer to a loaded module in
            // thisModule. We now need to enqueue jobs info into an EVS.
            if ( currentAction == ModuleSystem::Action::Exec )
            {
                ExecutionViewStep* evs
                    = qobject_cast< ExecutionViewStep* >( Calamares::ViewManager::instance()->viewSteps().last() );
                if ( !evs )  // If the last step is not an EVS, we must create it.
                {
                    evs = new ExecutionViewStep( ViewManager::instance() );
                    ViewManager::instance()->addViewStep( evs );
                }

                evs->appendJobModuleInstanceKey( instanceKey.toString() );
            }
        }
    }
    if ( !failedModules.isEmpty() )
    {
        ViewManager::instance()->onInitFailed( failedModules );
        emit modulesFailed( failedModules );
    }
    else
    {
        emit modulesLoaded();
    }
}

bool
ModuleManager::addModule( Module *module )
{
    if ( !module )
    {
        return false;
    }
    if ( !module->instanceKey().isValid() )
    {
        cWarning() << "Module" << module->location() << Logger::Pointer(module) << "has invalid instance key.";
        return false;
    }
    if ( !checkModuleDependencies( *module ) )
    {
        return false;
    }

    if ( !module->isLoaded() )
    {
        module->loadSelf();
    }

    // Even if the load failed, we keep the module, so that if it tried to
    // get loaded **again**, we already know.
    m_loadedModulesByInstanceKey.insert( module->instanceKey(), module );
    if ( !module->isLoaded() )
    {
        cError() << "Module" << module->instanceKey().toString() << "loading FAILED.";
        return false;
    }

    return true;
}

void
ModuleManager::checkRequirements()
{
    cDebug() << "Checking module requirements ..";

    QVector< Module* > modules( m_loadedModulesByInstanceKey.count() );
    int count = 0;
    for ( const auto& module : m_loadedModulesByInstanceKey )
    {
        modules[ count++ ] = module;
    }

    RequirementsChecker* rq = new RequirementsChecker( modules, m_requirementsModel, this );
    connect( rq, &RequirementsChecker::done, rq, &RequirementsChecker::deleteLater );
    connect( rq, &RequirementsChecker::done, this, [=](){ this->requirementsComplete( m_requirementsModel->satisfiedMandatory() ); } );

    QTimer::singleShot( 0, rq, &RequirementsChecker::run );
}

static QStringList
missingRequiredModules( const QStringList& required, const QMap< QString, QVariantMap >& available )
{
    QStringList l;
    for ( const QString& depName : required )
    {
        if ( !available.contains( depName ) )
        {
            l.append( depName );
        }
    }

    return l;
}

size_t
ModuleManager::checkDependencies()
{
    size_t numberRemoved = 0;
    bool somethingWasRemovedBecauseOfUnmetDependencies = false;

    // This goes through the map of available modules, and deletes those whose
    // dependencies are not met, if any.
    do
    {
        somethingWasRemovedBecauseOfUnmetDependencies = false;
        for ( auto it = m_availableDescriptorsByModuleName.begin(); it != m_availableDescriptorsByModuleName.end();
              ++it )
        {
            QStringList unmet = missingRequiredModules( it->value( "requiredModules" ).toStringList(),
                                                        m_availableDescriptorsByModuleName );

            if ( unmet.count() > 0 )
            {
                QString moduleName = it->value( "name" ).toString();
                somethingWasRemovedBecauseOfUnmetDependencies = true;
                m_availableDescriptorsByModuleName.erase( it );
                numberRemoved++;
                cWarning() << "Module" << moduleName << "requires missing modules" << Logger::DebugList( unmet );
                break;
            }
        }
    } while ( somethingWasRemovedBecauseOfUnmetDependencies );

    return numberRemoved;
}

bool
ModuleManager::checkModuleDependencies( const Module& m )
{
    if ( !m_availableDescriptorsByModuleName.contains( m.name() ) )
    {
        cWarning() << "Module" << m.name() << "loaded externally, no dependency information.";
        return true;
    }

    bool allRequirementsFound = true;
    QStringList requiredModules
        = m_availableDescriptorsByModuleName[ m.name() ].value( "requiredModules" ).toStringList();

    for ( const QString& required : requiredModules )
    {
        bool requirementFound = false;
        for ( const Module* v : m_loadedModulesByInstanceKey )
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

}  // namespace Calamares
