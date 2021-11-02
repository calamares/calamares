/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CLEARMOUNTSJOB_H
#define CLEARMOUNTSJOB_H

#include "Job.h"

class Device;

/**
 * This job tries to free all mounts for the given device, so partitioning
 * operations can proceed.
 *
 * - partitions on the device are unmounted
 * - swap on the device is disabled and cleared
 * - physical volumes for LVM on the device are disabled
 *
 * In addition, regardless of device:
 * - almost all(*) /dev/mapper entries (crypto / LUKS, also LVM) are closed
 * - all logical volumes for LVM are unmounted
 * Exceptions to "all /dev/mapper" may be configured through
 * the setMapperExceptions() method. Pass in names of mapper
 * files that should not be closed (e.g. "myvg-mylv").
 *
 * (*) Some exceptions always exist: /dev/mapper/control is never
 *     closed. /dev/mapper/live-* is never closed.
 *
 */
class ClearMountsJob : public Calamares::Job
{
    Q_OBJECT
public:
    /** @brief Creates a job freeing mounts on @p device
     *
     * No ownership is transferred; the @p device is used only to access
     * the device node (name).
     */
    explicit ClearMountsJob( Device* device );

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    ///@brief Sets the list of exceptions (names) when closing /dev/mapper
    void setMapperExceptions( const QStringList& names ) { m_mapperExceptions = names; }

private:
    const QString m_deviceNode;
    QStringList m_mapperExceptions;
};

#endif  // CLEARMOUNTSJOB_H
