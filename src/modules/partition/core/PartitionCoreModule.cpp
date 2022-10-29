/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2018 Caio Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/PartitionCoreModule.h"

#include "core/BootLoaderModel.h"
#include "core/ColorUtils.h"
#include "core/DeviceList.h"
#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "core/PartitionInfo.h"
#include "core/PartitionModel.h"
#include "jobs/AutoMountManagementJob.h"
#include "jobs/ChangeFilesystemLabelJob.h"
#include "jobs/ClearMountsJob.h"
#include "jobs/ClearTempMountsJob.h"
#include "jobs/CreatePartitionJob.h"
#include "jobs/CreatePartitionTableJob.h"
#include "jobs/CreateVolumeGroupJob.h"
#include "jobs/DeactivateVolumeGroupJob.h"
#include "jobs/DeletePartitionJob.h"
#include "jobs/FillGlobalStorageJob.h"
#include "jobs/FormatPartitionJob.h"
#include "jobs/RemoveVolumeGroupJob.h"
#include "jobs/ResizePartitionJob.h"
#include "jobs/ResizeVolumeGroupJob.h"
#include "jobs/SetPartitionFlagsJob.h"

#ifdef DEBUG_PARTITION_BAIL_OUT
#include "JobExample.h"
#endif
#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"
#include "utils/Traits.h"
#include "utils/Variant.h"

// KPMcore
#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/volumemanagerdevice.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/fs/luks.h>
#include <kpmcore/fs/lvm2_pv.h>

// Qt
#include <QDir>
#include <QFutureWatcher>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrent>

using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::isPartitionNew;
using CalamaresUtils::Partition::PartitionIterator;

PartitionCoreModule::RefreshHelper::RefreshHelper( PartitionCoreModule* module )
    : m_module( module )
{
}

PartitionCoreModule::RefreshHelper::~RefreshHelper()
{
    m_module->refreshAfterModelChange();
}

class OperationHelper
{
public:
    OperationHelper( PartitionModel* model, PartitionCoreModule* core )
        : m_coreHelper( core )
        , m_modelHelper( model )
    {
    }

    OperationHelper( const OperationHelper& ) = delete;
    OperationHelper& operator=( const OperationHelper& ) = delete;

private:
    // Keep these in order: first the model needs to finish,
    // then refresh is called. Remember that destructors are
    // called in *reverse* order of declaration in this class.
    PartitionCoreModule::RefreshHelper m_coreHelper;
    PartitionModel::ResetHelper m_modelHelper;
};


//- DeviceInfo ---------------------------------------------
// Some jobs have an updatePreview some don't
DECLARE_HAS_METHOD( updatePreview )

template < typename Job >
void
updatePreview( Job* job, const std::true_type& )
{
    job->updatePreview();
}

template < typename Job >
void
updatePreview( Job*, const std::false_type& )
{
}

template < typename Job >
void
updatePreview( Job* job )
{
    updatePreview( job, has_updatePreview< Job > {} );
}

/**
 * Owns the Device, PartitionModel and the jobs
 */
struct PartitionCoreModule::DeviceInfo
{
    DeviceInfo( Device* );
    ~DeviceInfo();
    QScopedPointer< Device > device;
    QScopedPointer< PartitionModel > partitionModel;
    const QScopedPointer< Device > immutableDevice;

    // To check if LVM VGs are deactivated
    bool isAvailable;

    void forgetChanges();
    bool isDirty() const;

    const Calamares::JobList& jobs() const { return m_jobs; }

    /** @brief Take the jobs of the given type that apply to @p partition
     *
     * Returns a job pointer to the job that has just been removed.
     */
    template < typename Job >
    Calamares::job_ptr takeJob( Partition* partition )
    {
        for ( auto it = m_jobs.begin(); it != m_jobs.end(); )
        {
            Job* job = qobject_cast< Job* >( it->data() );
            if ( job && job->partition() == partition )
            {
                Calamares::job_ptr p = *it;
                it = m_jobs.erase( it );
                return p;
            }
            else
            {
                ++it;
            }
        }

        return Calamares::job_ptr( nullptr );
    }

