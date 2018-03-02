/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CREATEPARTITIONJOB_H
#define CREATEPARTITIONJOB_H

#include <jobs/PartitionJob.h>

class Device;
class Partition;
class FileSystem;

/**
 * Creates a partition on a device.
 *
 * This job does two things:
 * 1. Create the partition
 * 2. Create the filesystem on the partition
 */
class CreatePartitionJob : public PartitionJob
{
    Q_OBJECT
public:
    CreatePartitionJob( Device* device, Partition* partition );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    void updatePreview();
    Device* device() const
    {
        return m_device;
    }

private:
    Device* m_device;
};

#endif /* CREATEPARTITIONJOB_H */
