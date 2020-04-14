/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Caio Carvalho <caiojcarvalho@gmail.com>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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

#include "core/PartitionCoreModule.h"

#include "core/BootLoaderModel.h"
#include "core/ColorUtils.h"
#include "core/DeviceList.h"
#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "core/PartitionInfo.h"
#include "core/PartitionModel.h"
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

#ifdef DEBUG_PARTITION_LAME
#include "JobExample.h"
#endif
#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"
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
#include <QProcess>
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
    jobs.clear();
    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
    {
        PartitionInfo::reset( *it );
    }
    partitionModel->revert();
}


bool
PartitionCoreModule::DeviceInfo::isDirty() const
{
    if ( !jobs.isEmpty() )
    {
        return true;
    }

    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
        if ( PartitionInfo::isDirty( *it ) )
        {
            return true;
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
    cDebug() << "node\tcapacity\tname\tprettyName";
    for ( auto device : devices )
    {
        // Gives ownership of the Device* to the DeviceInfo object
        auto deviceInfo = new DeviceInfo( device );
        m_deviceInfos << deviceInfo;
        cDebug() << device->deviceNode() << device->capacity() << device->name() << device->prettyName();
    }
    cDebug() << Logger::SubEntry << devices.count() << "devices detected.";
    m_deviceModel->init( devices );

    // The following PartUtils::runOsprober call in turn calls PartUtils::canBeResized,
    // which relies on a working DeviceModel.
    m_osproberLines = PartUtils::runOsprober( this );

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

QAbstractItemModel*
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
    DeviceInfo* info = infoForDevice( device );
    if ( info )
    {
        // Creating a partition table wipes all the disk, so there is no need to
        // keep previous changes
        info->forgetChanges();

        OperationHelper helper( partitionModelForDevice( device ), this );
        CreatePartitionTableJob* job = new CreatePartitionTableJob( device, type );
        job->updatePreview();
        info->jobs << Calamares::job_ptr( job );
    }
}

void
PartitionCoreModule::createPartition( Device* device, Partition* partition, PartitionTable::Flags flags )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    OperationHelper helper( partitionModelForDevice( device ), this );
    CreatePartitionJob* job = new CreatePartitionJob( device, partition );
    job->updatePreview();

    deviceInfo->jobs << Calamares::job_ptr( job );

    if ( flags != KPM_PARTITION_FLAG( None ) )
    {
        SetPartFlagsJob* fJob = new SetPartFlagsJob( device, partition, flags );
        deviceInfo->jobs << Calamares::job_ptr( fJob );
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

    CreateVolumeGroupJob* job = new CreateVolumeGroupJob( vgName, pvList, peSize );
    job->updatePreview();

    LvmDevice* device = new LvmDevice( vgName );

    for ( const Partition* p : pvList )
    {
        device->physicalVolumes() << p;
    }

    DeviceInfo* deviceInfo = new DeviceInfo( device );

    deviceInfo->partitionModel->init( device, osproberEntries() );

    m_deviceModel->addDevice( device );

    m_deviceInfos << deviceInfo;
    deviceInfo->jobs << Calamares::job_ptr( job );

    refreshAfterModelChange();
}

void
PartitionCoreModule::resizeVolumeGroup( LvmDevice* device, QVector< const Partition* >& pvList )
{
    DeviceInfo* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    ResizeVolumeGroupJob* job = new ResizeVolumeGroupJob( device, pvList );

    deviceInfo->jobs << Calamares::job_ptr( job );

    refreshAfterModelChange();
}

void
PartitionCoreModule::deactivateVolumeGroup( LvmDevice* device )
{
    DeviceInfo* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    deviceInfo->isAvailable = false;

    DeactivateVolumeGroupJob* job = new DeactivateVolumeGroupJob( device );

    // DeactivateVolumeGroupJob needs to be immediately called
    job->exec();

    refreshAfterModelChange();
}

void
PartitionCoreModule::removeVolumeGroup( LvmDevice* device )
{
    DeviceInfo* deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    RemoveVolumeGroupJob* job = new RemoveVolumeGroupJob( device );

    deviceInfo->jobs << Calamares::job_ptr( job );

    refreshAfterModelChange();
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
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

    Calamares::JobList& jobs = deviceInfo->jobs;
    if ( partition->state() == KPM_PARTITION_STATE( New ) )
    {
        // First remove matching SetPartFlagsJobs
        for ( auto it = jobs.begin(); it != jobs.end(); )
        {
            SetPartFlagsJob* job = qobject_cast< SetPartFlagsJob* >( it->data() );
            if ( job && job->partition() == partition )
            {
                it = jobs.erase( it );
            }
            else
            {
                ++it;
            }
        }

        // Find matching CreatePartitionJob
        auto it = std::find_if( jobs.begin(), jobs.end(), [partition]( Calamares::job_ptr job ) {
            CreatePartitionJob* createJob = qobject_cast< CreatePartitionJob* >( job.data() );
            return createJob && createJob->partition() == partition;
        } );
        if ( it == jobs.end() )
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
        jobs.erase( it );
        // The partition is no longer referenced by either a job or the device
        // partition list, so we have to delete it
        delete partition;
    }
    else
    {
        // Remove any PartitionJob on this partition
        for ( auto it = jobs.begin(); it != jobs.end(); )
        {
            PartitionJob* job = qobject_cast< PartitionJob* >( it->data() );
            if ( job && job->partition() == partition )
            {
                it = jobs.erase( it );
            }
            else
            {
                ++it;
            }
        }
        DeletePartitionJob* job = new DeletePartitionJob( device, partition );
        job->updatePreview();
        jobs << Calamares::job_ptr( job );
    }
}

void
PartitionCoreModule::formatPartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    OperationHelper helper( partitionModelForDevice( device ), this );

    FormatPartitionJob* job = new FormatPartitionJob( device, partition );
    deviceInfo->jobs << Calamares::job_ptr( job );
}

