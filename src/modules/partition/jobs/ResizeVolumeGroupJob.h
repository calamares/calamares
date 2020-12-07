/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef RESIZEVOLUMEGROUPJOB_H
#define RESIZEVOLUMEGROUPJOB_H

#include "Job.h"
#include "partition/KPMManager.h"

#include <QVector>

class Device;
class LvmDevice;
class Partition;

class ResizeVolumeGroupJob : public Calamares::Job
{
    Q_OBJECT
public:
    ResizeVolumeGroupJob( Device*, LvmDevice* device, QVector< const Partition* >& partitionList );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QString currentPartitions() const;
    QString targetPartitions() const;

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    LvmDevice* m_device;
    QVector< const Partition* > m_partitionList;
};

#endif  // RESIZEVOLUMEGROUPJOB_H
