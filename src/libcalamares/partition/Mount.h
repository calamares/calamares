/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
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

#ifndef PARTITION_MOUNT_H
#define PARTITION_MOUNT_H

#include "DllMacro.h"

#include <QString>
#include <QStringList>

namespace CalamaresUtils
{
namespace Partition
{

/**
 * Runs the mount utility with the specified parameters.
 * @param devicePath the path of the partition to mount.
 * @param mountPoint the full path of the target mount point.
 * @param filesystemName the name of the filesystem (optional).
 * @param options any additional options as passed to mount -o (optional).
 *          If @p options starts with a dash (-) then it is passed unchanged
 *          and no -o option is added; this is used in handling --bind mounts.
 * @returns the program's exit code, or:
 *             Crashed = QProcess crash
 *             FailedToStart = QProcess cannot start
 *             NoWorkingDirectory = bad arguments
 */
DLLEXPORT int mount( const QString& devicePath,
                     const QString& mountPoint,
                     const QString& filesystemName = QString(),
                     const QString& options = QString() );

/** @brief Unmount the given @p path (device or mount point).
 *
 * Runs umount(8) in the host system.
 *
 * @returns the program's exit code, or special codes like mount().
 */
DLLEXPORT int unmount( const QString& path, const QStringList& options = QStringList() );

class DLLEXPORT TemporaryMount
{
public:
    TemporaryMount( const QString& devicePath,
                    const QString& filesystemName = QString(),
                    const QString& options = QString() );
    TemporaryMount( const TemporaryMount& ) = delete;
    TemporaryMount& operator=( const TemporaryMount& ) = delete;
    ~TemporaryMount();

    bool isValid() const { return m_d; }
    QString path() const;

private:
    struct Private;
    Private* m_d = nullptr;
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