void
PartitionCoreModule::resizePartition( Device* device, Partition* partition, qint64 first, qint64 last )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    OperationHelper helper( partitionModelForDevice( device ), this );

    ResizePartitionJob* job = new ResizePartitionJob( device, partition, first, last );
    job->updatePreview();
    deviceInfo->jobs << Calamares::job_ptr( job );
}

void
PartitionCoreModule::setPartitionFlags( Device* device, Partition* partition, PartitionTable::Flags flags )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    OperationHelper( partitionModelForDevice( device ), this );

    SetPartFlagsJob* job = new SetPartFlagsJob( device, partition, flags );
    deviceInfo->jobs << Calamares::job_ptr( job );
    PartitionInfo::setFlags( partition, flags );
}

Calamares::JobList
PartitionCoreModule::jobs() const
{
    Calamares::JobList lst;
    QList< Device* > devices;

#ifdef DEBUG_PARTITION_UNSAFE
#ifdef DEBUG_PARTITION_LAME
    cDebug() << "Unsafe partitioning is enabled.";
    cDebug() << Logger::SubEntry << "it has been lamed, and will fail.";
    lst << Calamares::job_ptr( new Calamares::FailJob( QStringLiteral( "Partition" ) ) );
#else
    cWarning() << "Unsafe partitioning is enabled.";
    cWarning() << Logger::SubEntry << "the unsafe actions will be executed.";
#endif
#endif

    lst << Calamares::job_ptr( new ClearTempMountsJob() );

    for ( auto info : m_deviceInfos )
    {
        if ( info->isDirty() )
        {
            lst << Calamares::job_ptr( new ClearMountsJob( info->device.data() ) );
        }
    }

    for ( auto info : m_deviceInfos )
    {
        lst << info->jobs;
        devices << info->device.data();
    }
    lst << Calamares::job_ptr( new FillGlobalStorageJob( devices, m_bootLoaderInstallPath ) );

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
    auto condition = [name]( DeviceInfo* d ) {
        return dynamic_cast< LvmDevice* >( d->device.data() ) && d->device.data()->name() == name;
    };

    return std::find_if( m_deviceInfos.begin(), m_deviceInfos.end(), condition ) != m_deviceInfos.end();
}

