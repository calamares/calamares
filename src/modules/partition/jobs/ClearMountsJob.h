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
 */
class ClearMountsJob : public Calamares::Job
{
    Q_OBJECT
public:
    explicit ClearMountsJob( Device* device );
    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QString tryUmount( const QString& partPath );
    QString tryClearSwap( const QString& partPath );
    QString tryCryptoClose( const QString& mapperPath );
    QStringList getCryptoDevices() const;
    Device* m_device;
};

#endif  // CLEARMOUNTSJOB_H