    /** @brief Add a job of given type to the job list
     */
    template < typename Job, typename... Args >
    Calamares::Job* makeJob( Args... a )
    {
        auto* job = new Job( device.get(), a... );
        updatePreview( job );
        m_jobs << Calamares::job_ptr( job );
        return job;
    }

private:
    Calamares::JobList m_jobs;
};


PartitionCoreModule::DeviceInfo::DeviceInfo( Device* _device )
    : device( _device )
    , partitionModel( new PartitionModel )
    , immutableDevice( new Device( *_device ) )
    , isAvailable( true )
{
}

PartitionCoreModule::DeviceInfo::~DeviceInfo() {}


void
PartitionCoreModule::DeviceInfo::forgetChanges()
{
    m_jobs.clear();
    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
    {
        PartitionInfo::reset( *it );
    }
    partitionModel->revert();
}


bool
PartitionCoreModule::DeviceInfo::isDirty() const
{
    if ( !m_jobs.isEmpty() )
    {
        return true;
    }

    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
    {
        if ( PartitionInfo::isDirty( *it ) )
        {
            return true;
        }
    }

    return false;
}

//- PartitionCoreModule ------------------------------------
PartitionCoreModule::PartitionCoreModule( QObject* parent )
    : QObject( parent )
    , m_deviceModel( new DeviceModel( this ) )
    , m_bootLoaderModel( new BootLoaderModel( this ) )
{
    if ( !m_kpmcore )
    {
        qFatal( "Failed to initialize KPMcore backend" );
    }
}


void
PartitionCoreModule::init()
{
    QMutexLocker locker( &m_revertMutex );
    doInit();
}


void
PartitionCoreModule::doInit()
{
    FileSystemFactory::init();

    using DeviceList = QList< Device* >;
    DeviceList devices = PartUtils::getDevices( PartUtils::DeviceType::WritableOnly );

    cDebug() << "LIST OF DETECTED DEVICES:";
    cDebug() << Logger::SubEntry << "node\tcapacity\tname\tprettyName";
    for ( auto device : devices )
    {
        if ( device )
        {
            // Gives ownership of the Device* to the DeviceInfo object
            auto deviceInfo = new DeviceInfo( device );
            m_deviceInfos << deviceInfo;
            cDebug() << Logger::SubEntry << device->deviceNode() << device->capacity()
                     << Logger::RedactedName( "DevName", device->name() )
                     << Logger::RedactedName( "DevNamePretty", device->prettyName() );
        }
        else
        {
            cDebug() << Logger::SubEntry << "(skipped null device)";
        }
    }
    cDebug() << Logger::SubEntry << devices.count() << "devices detected.";
    m_deviceModel->init( devices );

    // The following PartUtils::runOsprober call in turn calls PartUtils::canBeResized,
    // which relies on a working DeviceModel.
    m_osproberLines = PartUtils::runOsprober( this->deviceModel() );

    // We perform a best effort of filling out filesystem UUIDs in m_osproberLines
    // because we will need them later on in PartitionModel if partition paths
    // change.
    // It is a known fact that /dev/sda1-style device paths aren't persistent
    // across reboots (and this doesn't affect us), but partition numbers can also
    // change at runtime against our will just for shits and giggles.
    // But why would that ever happen? What system could possibly be so poorly
    // designed that it requires a partition path rearrangement at runtime?
    // Logical partitions on an MSDOS disklabel of course.
    // See DeletePartitionJob::updatePreview.
    for ( auto deviceInfo : m_deviceInfos )
    {
        for ( auto it = PartitionIterator::begin( deviceInfo->device.data() );
              it != PartitionIterator::end( deviceInfo->device.data() );
              ++it )
        {
            Partition* partition = *it;
            for ( auto jt = m_osproberLines.begin(); jt != m_osproberLines.end(); ++jt )
            {
                if ( jt->path == partition->partitionPath()
                     && partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
                     && !partition->fileSystem().uuid().isEmpty() )
                {
                    jt->uuid = partition->fileSystem().uuid();
                }
            }
        }
    }

    for ( auto deviceInfo : m_deviceInfos )
    {
        deviceInfo->partitionModel->init( deviceInfo->device.data(), m_osproberLines );
    }

    DeviceList bootLoaderDevices;

    for ( DeviceList::Iterator it = devices.begin(); it != devices.end(); ++it )
        if ( ( *it )->type() != Device::Type::Disk_Device )
        {
            cDebug() << "Ignoring device that is not Disk_Device to bootLoaderDevices list.";
            continue;
        }
        else
        {
            bootLoaderDevices.append( *it );
        }

    m_bootLoaderModel->init( bootLoaderDevices );

    scanForLVMPVs();

    //FIXME: this should be removed in favor of
    //       proper KPM support for EFI
    if ( PartUtils::isEfiSystem() )
    {
        scanForEfiSystemPartitions();
    }
}

