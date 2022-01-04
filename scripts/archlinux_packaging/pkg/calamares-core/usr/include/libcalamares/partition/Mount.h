/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef PARTITION_MOUNT_H
#define PARTITION_MOUNT_H

#include "DllMacro.h"

#include <QString>
#include <QStringList>

#include <memory>

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

    bool isValid() const { return bool( m_d ); }
    QString path() const;

private:
    struct Private;
    std::unique_ptr< Private > m_d;
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
