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

#include "Job.h"
#include "partition/KPMManager.h"

#include <QVector>

class Device;
class Partition;

class CreateVolumeGroupJob : public Calamares::Job
{
    Q_OBJECT
public:
    CreateVolumeGroupJob( Device*, QString& vgName, QVector< const Partition* > pvList, const qint32 peSize );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    void updatePreview();
    void undoPreview();

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    QString m_vgName;
    QVector< const Partition* > m_pvList;
    qint32 m_peSize;
};

#endif  // CREATEVOLUMEGROUPJOB_H