PartitionCoreModule::~PartitionCoreModule()
{
    qDeleteAll( m_deviceInfos );
}

DeviceModel*
PartitionCoreModule::deviceModel() const
{
    return m_deviceModel;
}

BootLoaderModel*
PartitionCoreModule::bootLoaderModel() const
{
    return m_bootLoaderModel;
}

PartitionModel*
PartitionCoreModule::partitionModelForDevice( const Device* device ) const
{
    DeviceInfo* info = infoForDevice( device );
    Q_ASSERT( info );
    return info->partitionModel.data();
}


Device*
PartitionCoreModule::immutableDeviceCopy( const Device* device )
{
    Q_ASSERT( device );
    DeviceInfo* info = infoForDevice( device );
    if ( !info )
    {
        return nullptr;
    }

    return info->immutableDevice.data();
}


void
PartitionCoreModule::createPartitionTable( Device* device, PartitionTable::TableType type )
{
    auto* deviceInfo = infoForDevice( device );
    if ( deviceInfo )
    {
        // Creating a partition table wipes all the disk, so there is no need to
        // keep previous changes
        deviceInfo->forgetChanges();

        OperationHelper helper( partitionModelForDevice( device ), this );
        deviceInfo->makeJob< CreatePartitionTableJob >( type );
    }
}

void
PartitionCoreModule::createPartition( Device* device, Partition* partition, PartitionTable::Flags flags )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    OperationHelper helper( partitionModelForDevice( device ), this );
    deviceInfo->makeJob< CreatePartitionJob >( partition );

    if ( flags != KPM_PARTITION_FLAG( None ) )
    {
        deviceInfo->makeJob< SetPartFlagsJob >( partition, flags );
        PartitionInfo::setFlags( partition, flags );
    }
}

void
PartitionCoreModule::createVolumeGroup( QString& vgName, QVector< const Partition* > pvList, qint32 peSize )
{
    // Appending '_' character in case of repeated VG name
    while ( hasVGwithThisName( vgName ) )
    {
        vgName.append( '_' );
    }

    LvmDevice* device = new LvmDevice( vgName );
    for ( const Partition* p : pvList )
    {
        device->physicalVolumes() << p;
    }

    DeviceInfo* deviceInfo = new DeviceInfo( device );
    deviceInfo->partitionModel->init( device, osproberEntries() );
    m_deviceModel->addDevice( device );
    m_deviceInfos << deviceInfo;

    deviceInfo->makeJob< CreateVolumeGroupJob >( vgName, pvList, peSize );
    refreshAfterModelChange();
}

void
PartitionCoreModule::resizeVolumeGroup( LvmDevice* device, QVector< const Partition* >& pvList )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    deviceInfo->makeJob< ResizeVolumeGroupJob >( device, pvList );
    refreshAfterModelChange();
}

void
PartitionCoreModule::deactivateVolumeGroup( LvmDevice* device )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    deviceInfo->isAvailable = false;

    // TODO: this leaks
    DeactivateVolumeGroupJob* job = new DeactivateVolumeGroupJob( device );

    // DeactivateVolumeGroupJob needs to be immediately called
    job->exec();

    refreshAfterModelChange();
}