bool
PartitionCoreModule::isInVG( const Partition* partition ) const
{
    auto condition = [partition]( DeviceInfo* d ) {
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
        cDebug() << "## Device:" << info->device->name();
        for ( auto job : info->jobs )
        {
            cDebug() << "-" << job->prettyName();
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
    // the model to emit dataChanged() for the affected row instead, avoiding
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

#if defined( WITH_KPMCORE4API )
    VolumeManagerDevice::scanDevices( physicalDevices );
    for ( auto p : LVM::pvList::list() )
#else
    LvmDevice::scanSystemLVM( physicalDevices );
    for ( auto p : LVM::pvList )
#endif
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
        for ( auto job : d->jobs )
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
#if defined( WITH_KPMCORE4API )
                else if ( p->fileSystem().type() == FileSystem::Type::Luks2 )
                {
                    // Encrypted LVM PVs
                    FileSystem* innerFS = static_cast< const FS::luks* >( &p->fileSystem() )->innerFS();

                    if ( innerFS && innerFS->type() == FileSystem::Type::Lvm2_PV )
                    {
                        m_lvmPVs << p;
                    }
                }
#endif
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

void
PartitionCoreModule::initLayout()
{
    m_partLayout = new PartitionLayout();

    m_partLayout->addEntry( QString( "/" ), QString( "100%" ) );
}

void
PartitionCoreModule::initLayout( const QVariantList& config )
{
    bool ok;
    QString sizeString;
    QString minSizeString;
    QString maxSizeString;

    m_partLayout = new PartitionLayout();

    for ( const auto& r : config )
    {
        QVariantMap pentry = r.toMap();

        if ( !pentry.contains( "name" ) || !pentry.contains( "mountPoint" ) || !pentry.contains( "filesystem" )
             || !pentry.contains( "size" ) )
        {
            cError() << "Partition layout entry #" << config.indexOf( r )
                     << "lacks mandatory attributes, switching to default layout.";
            delete ( m_partLayout );
            initLayout();
            break;
        }

        if ( pentry.contains( "size" ) && CalamaresUtils::getString( pentry, "size" ).isEmpty() )
        {
            sizeString.setNum( CalamaresUtils::getInteger( pentry, "size", 0 ) );
        }
        else
        {
            sizeString = CalamaresUtils::getString( pentry, "size" );
        }

        if ( pentry.contains( "minSize" ) && CalamaresUtils::getString( pentry, "minSize" ).isEmpty() )
        {
            minSizeString.setNum( CalamaresUtils::getInteger( pentry, "minSize", 0 ) );
        }
        else
        {
            minSizeString = CalamaresUtils::getString( pentry, "minSize" );
        }

        if ( pentry.contains( "maxSize" ) && CalamaresUtils::getString( pentry, "maxSize" ).isEmpty() )
        {
            maxSizeString.setNum( CalamaresUtils::getInteger( pentry, "maxSize", 0 ) );
        }
        else
        {
            maxSizeString = CalamaresUtils::getString( pentry, "maxSize" );
        }

        if ( !m_partLayout->addEntry( CalamaresUtils::getString( pentry, "name" ),
                                      CalamaresUtils::getString( pentry, "type" ),
                                      CalamaresUtils::getString( pentry, "mountPoint" ),
                                      CalamaresUtils::getString( pentry, "filesystem" ),
                                      CalamaresUtils::getSubMap( pentry, "features", ok ),
                                      sizeString,
                                      minSizeString,
                                      maxSizeString ) )
        {
            cError() << "Partition layout entry #" << config.indexOf( r ) << "is invalid, switching to default layout.";
            delete ( m_partLayout );
            initLayout();
            break;
        }
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
    QList< Partition* > partList = m_partLayout->execute( dev, firstSector, lastSector, luksPassphrase, parent, role );

    // Partition::mountPoint() tells us where it is mounted **now**, while
    // PartitionInfo::mountPoint() says where it will be mounted in the target system.
    // .. the latter is more interesting.
    //
    // If we have a separate /boot, mark that one as bootable, otherwise mark
    // the root / as bootable.
    //
    // TODO: perhaps the partition that holds the bootloader?
    const QString boot = QStringLiteral( "/boot" );
    const QString root = QStringLiteral( "/" );
    const auto is_boot
        = [&]( Partition* p ) -> bool { return PartitionInfo::mountPoint( p ) == boot || p->mountPoint() == boot; };
    const auto is_root
        = [&]( Partition* p ) -> bool { return PartitionInfo::mountPoint( p ) == root || p->mountPoint() == root; };

    const bool separate_boot_partition
        = std::find_if( partList.constBegin(), partList.constEnd(), is_boot ) != partList.constEnd();
    for ( Partition* part : partList )
    {
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
    emit reverted();
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

            if ( !( *it )->jobs.empty() )
            {
                CreateVolumeGroupJob* vgJob = dynamic_cast< CreateVolumeGroupJob* >( ( *it )->jobs[ 0 ].data() );

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
    emit deviceReverted( newDev );
}


void
PartitionCoreModule::asyncRevertDevice( Device* dev, std::function< void() > callback )
{
    QFutureWatcher< void >* watcher = new QFutureWatcher< void >();
    connect( watcher, &QFutureWatcher< void >::finished, this, [watcher, callback] {
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
