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

#include <QList>
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


/** @brief Mount and automatically unmount a device
 *
 * The TemporaryMount object mounts a filesystem, and is like calling
 * the mount() function, above. When the object is destroyed, unmount()
 * is called with suitable options to undo the original mount.
 */
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


/** @brief Information about a mount point from /etc/mtab
 *
 * Entries in /etc/mtab are of the form: <device> <mountpoint> <other>
 * This struct only stores device and mountpoint.
 *
 * The main way of getting these structs is to call fromMtab() to read
 * an /etc/mtab-like file and storing all of the entries from it.
 */
struct DLLEXPORT MtabInfo
{
    QString device;
    QString mountPoint;

    /** @brief Reads an mtab-like file and returns the entries from it
     *
     * When @p mtabPath is given, that file is read. If the given name is
     * empty (e.g. the default) then /etc/mtab is read, instead.
     *
     * If @p mountPrefix is given, then only entries that have a mount point
     * that starts with that prefix are returned.
     */
    static QList< MtabInfo > fromMtabFilteredByPrefix( const QString& mountPrefix = QString(),
                                                       const QString& mtabPath = QString() );
    /// @brief Predicate to sort MtabInfo objects by device-name
    static bool deviceOrder( const MtabInfo& a, const MtabInfo& b ) { return a.device > b.device; }
    /// @brief Predicate to sort MtabInfo objects by mount-point
    static bool mountPointOrder( const MtabInfo& a, const MtabInfo& b ) { return a.mountPoint > b.mountPoint; }
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
