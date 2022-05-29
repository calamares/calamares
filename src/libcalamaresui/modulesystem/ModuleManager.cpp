/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    Logger::Once deb;
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
                        cDebug() << deb << bad_descriptor << descriptorFileInfo.absoluteFilePath() << "(missing)";
                        continue;
                    }
                    if ( !descriptorFileInfo.isReadable() )
                    {
                        cDebug() << deb << bad_descriptor << descriptorFileInfo.absoluteFilePath() << "(unreadable)";
                        continue;
                    }

                    bool ok = false;
                    QVariantMap moduleDescriptorMap = CalamaresUtils::loadYaml( descriptorFileInfo, &ok );
                    QString moduleName = ok ? moduleDescriptorMap.value( "name" ).toString() : QString();

                    if ( ok && !moduleName.isEmpty() && ( moduleName == currentDir.dirName() )
                         && !m_availableDescriptorsByModuleName.contains( moduleName ) )
                    {
                        auto descriptor = Calamares::ModuleSystem::Descriptor::fromDescriptorData(
                            moduleDescriptorMap, descriptorFileInfo.absoluteFilePath() );
                        descriptor.setDirectory( descriptorFileInfo.absoluteDir().absolutePath() );
                        m_availableDescriptorsByModuleName.insert( moduleName, descriptor );
                    }
                    else
                    {
                        // Duplicate modules are ok; other issues like empty name or dir-mismatch are reported.
                        if ( !m_availableDescriptorsByModuleName.contains( moduleName ) )
                        {
                            cWarning() << deb << "ModuleManager module descriptor"
                                       << descriptorFileInfo.absoluteFilePath() << "has bad name" << moduleName;
                        }
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
            cDebug() << deb << "ModuleManager module search path does not exist:" << path;
        }
    }
    // At this point m_availableDescriptorsByModuleName is filled with
    // the modules that were found in the search paths.
    cDebug() << deb << "Found" << m_availableDescriptorsByModuleName.count() << "modules";
    QTimer::singleShot( 10, this, &ModuleManager::initDone );
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
ModuleManager::moduleInstance( const ModuleSystem::InstanceKey& instanceKey )
{
    return m_loadedModulesByInstanceKey.value( instanceKey );
}


/** @brief Returns the config file name for the given @p instanceKey
 *
 * Custom instances have custom config files, non-custom ones
 * have a <modulename>.conf file. Returns an empty QString on
 * errors.
 */
static QString
getConfigFileName( const Settings::InstanceDescriptionList& descriptorList,
                   const ModuleSystem::InstanceKey& instanceKey,
                   const ModuleSystem::Descriptor& thisModule )
{
    if ( !thisModule.hasConfig() )
    {
        // Explicitly set to no-configuration. This doesn't apply
        // to custom instances (above) since the only reason to
        // **have** a custom instance is to specify a different
        // config file for more than one module.
        return QString();
    }

    for ( const auto& descriptor : descriptorList )
    {
        if ( descriptor.key() == instanceKey )
        {
            return descriptor.configFileName();
        }
    }


    // This should already have been checked and failed the module already
    return QString();
}

void
ModuleManager::loadModules()
{
    if ( checkDependencies() )
    {
        cWarning() << "Some installed modules have unmet dependencies.";
    }
    Settings::InstanceDescriptionList customInstances = Settings::instance()->moduleInstances();

    QStringList failedModules;
    const auto modulesSequence = Settings::instance()->modulesSequence();
    for ( const auto& modulePhase : modulesSequence )
    {
        ModuleSystem::Action currentAction = modulePhase.first;

        for ( const auto& instanceKey : modulePhase.second )
        {
            if ( !instanceKey.isValid() )
            {
                cError() << "Wrong module entry format for module" << instanceKey;
                failedModules.append( instanceKey.toString() );
                continue;
            }

            ModuleSystem::Descriptor descriptor
                = m_availableDescriptorsByModuleName.value( instanceKey.module(), ModuleSystem::Descriptor() );
            if ( !descriptor.isValid() )
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
                thisModule = Calamares::moduleFromDescriptor(
                    descriptor, instanceKey.id(), configFileName, descriptor.directory() );
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
                const auto steps = Calamares::ViewManager::instance()->viewSteps();
                ExecutionViewStep* evs = steps.isEmpty() ? nullptr : qobject_cast< ExecutionViewStep* >( steps.last() );
                if ( !evs )  // If the last step is not an EVS, we must create it.
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
        QTimer::singleShot( 10, [ = ]() { emit modulesFailed( failedModules ); } );
    }
    else
    {
        QTimer::singleShot( 10, this, &ModuleManager::modulesLoaded );
    }
}

bool
ModuleManager::addModule( Module* module )
{
    if ( !module )
    {
        return false;
    }
    if ( !module->instanceKey().isValid() )
    {
        cWarning() << "Module" << module->location() << Logger::Pointer( module ) << "has invalid instance key.";
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
    connect( rq,
             &RequirementsChecker::done,
             this,
             [ = ]()
             {
                 if ( m_requirementsModel->satisfiedMandatory() )
                 {
                     /* we're done */ this->requirementsComplete( true );
                 }
                 else
                 {
                     this->requirementsComplete( false );
                     QTimer::singleShot( std::chrono::seconds( 5 ), this, &ModuleManager::checkRequirements );
                 }
             } );

    QTimer::singleShot( 0, rq, &RequirementsChecker::run );
}

static QStringList
missingRequiredModules( const QStringList& required, const QMap< QString, ModuleSystem::Descriptor >& available )
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
            QStringList unmet = missingRequiredModules( it->requiredModules(), m_availableDescriptorsByModuleName );

            if ( unmet.count() > 0 )
            {
                QString moduleName = it->name();
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
    QStringList requiredModules = m_availableDescriptorsByModuleName[ m.name() ].requiredModules();

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
