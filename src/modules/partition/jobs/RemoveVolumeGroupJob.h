/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef REMOVEVOLUMEGROUPJOB_H
#define REMOVEVOLUMEGROUPJOB_H

#include "Job.h"
#include "partition/KPMManager.h"

class Device;
class LvmDevice;

class RemoveVolumeGroupJob : public Calamares::Job
{
    Q_OBJECT
public:
    RemoveVolumeGroupJob( Device*, LvmDevice* device );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    LvmDevice* m_device;
};

#endif  // REMOVEVOLUMEGROUPJOB_H
