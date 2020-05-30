/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
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
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */
#ifndef CALAMARES_REQUIREMENT_H
#define CALAMARES_REQUIREMENT_H

#include "DllMacro.h"

#include <QList>
#include <QMetaType>
#include <QString>

#include <functional>

namespace Calamares
{

/**
 * An indication of a requirement, which is checked in preparation
 * for system installation. An entry has a name and some explanation functions
 * (functions, because they need to respond to translations).
 *
 * A requirement can be *satisfied* or not.
 * A requirement can be optional (i.e. a "good to have") or mandatory.
 *
 * Requirements which are not satisfied, and also mandatory, will prevent the
 * installation from proceeding.
 */
struct RequirementEntry
{
    using TextFunction = std::function< QString() >;

    /// @brief name of this requirement; not shown to user and used as ID
    QString name;

    /// @brief Detailed description of this requirement, for use in user-visible lists
    TextFunction enumerationText;

    /// @brief User-visible string to show that the requirement is not met, short form
    TextFunction negatedText;

    bool satisfied;
    bool mandatory;

    /// @brief Convenience to check if this entry should be shown in details dialog
    bool hasDetails() const { return !enumerationText().isEmpty(); }
};

using RequirementsList = QList< RequirementEntry >;

}  // namespace Calamares

Q_DECLARE_METATYPE( Calamares::RequirementEntry )

#endif
