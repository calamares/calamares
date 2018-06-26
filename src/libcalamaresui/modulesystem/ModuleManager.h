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

#include "Typedefs.h"

#include <QObject>
#include <QStringList>
#include <QVariantMap>

namespace Calamares
{

class Module;

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
    QStringList loadedInstanceKeys();

    /**
     * @brief moduleDescriptor returns the module descriptor structure for a given module.
     * @param name the name of the module for which to return the module descriptor.
     * @return the module descriptor, as a variant map already parsed from YAML.
     */
    QVariantMap moduleDescriptor( const QString& name );

    /**
     * @brief moduleInstance returns a Module object for a given instance key.
     * @param instanceKey the instance key for a module instance.
     * @return a pointer to an object of a subtype of Module.
     */
    Module* moduleInstance( const QString& instanceKey );

    /**
     * @brief loadModules initiates the asynchronous module loading operation.
     * When this is done, the signal modulesLoaded is emitted.
     */
    void loadModules();

signals:
    void initDone();
    void modulesLoaded();  /// All of the modules were loaded successfully
    void modulesFailed( QStringList );   /// .. or not

private slots:
    void doInit();

private:
    /**
     * Check in a general sense whether the dependencies between
     * modules are valid. Returns a list of module names that
     * do **not** have their requirements met.
     *
     * Returns an empty list on success.
     *
     * Also modifies m_availableDescriptorsByModuleName to remove
     * all the entries that fail.
     */
    QStringList checkDependencies();

    /**
     * Check for this specific module if its required modules have
     * already been loaded (i.e. are in sequence before it).
     *
     * Returns true if the requirements are met.
     */
    bool checkDependencies( const Module& );

    QMap< QString, QVariantMap > m_availableDescriptorsByModuleName;
    QMap< QString, QString > m_moduleDirectoriesByModuleName;
    QMap< QString, Module* > m_loadedModulesByInstanceKey;
    const QStringList m_paths;

    static ModuleManager* s_instance;
};

}

#endif // MODULELOADER_H
