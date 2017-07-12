/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
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

#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QList>
#include <QString>

class Device;

namespace PartUtils
{

enum class DeviceType { All, WritableOnly };

/**
 * @brief Gets a list of storage devices.
 * @param which Can be used to select from all the devices in
 *      the system, filtering out those that do not meet a criterium.
 *      If set to WritableOnly, only devices which can be overwritten
 *      safely are returned (e.g. RO-media are ignored, as are mounted partitions).
 * @param minimumSize Can be used to filter devices based on their
 *      size (in bytes). If non-negative, only devices with a size
 *      greater than @p minimumSize will be returned.
 * @return a list of Devices meeting this criterium.
 */
QList< Device* > getDevices( DeviceType which = DeviceType::All, qint64 minimumSize = -1 );

}

#endif // DEVICELIST_H
