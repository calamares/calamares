/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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

#ifndef PARTUTILS_H
#define PARTUTILS_H

#include "OsproberEntry.h"

#include <QString>

class PartitionCoreModule;
class Partition;

namespace PartUtils
{

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for replacing it with the new OS.
 * @param candidate the candidate partition to replace.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeReplaced( Partition* candidate );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for resizing (shrinking) it to make room for a new OS.
 * @param candidate the candidate partition to resize.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeResized( Partition* candidate );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for resizing (shrinking) it to make room for a new OS.
 * @param core the PartitionCoreModule instance.
 * @param partitionPath the device path of the candidate partition to resize.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeResized( PartitionCoreModule* core, const QString& partitionPath );

/**
 * @brief runOsprober executes os-prober, parses the output and writes relevant
 * data to GlobalStorage.
 * @param core the PartitionCoreModule instance.
 * @return a list of os-prober entries, parsed.
 */
OsproberEntryList runOsprober( PartitionCoreModule* core );

/**
 * @brief Is this system EFI-enabled? Decides based on /sys/firmware/efi
 */
bool isEfiSystem();

}

#endif // PARTUTILS_H
