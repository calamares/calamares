/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Caio Jordão Carvalho <caiojcarvalho@gmail.com>
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

#ifndef RESIZEVOLUMEGROUPJOB_H
#define RESIZEVOLUMEGROUPJOB_H

#include <Job.h>

#include <QVector>

class LvmDevice;
class Partition;

class ResizeVolumeGroupJob : public Calamares::Job
{
public:
    ResizeVolumeGroupJob( LvmDevice* device, QVector< const Partition* >& partitionList );

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QString currentPartitions() const;
    QString targetPartitions() const;

private:
    LvmDevice* m_device;
    QVector< const Partition* > m_partitionList;
};

#endif // RESIZEVOLUMEGROUPJOB_H
