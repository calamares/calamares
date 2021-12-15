/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CREATEVOLUMEGROUPJOB_H
#define CREATEVOLUMEGROUPJOB_H

#include "core/KPMHelpers.h"

#include "Job.h"
#include "partition/KPMManager.h"

class CreateVolumeGroupJob : public Calamares::Job
{
    Q_OBJECT
public:
    /** @brief Make a job that will create a volume group
     *
     * The @p physicalExtentSize is given in MiB; typically this is 4 (MiB).
     */
    CreateVolumeGroupJob( Device*,
                          const QString& vgName,
                          const PartitionVector& pvList,
                          const qint32 physicalExtentSize );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    void updatePreview();
    void undoPreview();

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    QString m_vgName;
    PartitionVector m_pvList;
    qint32 m_physicalExtentSize;
};

#endif  // CREATEVOLUMEGROUPJOB_H
