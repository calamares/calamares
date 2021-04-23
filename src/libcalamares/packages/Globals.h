/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARES_PACKAGES_GLOBALS_H
#define LIBCALAMARES_PACKAGES_GLOBALS_H

#include "GlobalStorage.h"
#include "modulesystem/InstanceKey.h"

namespace CalamaresUtils
{
namespace Packages
{
/** @brief Sets the install-packages GS keys for the given module
 *
 * This replaces previously-set install-packages lists for the
 * given module by the two new lists.
 *
 * Returns @c true if anything was changed, @c false otherwise.
 */
bool setGSPackageAdditions( Calamares::GlobalStorage* gs,
                            const Calamares::ModuleSystem::InstanceKey& module,
                            const QVariantList& installPackages,
                            const QVariantList& tryInstallPackages );
/** @brief Sets the install-packages GS keys for the given module
 *
 * This replaces previously-set install-packages lists. Use this with
 * plain lists of package names. It does not support try-install.
 */
bool setGSPackageAdditions( Calamares::GlobalStorage* gs,
                            const Calamares::ModuleSystem::InstanceKey& module,
                            const QStringList& installPackages );
// void setGSPackageRemovals( const Calamares::ModuleSystem::InstanceKey& key, const QVariantList& removePackages );
}  // namespace Packages
}  // namespace CalamaresUtils


#endif
