/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef MODULELOADER_H
#define MODULELOADER_H

#include "modulesystem/Descriptor.h"
#include "modulesystem/InstanceKey.h"
#include "modulesystem/Requirement.h"

#include <QObject>
#include <QStringList>
#include <QVariantMap>

namespace Calamares
{

class Module;
class RequirementsModel;

/**
 * @brief The ModuleManager class is a singleton which manages Calamares modules.
 *
 * It goes through the module search directories and reads module metadata. It then
 * constructs objects of type Module, loads them and makes them accessible by their
 * instance key.
 */
class ModuleManager : public QObject
{
    Q_OBJECT
public:
    explicit ModuleManager( const QStringList& paths, QObject* parent = nullptr );
    ~ModuleManager() override;

    static ModuleManager* instance();

    /**
     * @brief init goes through the module search directories and gets a list of
     * modules available for loading, along with their metadata.
     * This information is stored as a map of Module* objects, indexed by name.
     */
    void init();

    /**
     * @brief loadedInstanceKeys returns a list of instance keys for the available
     * modules.
     * @return a QStringList with the instance keys.
     */
    QList< ModuleSystem::InstanceKey > loadedInstanceKeys();

    /**
     * @brief moduleDescriptor returns the module descriptor structure for a given module.
     * @param name the name of the module for which to return the module descriptor.
     * @return the module descriptor, as a variant map already parsed from YAML.
     */
    ModuleSystem::Descriptor moduleDescriptor( const QString& name );

    /** @brief returns the module descriptor structure for the module @p instance
     *
     * Descriptors are for the module, which may have multiple instances;
     * this is the same as moduleDescriptor( instance.module() ).
     */
    ModuleSystem::Descriptor moduleDescriptor( const ModuleSystem::InstanceKey& instanceKey )
    {
        return moduleDescriptor( instanceKey.module() );
    }

    /**
     * @brief moduleInstance returns a Module object for a given instance key.
     * @param instanceKey the instance key for a module instance.
     * @return a pointer to an object of a subtype of Module.
     */
    Module* moduleInstance( const ModuleSystem::InstanceKey& instanceKey );

    /**
     * @brief loadModules does all of the module loading operation.
     * When this is done, the signal modulesLoaded is emitted.
     * It is recommended to call this from a single-shot QTimer.
     */
    void loadModules();

    /**
     * @brief Adds a single module (loaded by some other means)
     *
     * Returns @c true on success (that is, the module's dependencies
     * are satisfied, it wasn't already loaded, ...).
     */
    bool addModule( Module* );

    /**
     * @brief Starts asynchronous requirements checking for each module.
     * When this is done, the signal requirementsComplete is emitted.
     */
    void checkRequirements();

    ///@brief Gets the model that requirements-checking works on.
    RequirementsModel* requirementsModel() { return m_requirementsModel; }

signals:
    /** @brief Emitted when all the module **configuration** has been read
     *
     * This indicates that all of the module.desc files have been
     * loaded; bad ones are silently skipped, so this just indicates
     * that the module manager is ready for the next phase (loading).
     */
    void initDone();
    /** @brief Emitted when all the modules are loaded successfully
     *
     * Each module listed in the settings is loaded. Modules are loaded
     * only once, even when instantiated multiple times. If all of
     * the listed modules are successfully loaded, this signal is
     * emitted (otherwise, it isn't, so you need to wait for **both**
     * of the signals).
     *
     * If this is emitted (i.e. all modules have loaded) then the next
     * phase, requirements checking, can be started.
     */
    void modulesLoaded();
    /** @brief Emitted if any modules failed to load
     *
     * Modules that failed to load (for any reason) are listed by
     * instance key (e.g. "welcome@welcome", "shellprocess@mycustomthing").
     */
    void modulesFailed( QStringList );
    /** @brief Emitted after all requirements have been checked
     *
     * The bool @p canContinue indicates if all of the **mandatory** requirements
     * are satisfied (e.g. whether installation can continue).
     */
    void requirementsComplete( bool canContinue );

private slots:
    void doInit();

private:
    /**
     * Check in a general sense whether the dependencies between
     * modules are valid. Returns the number of modules that
     * have missing dependencies -- this is **not** a problem
     * unless any of those modules are actually used.
     *
     * Returns 0 on success.
     *
     * Also modifies m_availableDescriptorsByModuleName to remove
     * all the entries that (so that later, when we try to look
     * them up, they are not found).
     */
    size_t checkDependencies();

    /**
     * Check for this specific module if its required modules have
     * already been loaded (i.e. are in sequence before it).
     *
     * Returns true if the requirements are met.
     */
    bool checkModuleDependencies( const Module& );

    QMap< QString, ModuleSystem::Descriptor > m_availableDescriptorsByModuleName;
    QMap< ModuleSystem::InstanceKey, Module* > m_loadedModulesByInstanceKey;
    const QStringList m_paths;
    RequirementsModel* m_requirementsModel;

    static ModuleManager* s_instance;
};

}  // namespace Calamares

#endif  // MODULELOADER_H
