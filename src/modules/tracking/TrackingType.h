/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef TRACKINGTYPE_H
#define TRACKINGTYPE_H

#include "utils/NamedEnum.h"

enum class TrackingType
{
    NoTracking,  // Do not enable tracking at all
    InstallTracking,  // Track that *this* install has happened
    MachineTracking,  // Track the machine, ongoing
    UserTracking  // Track the user, ongoing
};

// Implemented in Config.cpp
const NamedEnumTable< TrackingType >& trackingNames();

#endif  //TRACKINGTYPE_H
