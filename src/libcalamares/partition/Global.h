/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/*
 * This is the API for manipulating Global Storage keys related to
 * filesystems and partitions.
 */

#ifndef PARTITION_GLOBAL_H
#define PARTITION_GLOBAL_H

#include "DllMacro.h"
#include "FileSystem.h"
#include "JobQueue.h"

#include <kpmcore/fs/filesystem.h>

namespace CalamaresUtils
{
namespace Partition
{
/** @brief Mark a particular filesystem type as used (or not)
 *
 * Filesystems are marked used (or not) in the global storage
 * key *filesystem_use*. Sub-keys are the filesystem name,
 * and the values are boolean; filesystems that are used in
 * the target system are marked with @c true. Unused filesystems
 * may be unmarked, or may be marked @c false.
 *
 * The filesystem name should be the untranslated name. Filesystem
 * names are **lower**cased when used as keys.
 */
void DLLEXPORT useFilesystemGS( Calamares::GlobalStorage* gs, const QString& filesystemType, bool used );
/** @brief Reads from global storage whether the filesystem type is used
 *
 * Reads from the global storage key *filesystem_use* and returns
 * the boolean value stored in subkey @p filesystemType. Returns
 * @c false if the subkey is not set at all.
 *
 * The filesystem name should be the untranslated name. Filesystem
 * names are **lower**cased when used as keys.
 */
bool DLLEXPORT isFilesystemUsedGS( const Calamares::GlobalStorage* gs, const QString& filesystemType );

/** @brief Clears the usage data for filesystems
 *
 * This removes the internal key *filesystem_use*.
 */
void DLLEXPORT clearFilesystemGS( Calamares::GlobalStorage* gs );

/** @brief Convenience function for using "the" Global Storage
 *
 * @see useFilesystemGS(const QString&, bool)
 */
inline void
useFilesystemGS( const QString& filesystemType, bool used )
{
    useFilesystemGS( Calamares::JobQueue::instanceGlobalStorage(), filesystemType, used );
}

/** @brief Convenience function for using "the" Global Storage
 *
 * @see isFilesystemUsedGS(const QString&);
 */
inline bool
isFilesystemUsedGS( const QString& filesystemType )
{
    return isFilesystemUsedGS( Calamares::JobQueue::instanceGlobalStorage(), filesystemType );
}

/** @brief Mark a particular filesystem type as used (or not)
 *
 * See useFilesystemGS(const QString&, bool); this method uses the filesystem type
 * enumeration to pick the name.
 */
inline void
useFilesystemGS( FileSystem::Type filesystem, bool used )
{
    useFilesystemGS( untranslatedFS( filesystem ), used );
}

/* @brief Reads from global storage whether the typesystem type is used
 *
 * See isFilesystemUsedGS(const QString&).
 */
inline bool
isFilesystemUsedGS( FileSystem::Type filesystem )
{
    return isFilesystemUsedGS( untranslatedFS( filesystem ) );
}

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
