/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef DEACTIVATEVOLUMEGROUPJOB_H
#define DEACTIVATEVOLUMEGROUPJOB_H

#include "Job.h"
#include "partition/KPMManager.h"

class LvmDevice;

class DeactivateVolumeGroupJob : public Calamares::Job
{
    Q_OBJECT
public:
    DeactivateVolumeGroupJob( LvmDevice* device );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    LvmDevice* m_device;
};

#endif  // DEACTIVATEVOLUMEGROUPJOB_H