void
PartitionCoreModule::removeVolumeGroup( LvmDevice* device )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    deviceInfo->makeJob< RemoveVolumeGroupJob >( device );
    refreshAfterModelChange();
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    OperationHelper helper( partitionModelForDevice( device ), this );

    if ( partition->roles().has( PartitionRole::Extended ) )
    {
        // Delete all logical partitions first
        // I am not sure if we can iterate on Partition::children() while
        // deleting them, so let's play it safe and keep our own list.
        QList< Partition* > lst;
        for ( auto childPartition : partition->children() )
            if ( !isPartitionFreeSpace( childPartition ) )
            {
                lst << childPartition;
            }

        for ( auto childPartition : lst )
        {
            deletePartition( device, childPartition );
        }
    }

    if ( partition->state() == KPM_PARTITION_STATE( New ) )
    {
        // Take all the SetPartFlagsJob from the list and delete them
        do
        {
            auto job_ptr = deviceInfo->takeJob< SetPartFlagsJob >( partition );
            if ( job_ptr.data() )
            {
                continue;
            }
        } while ( false );


        // Find matching CreatePartitionJob
        auto job_ptr = deviceInfo->takeJob< CreatePartitionJob >( partition );
        if ( !job_ptr.data() )
        {
            cDebug() << "Failed to find a CreatePartitionJob matching the partition to remove";
            return;
        }
        // Remove it
        if ( !partition->parent()->remove( partition ) )
        {
            cDebug() << "Failed to remove partition from preview";
            return;
        }

        device->partitionTable()->updateUnallocated( *device );
        // The partition is no longer referenced by either a job or the device
        // partition list, so we have to delete it
        delete partition;
    }
    else
    {
        // Remove any PartitionJob on this partition
        do
        {
            auto job_ptr = deviceInfo->takeJob< PartitionJob >( partition );
            if ( job_ptr.data() )
            {
                continue;
            }
        } while ( false );

        deviceInfo->makeJob< DeletePartitionJob >( partition );
    }
}

void
PartitionCoreModule::formatPartition( Device* device, Partition* partition )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    OperationHelper helper( partitionModelForDevice( device ), this );
    deviceInfo->makeJob< FormatPartitionJob >( partition );
}

void
PartitionCoreModule::setFilesystemLabel( Device* device, Partition* partition, const QString& newLabel )
{
    if ( newLabel.isEmpty() )
    {
        // Don't bother
        return;
    }
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    OperationHelper helper( partitionModelForDevice( device ), this );
    deviceInfo->makeJob< ChangeFilesystemLabelJob >( partition, newLabel );
}

void
PartitionCoreModule::resizePartition( Device* device, Partition* partition, qint64 first, qint64 last )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    OperationHelper helper( partitionModelForDevice( device ), this );
    deviceInfo->makeJob< ResizePartitionJob >( partition, first, last );
}

void
PartitionCoreModule::setPartitionFlags( Device* device, Partition* partition, PartitionTable::Flags flags )
{
    auto* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    OperationHelper( partitionModelForDevice( device ), this );
    deviceInfo->makeJob< SetPartFlagsJob >( partition, flags );
    PartitionInfo::setFlags( partition, flags );
}

STATICTEST QStringList
findEssentialLVs( const QList< PartitionCoreModule::DeviceInfo* >& infos )
{
    QStringList doNotClose;
    cDebug() << "Checking LVM use on" << infos.count() << "devices";
    for ( const auto* info : infos )
    {
        if ( info->device->type() != Device::Type::LVM_Device )
        {
            continue;
        }

        for ( const auto& j : qAsConst( info->jobs() ) )
        {
            FormatPartitionJob* format = dynamic_cast< FormatPartitionJob* >( j.data() );
            if ( format )
            {
                // device->deviceNode() is /dev/<vg name>
                // partition()->partitionPath() is /dev/<vg name>/<lv>
                const auto* partition = format->partition();
                const QString partPath = partition->partitionPath();
                const QString devicePath = info->device->deviceNode() + '/';
                const bool isLvm = partition->roles().has( PartitionRole::Lvm_Lv );
                if ( isLvm && partPath.startsWith( devicePath ) )
                {
                    cDebug() << Logger::SubEntry << partPath
                             << "is an essential LV filesystem=" << partition->fileSystem().type();
                    QString lvName = partPath.right( partPath.length() - devicePath.length() );
                    doNotClose.append( info->device->name() + '-' + lvName );
                }
            }
        }
    }
    return doNotClose;
}

