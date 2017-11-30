/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
#ifndef CALAMARES_REQUIREMENT_H
#define CALAMARES_REQUIREMENT_H

#include <QList>
#include <QString>

#include <functional>

namespace Calamares
{

/**
 * An indication of a requirement, which is checked in preparation
 * for system installation. An entry has a name and some explanation,
 * as well as three meaningful states:
 *  - checked = true, the requirement is met (green)
 *  - checked = false, the requirement is not met
 *      - required = false, warn about it (yellow), no failure
 *      - required = true, prohibit installation (red)
 */
struct RequirementEntry
{
    QString name;
    std::function< QString() > enumerationText; //Partial string, inserted in a
                                                //list of requirements to satisfy.
    std::function< QString() > negatedText;     //Complete sentence about this requirement
                                                //not having been met.
    bool checked;
    bool required;
};

using RequirementsList = QList< RequirementEntry >;

}  // namespace Calamares
#endif
