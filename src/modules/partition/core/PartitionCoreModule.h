/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONCOREMODULE_H
#define PARTITIONCOREMODULE_H

#include "core/KPMHelpers.h"
#include "core/PartitionLayout.h"
#include "core/PartitionModel.h"
#include "jobs/PartitionJob.h"

#include "Job.h"
#include "partition/KPMManager.h"

// KPMcore
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partitiontable.h>

// Qt
#include <QList>
#include <QMutex>
#include <QObject>

#include <functional>

class BootLoaderModel;
class Config;
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
     * This helper class calls refresh() on the module
     * on destruction (nothing else). It is used as
     * part of the model-consistency objects, along with
     * PartitionModel::ResetHelper.
     */
    class RefreshHelper
    {
    public:
        RefreshHelper( PartitionCoreModule* module );
        ~RefreshHelper();

        RefreshHelper( const RefreshHelper& ) = delete;
        RefreshHelper& operator=( const RefreshHelper& ) = delete;

    private:
        PartitionCoreModule* m_module;
    };

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
    ~PartitionCoreModule() override;

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
    BootLoaderModel* bootLoaderModel() const;

    void createPartitionTable( Device* device, PartitionTable::TableType type );

    /**
     * @brief Add a job to do the actual partition-creation.
     *
     * If @p flags is not FlagNone, then the given flags are
     * applied to the newly-created partition.
     */
    void
    createPartition( Device* device, Partition* partition, PartitionTable::Flags flags = KPM_PARTITION_FLAG( None ) );

    void createVolumeGroup( QString& vgName, QVector< const Partition* > pvList, qint32 peSize );

    void resizeVolumeGroup( LvmDevice* device, QVector< const Partition* >& pvList );

    void deactivateVolumeGroup( LvmDevice* device );

    void removeVolumeGroup( LvmDevice* device );

    void deletePartition( Device* device, Partition* partition );

    void formatPartition( Device* device, Partition* partition );

    void setFilesystemLabel( Device* device, Partition* partition, const QString& newLabel );

    void resizePartition( Device* device, Partition* partition, qint64 first, qint64 last );

    void setPartitionFlags( Device* device, Partition* partition, PartitionTable::Flags flags );

    /// @brief Retrieve the path where the bootloader will be installed
    QString bootLoaderInstallPath() const { return m_bootLoaderInstallPath; }
    /// @brief Set the path where the bootloader will be installed
    void setBootLoaderInstallPath( const QString& path );

    /** @brief Initialize the default layout that will be applied
     *
     * See PartitionLayout::init()
     */
    void initLayout( FileSystem::Type defaultFsType, const QVariantList& config = QVariantList() );

    void layoutApply( Device* dev, qint64 firstSector, qint64 lastSector, QString luksPassphrase );
    void layoutApply( Device* dev,
                      qint64 firstSector,
                      qint64 lastSector,
                      QString luksPassphrase,
                      PartitionNode* parent,
                      const PartitionRole& role );

    /**
     * @brief jobs creates and returns a list of jobs which can then apply the changes
     * requested by the user.
     * @return a list of jobs.
     */
    Calamares::JobList jobs( const Config* ) const;

    bool hasRootMountPoint() const;

    QList< Partition* > efiSystemPartitions() const;

    QVector< const Partition* > lvmPVs() const;

    bool hasVGwithThisName( const QString& name ) const;

    bool isInVG( const Partition* partition ) const;

    /**
     * @brief findPartitionByMountPoint returns a Partition* for a given mount point.
     * @param mountPoint the mount point to find a partition for.
     * @return a pointer to a Partition object.
     * Note that this function looks for partitions in live devices (the "proposed"
     * state), not the immutable copies. Comparisons with Partition* objects that
     * refer to immutable Device*s will fail.
     */
    Partition* findPartitionByMountPoint( const QString& mountPoint ) const;

    void revert();  // full revert, thread safe, calls doInit
    void revertAllDevices();  // convenience function, calls revertDevice
    /** @brief rescans a single Device and updates DeviceInfo
     *
     * When @p individualRevert is true, calls refreshAfterModelChange(),
     * used to reduce number of refreshes when calling revertAllDevices().
     */
    void revertDevice( Device* dev, bool individualRevert = true );
    void asyncRevertDevice( Device* dev, std::function< void() > callback );  //like revertDevice, but asynchronous

    void clearJobs();  // only clear jobs, the Device* states are preserved

    bool isDirty();  // true if there are pending changes, otherwise false

    bool isVGdeactivated( LvmDevice* device );

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

    const OsproberEntryList osproberEntries() const;  // os-prober data structure, cached

    void dumpQueue() const;  // debug output

Q_SIGNALS:
    void hasRootMountPointChanged( bool value );
    void isDirtyChanged( bool value );
    void reverted();
    void deviceReverted( Device* device );

private:
    struct DeviceInfo;
    void refreshAfterModelChange();

    void doInit();
    void updateHasRootMountPoint();
    void updateIsDirty();
    void scanForEfiSystemPartitions();
    void scanForLVMPVs();

    DeviceInfo* infoForDevice( const Device* ) const;

    CalamaresUtils::Partition::KPMManager m_kpmcore;

    QList< DeviceInfo* > m_deviceInfos;
    QList< Partition* > m_efiSystemPartitions;
    QVector< const Partition* > m_lvmPVs;

    DeviceModel* m_deviceModel;
    BootLoaderModel* m_bootLoaderModel;
    bool m_hasRootMountPoint = false;
    bool m_isDirty = false;
    QString m_bootLoaderInstallPath;
    PartitionLayout m_partLayout;

    OsproberEntryList m_osproberLines;

    QMutex m_revertMutex;
};

#endif /* PARTITIONCOREMODULE_H */
