/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QList>
#include <QString>

class Device;

namespace PartUtils
{

enum class DeviceType
{
    All,
    WritableOnly
};

/**
 * @brief Gets a list of storage devices.
 * @param which Can be used to select from all the devices in
 *      the system, filtering out those that do not meet a criterium.
 *      If set to WritableOnly, only devices which can be overwritten
 *      safely are returned (e.g. RO-media are ignored, as are mounted partitions).
 * @return a list of Devices meeting this criterium.
 */
QList< Device* > getDevices( DeviceType which = DeviceType::All );

}  // namespace PartUtils

#endif  // DEVICELIST_H
