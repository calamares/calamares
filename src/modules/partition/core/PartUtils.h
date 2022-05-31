/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

class DeviceModel;
class Partition;
namespace Logger
{
class Once;
}

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
 * @param o applied to debug-logging.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeReplaced( Partition* candidate, const Logger::Once& o );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for resizing (shrinking) it to make room for a new OS.
 * @param candidate the candidate partition to resize.
 * @param o applied to debug-logging.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeResized( Partition* candidate, const Logger::Once& o );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for resizing (shrinking) it to make room for a new OS.
 * @param dm the DeviceModel instance.
 * @param partitionPath the device path of the candidate partition to resize.
 * @param o applied to debug-logging.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeResized( DeviceModel* dm, const QString& partitionPath, const Logger::Once& o );

/**
 * @brief runOsprober executes os-prober, parses the output and writes relevant
 * data to GlobalStorage.
 * @param dm the DeviceModel instance.
 * @return a list of os-prober entries, parsed.
 */
OsproberEntryList runOsprober( DeviceModel* dm );

/**
 * @brief Is this system EFI-enabled? Decides based on /sys/firmware/efi
 */
bool isEfiSystem();

/**
 * @brief Is the @p partition suitable as an EFI boot partition?
 * Checks for filesystem type (FAT32).
 */
bool isEfiFilesystemSuitableType( const Partition* candidate );

/**
 * @brief Is the @p partition suitable as an EFI boot partition?
 * Checks for filesystem size (300MiB, see efiFilesystemMinimumSize).
 */
bool isEfiFilesystemSuitableSize( const Partition* candidate );

/** @brief Returns the minimum size of an EFI boot partition in bytes.
 *
 * This is determined as 300MiB, based on the FAT32 standard
 * and EFI documentation (and not a little discussion in Calamares
 * issues about what works, what is effective, and what is mandated
 * by the standard and how all of those are different).
 *
 * This can be configured through the `partition.conf` file,
 * key *efiSystemPartitionSize*, which will then apply to both
 * automatic partitioning **and** the warning for manual partitioning.
 *
 * A minimum of 32MiB (which is bonkers-small) is enforced.
 */
qint64 efiFilesystemMinimumSize();

/**
 * @brief Is the given @p partition bootable in EFI? Depending on
 * the partition table layout, this may mean different flags.
 */
bool isEfiBootable( const Partition* candidate );

/** @brief translate @p fsName into a recognized name and type
 *
 * Makes several attempts to translate the string into a
 * name that KPMCore will recognize. Returns the canonical
 * filesystem name (e.g. asking for "EXT4" will return "ext4").
 *
 * The corresponding filesystem type is stored in @p fsType, and
 * its value is FileSystem::Unknown if @p fsName is not recognized.
 */
QString canonicalFilesystemName( const QString& fsName, FileSystem::Type* fsType );

}  // namespace PartUtils

#endif  // PARTUTILS_H
