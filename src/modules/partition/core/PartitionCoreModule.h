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
    /**
     * @brief The SummaryInfo struct is a wrapper for PartitionModel instances for
     * a given Device.
     * Each Device gets a mutable "after" model and an immutable "before" model.
     */
    struct SummaryInfo
    {
        QString deviceName;
        QString deviceNode;
        PartitionModel* partitionModelBefore;
        PartitionModel* partitionModelAfter;
    };

    PartitionCoreModule( QObject* parent = nullptr );
    ~PartitionCoreModule();

    /**
     * @brief init performs a devices scan and initializes all KPMcore data
     * structures.
     * This function is thread safe.
     */
    void init();

    /**
     * @brief deviceModel returns a model which exposes a list of available
     * storage devices.
     * @return the device model.
     */
    DeviceModel* deviceModel() const;

    /**
     * @brief partitionModelForDevice returns the PartitionModel for the given device.
     * @param device the device for which to get a model.
     * @return a PartitionModel which represents the partitions of a device.
     */
    PartitionModel* partitionModelForDevice( const Device* device ) const;

    //HACK: all devices change over time, and together make up the state of the CoreModule.
    //      However this makes it hard to show the *original* state of a device.
    //      For each DeviceInfo we keep a second Device object that contains the
    //      current state of a disk regardless of subsequent changes.
    //              -- Teo 4/2015
    //FIXME: make this horrible method private. -- Teo 12/2015
    Device* immutableDeviceCopy( const Device* device );

    /**
     * @brief bootLoaderModel returns a model which represents the available boot
     * loader locations.
     * The single BootLoaderModel instance belongs to the PCM.
     * @return the BootLoaderModel.
     */
    QAbstractItemModel* bootLoaderModel() const;

    void createPartitionTable( Device* device, PartitionTable::TableType type );

    void createPartition( Device* device, Partition* partition,
                          PartitionTable::Flags flags = PartitionTable::FlagNone );

    void deletePartition( Device* device, Partition* partition );

    void formatPartition( Device* device, Partition* partition );

    void resizePartition( Device* device, Partition* partition, qint64 first, qint64 last );

    void setPartitionFlags( Device* device, Partition* partition, PartitionTable::Flags flags );

    void setBootLoaderInstallPath( const QString& path );

    /**
     * @brief jobs creates and returns a list of jobs which can then apply the changes
     * requested by the user.
     * @return a list of jobs.
     */
    QList< Calamares::job_ptr > jobs() const;

    bool hasRootMountPoint() const;

    QList< Partition* > efiSystemPartitions() const;

    /**
     * @brief findPartitionByMountPoint returns a Partition* for a given mount point.
     * @param mountPoint the mount point to find a partition for.
     * @return a pointer to a Partition object.
     * Note that this function looks for partitions in live devices (the "proposed"
     * state), not the immutable copies. Comparisons with Partition* objects that
     * refer to immutable Device*s will fail.
     */
    Partition* findPartitionByMountPoint( const QString& mountPoint ) const;

    void revert();                      // full revert, thread safe, calls doInit
    void revertAllDevices();            // convenience function, calls revertDevice
    void revertDevice( Device* dev );   // rescans a single Device and updates DeviceInfo
    void asyncRevertDevice( Device* dev, std::function< void() > callback ); //like revertDevice, but asynchronous

    void clearJobs();   // only clear jobs, the Device* states are preserved

    bool isDirty();     // true if there are pending changes, otherwise false

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

    void dumpQueue() const; // debug output

    const OsproberEntryList osproberEntries() const;    // os-prober data structure, cached

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
        const QScopedPointer< Device > immutableDevice;
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

    void doInit();
    void updateHasRootMountPoint();
    void updateIsDirty();
    void scanForEfiSystemPartitions();

    DeviceInfo* infoForDevice( const Device* ) const;

    OsproberEntryList m_osproberLines;

    QMutex m_revertMutex;
};

#endif /* PARTITIONCOREMODULE_H */
