/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef RESIZEPARTITIONJOB_H
#define RESIZEPARTITIONJOB_H

#include "PartitionJob.h"

class Device;
class Partition;
class FileSystem;

/**
 * This job resizes an existing partition.
 *
 * It can grow, shrink and/or move a partition while preserving its content.
 */
class ResizePartitionJob : public PartitionJob
{
    Q_OBJECT
public:
    ResizePartitionJob( Device* device, Partition* partition, qint64 firstSector, qint64 lastSector );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    void updatePreview();

    Device* device() const;

private:
    Device* m_device;
    qint64 m_oldFirstSector;
    qint64 m_oldLastSector;
    qint64 m_newFirstSector;
    qint64 m_newLastSector;
};

#endif /* RESIZEPARTITIONJOB_H */
