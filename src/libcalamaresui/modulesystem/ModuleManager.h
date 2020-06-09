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
    virtual ~ModuleManager() override;

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

    /**
     * @brief moduleInstance returns a Module object for a given instance key.
     * @param instanceKey the instance key for a module instance.
     * @return a pointer to an object of a subtype of Module.
     */
    Module* moduleInstance( const QString& instanceKey );

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
    void initDone();
    void modulesLoaded();  /// All of the modules were loaded successfully
    void modulesFailed( QStringList );  /// .. or not
    // Below, see RequirementsChecker documentation
    void requirementsComplete( bool );

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
    QMap< QString, QString > m_moduleDirectoriesByModuleName;
    QMap< ModuleSystem::InstanceKey, Module* > m_loadedModulesByInstanceKey;
    const QStringList m_paths;
    RequirementsModel* m_requirementsModel;

    static ModuleManager* s_instance;
};

}  // namespace Calamares

#endif  // MODULELOADER_H
