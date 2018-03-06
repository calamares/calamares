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

#ifndef FILLGLOBALSTORAGEJOB_H
#define FILLGLOBALSTORAGEJOB_H

#include <Job.h>

// Qt
#include <QList>

class Device;
class Partition;

/**
 * This job does not touch devices. It inserts in GlobalStorage the
 * partition-related keys (see hacking/GlobalStorage.md)
 *
 * Inserting the keys after partitioning makes it possible to access
 * information such as the partition path or the UUID.
 */
class FillGlobalStorageJob : public Calamares::Job
{
    Q_OBJECT
public:
    FillGlobalStorageJob( QList< Device* > devices, const QString& bootLoaderPath );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
private:
    QList< Device* > m_devices;
    QString m_bootLoaderPath;

    QVariant createPartitionList() const;
    QVariant createBootLoaderMap() const;
};

#endif /* FILLGLOBALSTORAGEJOB_H */
