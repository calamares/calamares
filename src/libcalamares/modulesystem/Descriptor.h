/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef MODULESYSTEM_DESCRIPTOR_H
#define MODULESYSTEM_DESCRIPTOR_H

#include "utils/NamedEnum.h"

#include <QVariantMap>

namespace Calamares
{
namespace ModuleSystem
{
/**
 * @brief The Type enum represents the intended functionality of the module
 * Every module is either a job module or a view module.
 * A job module is a single Calamares job.
 * A view module has a UI (one or more view pages) and zero-to-many jobs.
 */
enum class Type
{
    Job,
    View
};
const NamedEnumTable< Type >& typeNames();

/**
 * @brief The Interface enum represents the interface through which the module
 * talks to Calamares.
 * Not all Type-Interface associations are valid.
 */
enum class Interface
{
    QtPlugin,  // Jobs or Views
    Python,  // Jobs only
    Process,  // Deprecated interface
};
const NamedEnumTable< Interface >& interfaceNames();


/* While this isn't a useful *using* right now, the intention is
 * to create a more strongly-typed Module Descriptor that carries
 * only the necessary information and no variants.
 */
class Descriptor
{
public:
    ///@brief an invalid, and empty, descriptor
    Descriptor();

    /** @brief Fills a descriptor from the loaded (YAML) data.
     *
     * The @p descriptorPath is used only for debug messages, the
     * data is only read from @p moduleDesc.
     *
     */
    static Descriptor fromDescriptorData( const QVariantMap& moduleDesc, const QString& descriptorPath );

    bool isValid() const { return m_isValid; }

    QString name() const { return m_name; }
    Type type() const { return m_type; }
    Interface interface() const { return m_interface; }

    bool isEmergency() const { return m_isEmergeny; }
    bool hasConfig() const { return m_hasConfig; }
    int weight() const { return m_weight < 1 ? 1 : m_weight; }
    bool explicitWeight() const { return m_weight > 0; }


    /// @brief The directory where the module.desc lives
    QString directory() const { return m_directory; }
    void setDirectory( const QString& d ) { m_directory = d; }

    const QStringList& requiredModules() const { return m_requiredModules; }

    /** @section C++ Modules
     *
     * The C++ modules are the most general, and are loaded as
     * a shared library after which a suitable factory creates
     * objects from them.
     */

    /// @brief Short path to the shared-library; no extension.
    QString load() const { return m_interface == Interface::QtPlugin ? m_script : QString(); }

    /** @section Process Job modules
     *
     * Process Jobs are somewhat deprecated in favor of shellprocess
     * and contextualprocess jobs, since those handle multiple configuration
     * much more gracefully.
     *
     * Process Jobs execute one command.
     */
    /// @brief The command to execute; passed to the shell
    QString command() const { return m_interface == Interface::Process ? m_script : QString(); }
    /// @brief Timeout in seconds
    int timeout() const { return m_processTimeout; }
    /// @brief Run command in chroot?
    bool chroot() const { return m_processChroot; }

    /** @section Python Job modules
     *
     * Python job modules have one specific script to load and run.
     */
    QString script() const
    {
        return m_interface == Interface::Python ? m_script : QString();
    }

private:
    QString m_name;
    QString m_directory;
    QStringList m_requiredModules;
    int m_weight = -1;
    Type m_type;
    Interface m_interface;
    bool m_isValid = false;
    bool m_isEmergeny = false;
    bool m_hasConfig = true;

    /** @brief The name of the thing to load
     *
     * - A C++ module loads a shared library (via key *load*),
     * - A Python module loads a Python script (via key *script*),
     * - A process runs a specific command (via key *command*)
     *
     * This name-of-the-thing is stored here, regardless of which
     * interface is being used.
     */
    QString m_script;

    int m_processTimeout = 30;
    bool m_processChroot = false;
};

}  // namespace ModuleSystem
}  // namespace Calamares

#endif
