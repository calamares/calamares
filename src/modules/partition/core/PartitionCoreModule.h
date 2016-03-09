/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#include "core/PartitionModel.h"
#include "Typedefs.h"

// KPMcore
#include <kpmcore/core/partitiontable.h>

// Qt
#include <QList>
#include <QMutex>
#include <QObject>

#include <functional>

class BootLoaderModel;
class CreatePartitionJob;
class Device;
class DeviceModel;
class FileSystem;
class Partition;

class QStandardItemModel;

/**
 * The core of the module.
 *
 * It has two responsibilities:
 * - Listing the devices and partitions, creating Qt models for them.
 * - Creating jobs for any changes requested by the user interface.
 */
class PartitionCoreModule : public QObject
{
    Q_OBJECT
public:
    struct SummaryInfo
    {
        QString deviceName;
        QString deviceNode;
        PartitionModel* partitionModelBefore;
        PartitionModel* partitionModelAfter;
    };

    PartitionCoreModule( QObject* parent = nullptr );
    ~PartitionCoreModule();

    DeviceModel* deviceModel() const;

    PartitionModel* partitionModelForDevice( Device* device ) const;

    //HACK: all devices change over time, and together make up the state of the CoreModule.
    //      However this makes it hard to show the *original* state of a device.
    //      With this horrible hack we rescan a single device node to create a Device object
    //      that contains the current state of a disk regardless of subsequent changes.
    //      This should probably be redone some other way.
    //              -- Teo 4/2015
    //FIXME: make this horrible method private. -- Teo 12/2015
    static Device* createImmutableDeviceCopy( Device* device );

    QAbstractItemModel* bootLoaderModel() const;

    void createPartitionTable( Device* device, PartitionTable::TableType type );

    void createPartition( Device* device, Partition* partition,
                          PartitionTable::Flags flags = PartitionTable::FlagNone );

    void deletePartition( Device* device, Partition* partition );

    void formatPartition( Device* device, Partition* partition );

    void resizePartition( Device* device, Partition* partition, qint64 first, qint64 last );

    void setPartitionFlags( Device* device, Partition* partition, PartitionTable::Flags flags );

    void setBootLoaderInstallPath( const QString& path );

    QList< Calamares::job_ptr > jobs() const;

    bool hasRootMountPoint() const;

    QList< Partition* > efiSystemPartitions() const;
    Partition* findPartitionByMountPoint( const QString& mountPoint ) const;

    void revert();
    void revertAllDevices();
    void revertDevice( Device* dev );
    void asyncRevertDevice( Device* dev, std::function< void() > callback );

    void clearJobs();

    bool isDirty();

    /**
     * To be called when a partition has been altered, but only for changes
     * which do not affect its size, because changes which affect the partition size
     * affect the size of other partitions as well.
     */
    void refreshPartition( Device* device, Partition* partition );

    /**
     * Returns a list of SummaryInfo for devices which have pending changes.
     * Caller is responsible for deleting the partition models
     */
    QList< SummaryInfo > createSummaryInfo() const;

    void dumpQueue() const;

    OsproberEntryList osproberEntries() const;

Q_SIGNALS:
    void hasRootMountPointChanged( bool value );
    void isDirtyChanged( bool value );
    void reverted();
    void deviceReverted( Device* device );

private:
    void refresh();

    /**
     * Owns the Device, PartitionModel and the jobs
     */
    struct DeviceInfo
    {
        DeviceInfo( Device* );
        ~DeviceInfo();
        QScopedPointer< Device > device;
        QScopedPointer< PartitionModel > partitionModel;
        QList< Calamares::job_ptr > jobs;

        void forgetChanges();
        bool isDirty() const;
    };
    QList< DeviceInfo* > m_deviceInfos;
    QList< Partition* > m_efiSystemPartitions;

    DeviceModel* m_deviceModel;
    BootLoaderModel* m_bootLoaderModel;
    bool m_hasRootMountPoint = false;
    bool m_isDirty = false;
    QString m_bootLoaderInstallPath;

    void init();
    void updateHasRootMountPoint();
    void updateIsDirty();
    void scanForEfiSystemPartitions();

    DeviceInfo* infoForDevice( Device* ) const;

    OsproberEntryList m_osproberLines;

    QMutex m_revertMutex;
};

#endif /* PARTITIONCOREMODULE_H */
