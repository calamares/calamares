/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
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
    PythonQt  // Views only, available as enum even if PythonQt isn't used
};
const NamedEnumTable< Interface >& interfaceNames();


/* While this isn't a useful *using* right now, the intention is
 * to create a more strongly-typed Module Descriptor that carries
 * only the necessary information and no variants.
 */
// using Descriptor = QVariantMap;

class Descriptor
{
public:
    Descriptor();

    bool isValid() const { return false; }

    QString name() const { return QString(); }
    bool isEmergency() const { return false; }
};

}  // namespace ModuleSystem
}  // namespace Calamares

#endif
