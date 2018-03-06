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

#ifndef DELETEPARTITIONJOB_H
#define DELETEPARTITIONJOB_H

#include <jobs/PartitionJob.h>

class Device;
class Partition;
class FileSystem;

/**
 * Deletes an existing partition.
 *
 * This is only used for partitions which already existed before the installer
 * was started: partitions created within the installer and then removed are
 * simply forgotten.
 */
class DeletePartitionJob : public PartitionJob
{
    Q_OBJECT
public:
    DeletePartitionJob( Device* device, Partition* partition );
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

#endif /* DELETEPARTITIONJOB_H */
