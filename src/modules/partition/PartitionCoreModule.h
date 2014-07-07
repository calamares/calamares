/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#ifndef PARTITIONCOREMODULE_H
#define PARTITIONCOREMODULE_H

#include <PartitionInfo.h>
#include <Typedefs.h>

// CalaPM
#include <core/partitiontable.h>

// Qt
#include <QList>
#include <QObject>

class CreatePartitionJob;
class Device;
class DeviceModel;
class FileSystem;
class Partition;
class PartitionModel;

/**
 * Owns the Qt models and the PM devices
 */
class PartitionCoreModule : public QObject
{
    Q_OBJECT
public:
    PartitionCoreModule( QObject* parent = nullptr );
    ~PartitionCoreModule();

    DeviceModel* deviceModel() const;

    PartitionModel* partitionModelForDevice( Device* device ) const;

    void createPartition( Device* device, PartitionInfo* partitionInfo );

    void deletePartition( Device* device, Partition* partition );

    QList< Calamares::job_ptr > jobs() const
    {
        return m_jobs;
    }

    bool hasRootMountPoint() const
    {
        return m_hasRootMountPoint;
    }

Q_SIGNALS:
    void hasRootMountPointChanged( bool value );

private:
    QList< Device* > m_devices;
    QHash< Device*, PartitionModel* > m_partitionModelForDeviceHash;
    DeviceModel* m_deviceModel;
    bool m_hasRootMountPoint = false;

    InfoForPartitionHash m_infoForPartitionHash;

    QList< Calamares::job_ptr > m_jobs;

    void listDevices();

    void dumpQueue() const;
};

#endif /* PARTITIONCOREMODULE_H */
