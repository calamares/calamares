/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#ifndef RESIZEPARTITIONJOB_H
#define RESIZEPARTITIONJOB_H

#include <jobs/PartitionJob.h>

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