Calamares::JobList
PartitionCoreModule::jobs( const Config* config ) const
{
    Calamares::JobList lst;
    QList< Device* > devices;

#ifdef DEBUG_PARTITION_UNSAFE
#ifdef DEBUG_PARTITION_BAIL_OUT
    cDebug() << "Unsafe partitioning is enabled.";
    cDebug() << Logger::SubEntry << "it has been lamed, and will fail.";
    lst << Calamares::job_ptr( new Calamares::FailJob( QStringLiteral( "Partition" ) ) );
#else
    cWarning() << "Unsafe partitioning is enabled.";
    cWarning() << Logger::SubEntry << "the unsafe actions will be executed.";
#endif
#endif

    // The automountControl job goes in the list twice: the first
    //   time it runs, it disables automount and remembers the old setting
    //   for automount; the second time it restores that old setting.
    Calamares::job_ptr automountControl( new AutoMountManagementJob( true /* disable automount */ ) );
    lst << automountControl;
    lst << Calamares::job_ptr( new ClearTempMountsJob() );

#ifdef DEBUG_PARTITION_SKIP
    cWarning() << "Partitioning actions are skipped.";
#else
    const QStringList doNotClose = findEssentialLVs( m_deviceInfos );

    for ( const auto* info : m_deviceInfos )
    {
        if ( info->isDirty() )
        {
            auto* job = new ClearMountsJob( info->device.data() );
            job->setMapperExceptions( doNotClose );
            lst << Calamares::job_ptr( job );
        }
    }
#endif

    for ( const auto* info : m_deviceInfos )
    {
#ifdef DEBUG_PARTITION_SKIP
        cWarning() << Logger::SubEntry << "Skipping jobs for" << info->device.data()->deviceNode();
#else
        lst << info->jobs();
#endif
        devices << info->device.data();
    }
    lst << Calamares::job_ptr( new FillGlobalStorageJob( config, devices, m_bootLoaderInstallPath ) );
    lst << automountControl;

    return lst;
}

bool
PartitionCoreModule::hasRootMountPoint() const
{
    return m_hasRootMountPoint;
}

QList< Partition* >
PartitionCoreModule::efiSystemPartitions() const
{
    return m_efiSystemPartitions;
}

QVector< const Partition* >
PartitionCoreModule::lvmPVs() const
{
    return m_lvmPVs;
}

bool
PartitionCoreModule::hasVGwithThisName( const QString& name ) const
{
    auto condition = [ name ]( DeviceInfo* d )
    { return dynamic_cast< LvmDevice* >( d->device.data() ) && d->device.data()->name() == name; };

    return std::find_if( m_deviceInfos.begin(), m_deviceInfos.end(), condition ) != m_deviceInfos.end();
}

bool
PartitionCoreModule::isInVG( const Partition* partition ) const
{
    auto condition = [ partition ]( DeviceInfo* d )
    {
        LvmDevice* vg = dynamic_cast< LvmDevice* >( d->device.data() );
        return vg && vg->physicalVolumes().contains( partition );
    };

    return std::find_if( m_deviceInfos.begin(), m_deviceInfos.end(), condition ) != m_deviceInfos.end();
}

void
PartitionCoreModule::dumpQueue() const
{
    cDebug() << "# Queue:";
    for ( auto info : m_deviceInfos )
    {
        cDebug() << Logger::SubEntry << "## Device:" << info->device->deviceNode();
        for ( const auto& job : info->jobs() )
        {
            cDebug() << Logger::SubEntry << "-" << job->metaObject()->className();
        }
    }
}


const OsproberEntryList
PartitionCoreModule::osproberEntries() const
{
    return m_osproberLines;
}

void
PartitionCoreModule::refreshPartition( Device* device, Partition* )
{
    // Keep it simple for now: reset the model. This can be improved to cause
    // the model to Q_EMIT dataChanged() for the affected row instead, avoiding
    // the loss of the current selection.
    auto model = partitionModelForDevice( device );
    Q_ASSERT( model );
    OperationHelper helper( model, this );
}

