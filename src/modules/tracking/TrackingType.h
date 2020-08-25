/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
