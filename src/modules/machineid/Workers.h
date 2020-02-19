/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef WORKERS_H
#define WORKERS_H

#include "Job.h"

/// @brief Utility functions for doing the random-data stuff for MachineId
namespace MachineId
{
/** @brief Utility functions
 *
 * These probably belong in libcalamares, since they're general utilities
 * for moving files around in the target system.
 */

/// @brief Copy @p fileName from host into target system at @p rootMountPoint
Calamares::JobResult copyFile( const QString& rootMountPoint, const QString& fileName );


/** @brief Entropy functions
 *
 * The target system may want to pre-seed the entropy pool with a suitable
 * chunk of entropy data. During installation we have lots of disk access
 * so plenty of entropy -- this is used mostly be Debian.
 */

/// @brief How to generate entropy (bool-like)
enum class EntropyGeneration
{
    New,
    CopyFromHost
};

/// @brief Creates a new entropy file @p fileName in the target system at @p rootMountPoint
Calamares::JobResult createNewEntropy( int poolSize, const QString& rootMountPoint, const QString& fileName );

/// @brief Create an entropy file  @p fileName in the target system at @p rootMountPoint
Calamares::JobResult
createEntropy( const EntropyGeneration kind, const QString& rootMountPoint, const QString& fileName );


/** @brief MachineID functions
 *
 * Creating UUIDs for DBUS and SystemD.
 */

/// @brief Create a new DBus UUID file
Calamares::JobResult createDBusMachineId( const QString& rootMountPoint, const QString& fileName );

/// @brief Symlink DBus UUID file to the one from systemd (which must exist already)
Calamares::JobResult
createDBusLink( const QString& rootMountPoint, const QString& fileName, const QString& systemdFileName );

Calamares::JobResult createSystemdMachineId( const QString& rootMountPoint, const QString& fileName );


}  // namespace MachineId

#endif  // WORKERS_H