void
PartitionCoreModule::refreshAfterModelChange()
{
    updateHasRootMountPoint();
    updateIsDirty();
    m_bootLoaderModel->update();

    scanForLVMPVs();

    //FIXME: this should be removed in favor of
    //       proper KPM support for EFI
    if ( PartUtils::isEfiSystem() )
    {
        scanForEfiSystemPartitions();
    }
}

void
PartitionCoreModule::updateHasRootMountPoint()
{
    bool oldValue = m_hasRootMountPoint;
    m_hasRootMountPoint = findPartitionByMountPoint( "/" );

    if ( oldValue != m_hasRootMountPoint )
    {
        hasRootMountPointChanged( m_hasRootMountPoint );
    }
}

void
PartitionCoreModule::updateIsDirty()
{
    bool oldValue = m_isDirty;
    m_isDirty = false;
    for ( auto info : m_deviceInfos )
        if ( info->isDirty() )
        {
            m_isDirty = true;
            break;
        }
    if ( oldValue != m_isDirty )
    {
        isDirtyChanged( m_isDirty );
    }
}

void
PartitionCoreModule::scanForEfiSystemPartitions()
{
    const bool wasEmpty = m_efiSystemPartitions.isEmpty();

    m_efiSystemPartitions.clear();

    QList< Device* > devices;
    for ( int row = 0; row < deviceModel()->rowCount(); ++row )
    {
        Device* device = deviceModel()->deviceForIndex( deviceModel()->index( row ) );
        devices.append( device );
    }

    QList< Partition* > efiSystemPartitions
        = CalamaresUtils::Partition::findPartitions( devices, PartUtils::isEfiBootable );

    if ( efiSystemPartitions.isEmpty() )
    {
        cWarning() << "system is EFI but no EFI system partitions found.";
    }
    else if ( wasEmpty )
    {
        // But it isn't empty anymore, so whatever problem has been solved
        cDebug() << "system is EFI and new EFI system partition has been found.";
    }

    m_efiSystemPartitions = efiSystemPartitions;
}

void
PartitionCoreModule::scanForLVMPVs()
{
    m_lvmPVs.clear();

    QList< Device* > physicalDevices;
    QList< LvmDevice* > vgDevices;

    for ( DeviceInfo* deviceInfo : m_deviceInfos )
    {
        if ( deviceInfo->device.data()->type() == Device::Type::Disk_Device )
        {
            physicalDevices << deviceInfo->device.data();
        }
        else if ( deviceInfo->device.data()->type() == Device::Type::LVM_Device )
        {
            LvmDevice* device = dynamic_cast< LvmDevice* >( deviceInfo->device.data() );

            // Restoring physical volume list
            device->physicalVolumes().clear();

            vgDevices << device;
        }
    }

    VolumeManagerDevice::scanDevices( physicalDevices );
    for ( auto p : LVM::pvList::list() )
    {
        m_lvmPVs << p.partition().data();

        for ( LvmDevice* device : vgDevices )
            if ( p.vgName() == device->name() )
            {
                // Adding scanned VG to PV list
                device->physicalVolumes() << p.partition();
                break;
            }
    }

    for ( DeviceInfo* d : m_deviceInfos )
    {
        for ( const auto& job : d->jobs() )
        {
            // Including new LVM PVs
            CreatePartitionJob* partJob = dynamic_cast< CreatePartitionJob* >( job.data() );
            if ( partJob )
            {
                Partition* p = partJob->partition();

                if ( p->fileSystem().type() == FileSystem::Type::Lvm2_PV )
                {
                    m_lvmPVs << p;
                }
                else if ( p->fileSystem().type() == FileSystem::Type::Luks )
                {
                    // Encrypted LVM PVs
                    FileSystem* innerFS = static_cast< const FS::luks* >( &p->fileSystem() )->innerFS();

                    if ( innerFS && innerFS->type() == FileSystem::Type::Lvm2_PV )
                    {
                        m_lvmPVs << p;
                    }
                }
                else if ( p->fileSystem().type() == FileSystem::Type::Luks2 )
                {
                    // Encrypted LVM PVs
                    FileSystem* innerFS = static_cast< const FS::luks* >( &p->fileSystem() )->innerFS();

                    if ( innerFS && innerFS->type() == FileSystem::Type::Lvm2_PV )
                    {
                        m_lvmPVs << p;
                    }
                }
            }
        }
    }
}

