/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_MODULEFACTORY_H
#define CALAMARES_MODULEFACTORY_H

#include "DllMacro.h"

#include "modulesystem/Descriptor.h"
#include "modulesystem/Module.h"

#include <QString>

namespace Calamares
{

/**
 * @brief fromDescriptor creates a new Module object of the correct type.
 * @param moduleDescriptor a module descriptor, already parsed into a variant map.
 * @param instanceId the instance id of the new module instance.
 * @param configFileName the name of the configuration file to read.
 * @param moduleDirectory the path to the directory with this module's files.
 * @return a pointer to an object of a subtype of Module.
 */
UIDLLEXPORT Module* moduleFromDescriptor( const ModuleSystem::Descriptor& moduleDescriptor,
                                          const QString& instanceId,
                                          const QString& configFileName,
                                          const QString& moduleDirectory );
}  // namespace Calamares

#endif  // CALAMARES_MODULEFACTORY_H
