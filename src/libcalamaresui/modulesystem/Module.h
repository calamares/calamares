/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_MODULE_H
#define CALAMARES_MODULE_H

#include "UiDllMacro.h"

#include <Typedefs.h>

#include <QStringList>
#include <QVariant>


namespace Calamares
{
class Module;
}

void operator>>( const QVariantMap& moduleDescriptor, Calamares::Module* m );

namespace Calamares
{

/**
 * @brief The Module class is a common supertype for Calamares modules.
 * It enforces a common interface for all the different types of modules, and it
 * takes care of creating an object of the correct type starting from a module
 * descriptor structure.
 */
class UIDLLEXPORT Module
{
public:
    /**
     * @brief The Type enum represents the intended functionality of the module
     * Every module is either a job module or a view module.
     * A job module is a single Calamares job.
     * A view module has a UI (one or more view pages) and zero-to-many jobs.
     */
    enum Type
    {
        Job,
        View
    };

    /**
     * @brief The Interface enum represents the interface through which the module
     * talks to Calamares.
     * Not all Type-Interface associations are valid.
     */
    enum Interface
    {
        QtPluginInterface,
        PythonInterface,
        ProcessInterface,
        PythonQtInterface
    };

    /**
     * @brief fromDescriptor creates a new Module object of the correct type.
     * @param moduleDescriptor a module descriptor, already parsed into a variant map.
     * @param instanceId the instance id of the new module instance.
     * @param configFileName the name of the configuration file to read.
     * @param moduleDirectory the path to the directory with this module's files.
     * @return a pointer to an object of a subtype of Module.
     */
    static Module* fromDescriptor( const QVariantMap& moduleDescriptor,
                                   const QString& instanceId,
                                   const QString& configFileName,
                                   const QString& moduleDirectory );
    virtual ~Module();

    /**
     * @brief name returns the name of this module.
     * @return a string with this module's name.
     */
    virtual QString name() const final;

    /**
     * @brief instanceId returns the instance id of this module.
     * @return a string with this module's instance id.
     */
    virtual QString instanceId() const final;

    /**
     * @brief instanceKey returns the instance key of this module.
     * @return a string with the instance key.
     * A module instance's instance key is modulename\@instanceid.
     * For instance, "partition\@partition" (default configuration) or
     * "locale\@someconfig" (custom configuration)
     */
    virtual QString instanceKey() const final;

    /**
     * @brief requiredModules a list of names of modules required by this one.
     * @return the list of names.
     * The module dependencies system is currently incomplete and unused.
     */
    virtual QStringList requiredModules() const;

    /**
     * @brief location returns the full path of this module's directory.
     * @return the path.
     */
    virtual QString location() const final;

    /**
     * @brief type returns the Type of this module object.
     * @return the type enum value.
     */
    virtual Type type() const = 0;

    /**
     * @brief typeString returns a user-visible string for the module's type.
     * @return the type string.
     */
    virtual QString typeString() const;

    /**
     * @brief interface the Interface used by this module.
     * @return the interface enum value.
     */
    virtual Interface interface() const = 0;

    /**
     * @brief interface returns a user-visible string for the module's interface.
     * @return the interface string.
     */
    virtual QString interfaceString() const;

    /**
     * @brief isLoaded reports on the loaded status of a module.
     * @return true if the module's loading phase has finished, otherwise false.
     */
    virtual bool isLoaded() const;

    /**
     * @brief loadSelf initialized the module.
     * Subclasses must reimplement this depending on the module type and interface.
     */
    virtual void loadSelf() = 0;

    /**
     * @brief jobs returns any jobs exposed by this module.
     * @return a list of jobs (can be empty).
     */
    virtual JobList jobs() const = 0;

    /**
     * @brief configurationMap returns the contents of the configuration file for
     * this module instance.
     * @return the instance's configuration, already parsed from YAML into a variant map.
     */
    QVariantMap configurationMap();

protected:
    explicit Module();
    virtual void initFrom( const QVariantMap& moduleDescriptor );
    bool m_loaded;
    QVariantMap m_configurationMap;

private:
    void loadConfigurationFile( const QString& configFileName ); //throws YAML::Exception
    QString m_name;
    QStringList m_requiredModules;
    QString m_directory;
    QString m_instanceId;

    friend void ::operator>>( const QVariantMap& moduleDescriptor,
                              Calamares::Module* m );
};

}

#endif // CALAMARES_MODULE_H