PartitionCoreModule::DeviceInfo*
PartitionCoreModule::infoForDevice( const Device* device ) const
{
    for ( auto it = m_deviceInfos.constBegin(); it != m_deviceInfos.constEnd(); ++it )
    {
        if ( ( *it )->device.data() == device )
        {
            return *it;
        }
        if ( ( *it )->immutableDevice.data() == device )
        {
            return *it;
        }
    }
    return nullptr;
}

Partition*
PartitionCoreModule::findPartitionByMountPoint( const QString& mountPoint ) const
{
    for ( auto deviceInfo : m_deviceInfos )
    {
        Device* device = deviceInfo->device.data();
        for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
            if ( PartitionInfo::mountPoint( *it ) == mountPoint )
            {
                return *it;
            }
    }
    return nullptr;
}

void
PartitionCoreModule::setBootLoaderInstallPath( const QString& path )
{
    cDebug() << "PCM::setBootLoaderInstallPath" << path;
    m_bootLoaderInstallPath = path;
}

static void
applyDefaultLabel( Partition* p, bool ( *predicate )( const Partition* ), const QString& label )
{
    if ( p->label().isEmpty() && predicate( p ) )
    {
        p->setLabel( label );
    }
}

void
PartitionCoreModule::layoutApply( Device* dev,
                                  qint64 firstSector,
                                  qint64 lastSector,
                                  QString luksPassphrase,
                                  PartitionNode* parent,
                                  const PartitionRole& role )
{
    bool isEfi = PartUtils::isEfiSystem();
    QList< Partition* > partList
        = m_partLayout.createPartitions( dev, firstSector, lastSector, luksPassphrase, parent, role );

    // Partition::mountPoint() tells us where it is mounted **now**, while
    // PartitionInfo::mountPoint() says where it will be mounted in the target system.
    // .. the latter is more interesting.
    //
    // If we have a separate /boot, mark that one as bootable,
    // otherwise mark the root / as bootable.
    //
    // If the layout hasn't applied a label to the partition,
    //      apply a default label (to boot and root, at least).
    const auto is_boot = []( const Partition* p ) -> bool
    {
        const QString boot = QStringLiteral( "/boot" );
        return PartitionInfo::mountPoint( p ) == boot || p->mountPoint() == boot;
    };
    const auto is_root = []( const Partition* p ) -> bool
    {
        const QString root = QStringLiteral( "/" );
        return PartitionInfo::mountPoint( p ) == root || p->mountPoint() == root;
    };

    const bool separate_boot_partition
        = std::find_if( partList.constBegin(), partList.constEnd(), is_boot ) != partList.constEnd();
    for ( Partition* part : partList )
    {
        applyDefaultLabel( part, is_root, QStringLiteral( "root" ) );
        applyDefaultLabel( part, is_boot, QStringLiteral( "boot" ) );
        if ( ( separate_boot_partition && is_boot( part ) ) || ( !separate_boot_partition && is_root( part ) ) )
        {
            createPartition(
                dev, part, part->activeFlags() | ( isEfi ? KPM_PARTITION_FLAG( None ) : KPM_PARTITION_FLAG( Boot ) ) );
        }
        else
        {
            createPartition( dev, part );
        }
    }
}

void
PartitionCoreModule::layoutApply( Device* dev, qint64 firstSector, qint64 lastSector, QString luksPassphrase )
{
    layoutApply(
        dev, firstSector, lastSector, luksPassphrase, dev->partitionTable(), PartitionRole( PartitionRole::Primary ) );
}

void
PartitionCoreModule::revert()
{
    QMutexLocker locker( &m_revertMutex );
    qDeleteAll( m_deviceInfos );
    m_deviceInfos.clear();
    doInit();
    updateIsDirty();
    Q_EMIT reverted();
}


