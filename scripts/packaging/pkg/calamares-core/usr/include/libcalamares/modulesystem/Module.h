/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef CALAMARES_MODULE_H
#define CALAMARES_MODULE_H

#include "DllMacro.h"
#include "Job.h"

#include "modulesystem/Descriptor.h"
#include "modulesystem/InstanceKey.h"
#include "modulesystem/Requirement.h"

#include <QStringList>
#include <QVariant>


namespace Calamares
{
class Module;
Module* moduleFromDescriptor( const ModuleSystem::Descriptor& moduleDescriptor,
                              const QString& instanceId,
                              const QString& configFileName,
                              const QString& moduleDirectory );


/**
 * @brief The Module class is a common supertype for Calamares modules.
 * It enforces a common interface for all the different types of modules, and it
 * takes care of creating an object of the correct type starting from a module
 * descriptor structure.
 */
class DLLEXPORT Module
{
public:
    using Type = ModuleSystem::Type;
    using Interface = ModuleSystem::Interface;

    virtual ~Module();

    /**
     * @brief name returns the name of this module.
     * @return a string with this module's name.
     */
    QString name() const { return m_key.module(); }

    /**
     * @brief instanceId returns the instance id of this module.
     * @return a string with this module's instance id.
     */
    QString instanceId() const { return m_key.id(); }

    /**
     * @brief instanceKey returns the instance key of this module.
     * @return a string with the instance key.
     * A module instance's instance key is modulename\@instanceid.
     * For instance, "partition\@partition" (default configuration) or
     * "locale\@someconfig" (custom configuration)
     */
    ModuleSystem::InstanceKey instanceKey() const { return m_key; }

    /**
     * @brief location returns the full path of this module's directory.
     * @return the path.
     */
    QString location() const { return m_directory; }

    /**
     * @brief Is this an emergency module?
     *
     * An emergency module is run even if an error occurs
     * which would terminate Calamares earlier in the same
     * *exec* block. Emergency modules in later exec blocks
     * are not run (in the common case where there is only
     * one exec block, this doesn't really matter).
     */
    bool isEmergency() const { return m_emergency; }

    /**
     * @brief isLoaded reports on the loaded status of a module.
     * @return true if the module's loading phase has finished, otherwise false.
     */
    bool isLoaded() const { return m_loaded; }

    /**
     * @brief configurationMap returns the contents of the configuration file for
     * this module instance.
     * @return the instance's configuration, already parsed from YAML into a variant map.
     */
    QVariantMap configurationMap();

    /**
     * @brief typeString returns a user-visible string for the module's type.
     * @return the type string.
     */
    QString typeString() const;

    /**
     * @brief interface returns a user-visible string for the module's interface.
     * @return the interface string.
     */
    QString interfaceString() const;

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
     * @brief type returns the Type of this module object.
     * @return the type enum value.
     */
    virtual Type type() const = 0;

    /**
     * @brief interface the Interface used by this module.
     * @return the interface enum value.
     */
    virtual Interface interface() const = 0;

    /**
     * @brief Check the requirements of this module.
     */
    virtual RequirementsList checkRequirements();

protected:
    explicit Module();

    /// @brief For subclasses to read their part of the descriptor
    virtual void initFrom( const ModuleSystem::Descriptor& moduleDescriptor ) = 0;
    /// @brief Generic part of descriptor reading (and instance id)
    void initFrom( const ModuleSystem::Descriptor& moduleDescriptor, const QString& id );

    QVariantMap m_configurationMap;

    bool m_loaded = false;
    bool m_emergency = false;  // Based on module and local config
    bool m_maybe_emergency = false;  // Based on the module.desc

private:
    void loadConfigurationFile( const QString& configFileName );  //throws YAML::Exception

    QString m_directory;
    ModuleSystem::InstanceKey m_key;

    friend Module* Calamares::moduleFromDescriptor( const ModuleSystem::Descriptor& moduleDescriptor,
                                                    const QString& instanceId,
                                                    const QString& configFileName,
                                                    const QString& moduleDirectory );
};

}  // namespace Calamares

#endif  // CALAMARES_MODULE_H
