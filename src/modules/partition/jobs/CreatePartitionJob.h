/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CREATEPARTITIONJOB_H
#define CREATEPARTITIONJOB_H

#include "PartitionJob.h"

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
    Device* device() const { return m_device; }

private:
    Device* m_device;
};

#endif /* CREATEPARTITIONJOB_H */