void
PartitionCoreModule::revertAllDevices()
{
    for ( auto it = m_deviceInfos.begin(); it != m_deviceInfos.end(); )
    {
        // In new VGs device info, there will be always a CreateVolumeGroupJob as the first job in jobs list
        if ( dynamic_cast< LvmDevice* >( ( *it )->device.data() ) )
        {
            ( *it )->isAvailable = true;

            if ( !( *it )->jobs().empty() )
            {
                CreateVolumeGroupJob* vgJob = dynamic_cast< CreateVolumeGroupJob* >( ( *it )->jobs().first().data() );

                if ( vgJob )
                {
                    vgJob->undoPreview();

                    ( *it )->forgetChanges();

                    m_deviceModel->removeDevice( ( *it )->device.data() );

                    it = m_deviceInfos.erase( it );

                    continue;
                }
            }
        }

        revertDevice( ( *it )->device.data(), false );
        ++it;
    }

    refreshAfterModelChange();
}


void
PartitionCoreModule::revertDevice( Device* dev, bool individualRevert )
{
    QMutexLocker locker( &m_revertMutex );
    DeviceInfo* devInfo = infoForDevice( dev );

    if ( !devInfo )
    {
        return;
    }
    devInfo->forgetChanges();
    CoreBackend* backend = CoreBackendManager::self()->backend();
    Device* newDev = backend->scanDevice( devInfo->device->deviceNode() );
    devInfo->device.reset( newDev );
    devInfo->partitionModel->init( newDev, m_osproberLines );

    m_deviceModel->swapDevice( dev, newDev );

    QList< Device* > devices;
    for ( DeviceInfo* const info : m_deviceInfos )
    {
        if ( info && !info->device.isNull() && info->device->type() == Device::Type::Disk_Device )
        {
            devices.append( info->device.data() );
        }
    }

    m_bootLoaderModel->init( devices );

    if ( individualRevert )
    {
        refreshAfterModelChange();
    }
    Q_EMIT deviceReverted( newDev );
}


void
PartitionCoreModule::asyncRevertDevice( Device* dev, std::function< void() > callback )
{
    QFutureWatcher< void >* watcher = new QFutureWatcher< void >();
    connect( watcher,
             &QFutureWatcher< void >::finished,
             this,
             [ watcher, callback ]
             {
                 callback();
                 watcher->deleteLater();
             } );

    QFuture< void > future = QtConcurrent::run( this, &PartitionCoreModule::revertDevice, dev, true );
    watcher->setFuture( future );
}


void
PartitionCoreModule::clearJobs()
{
    foreach ( DeviceInfo* deviceInfo, m_deviceInfos )
    {
        deviceInfo->forgetChanges();
    }
    updateIsDirty();
}


bool
PartitionCoreModule::isDirty()
{
    return m_isDirty;
}

bool
PartitionCoreModule::isVGdeactivated( LvmDevice* device )
{
    for ( DeviceInfo* deviceInfo : m_deviceInfos )
        if ( device == deviceInfo->device.data() && !deviceInfo->isAvailable )
        {
            return true;
        }

    return false;
}

QList< PartitionCoreModule::SummaryInfo >
PartitionCoreModule::createSummaryInfo() const
{
    QList< SummaryInfo > lst;
    for ( auto deviceInfo : m_deviceInfos )
    {
        if ( !deviceInfo->isDirty() )
        {
            continue;
        }
        SummaryInfo summaryInfo;
        summaryInfo.deviceName = deviceInfo->device->name();
        summaryInfo.deviceNode = deviceInfo->device->deviceNode();

        Device* deviceBefore = deviceInfo->immutableDevice.data();
        summaryInfo.partitionModelBefore = new PartitionModel;
        summaryInfo.partitionModelBefore->init( deviceBefore, m_osproberLines );
        // Make deviceBefore a child of partitionModelBefore so that it is not
        // leaked (as long as partitionModelBefore is deleted)
        deviceBefore->setParent( summaryInfo.partitionModelBefore );

        summaryInfo.partitionModelAfter = new PartitionModel;
        summaryInfo.partitionModelAfter->init( deviceInfo->device.data(), m_osproberLines );

        lst << summaryInfo;
    }
    return lst;
}
