/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
