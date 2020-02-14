/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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
#include "utils/NamedSuffix.h"
#include "utils/Units.h"

// KPMcore
#include <kpmcore/fs/filesystem.h>

// Qt
#include <QString>

class PartitionCoreModule;
class Partition;

namespace PartUtils
{

/**
 * @brief Provides a nice human-readable name for @p candidate
 *
 * The most-specific human-readable name for the partition @p candidate
 * is returned (e.g. device name, or partition path). In the worst
 * case, a string representation of (void *)candidate is returned.
 */
QString convenienceName( const Partition* const candidate );

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

/**
 * @brief Is the given @p partition bootable in EFI? Depending on
 * the partition table layout, this may mean different flags.
 */
bool isEfiBootable( const Partition* candidate );

/** @brief translate @p fsName into a recognized name and type
 *
 * Makes several attempts to translate the string into a
 * name that KPMCore will recognize.
 * The corresponding filesystem type is stored in @p fsType, and
 * its value is FileSystem::Unknown if @p fsName is not recognized.
 */
QString findFS( QString fsName, FileSystem::Type* fsType );

}  // namespace PartUtils

#endif  // PARTUTILS_H
