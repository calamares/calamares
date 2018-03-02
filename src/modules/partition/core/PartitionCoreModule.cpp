/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"
#include "core/PartitionModel.h"
#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "jobs/ClearMountsJob.h"
#include "jobs/ClearTempMountsJob.h"
#include "jobs/CreatePartitionJob.h"
#include "jobs/CreatePartitionTableJob.h"
#include "jobs/DeletePartitionJob.h"
#include "jobs/FillGlobalStorageJob.h"
#include "jobs/FormatPartitionJob.h"
#include "jobs/ResizePartitionJob.h"
#include "jobs/SetPartitionFlagsJob.h"

#include "Typedefs.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/fs/filesystemfactory.h>

// Qt
#include <QStandardItemModel>
#include <QDir>
#include <QProcess>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

//- DeviceInfo ---------------------------------------------
PartitionCoreModule::DeviceInfo::DeviceInfo( Device* _device )
    : device( _device )
    , partitionModel( new PartitionModel )
    , immutableDevice( new Device( *_device ) )
{}

PartitionCoreModule::DeviceInfo::~DeviceInfo()
{
}


void
PartitionCoreModule::DeviceInfo::forgetChanges()
{
    jobs.clear();
    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
        PartitionInfo::reset( *it );
    partitionModel->revert();
}


bool
PartitionCoreModule::DeviceInfo::isDirty() const
{
    if ( !jobs.isEmpty() )
        return true;

    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
        if ( PartitionInfo::isDirty( *it ) )
            return true;

    return false;
}

//- PartitionCoreModule ------------------------------------
PartitionCoreModule::PartitionCoreModule( QObject* parent )
    : QObject( parent )
    , m_deviceModel( new DeviceModel( this ) )
    , m_bootLoaderModel( new BootLoaderModel( this ) )
{
    if ( !KPMHelpers::initKPMcore() )
        qFatal( "Failed to initialize KPMcore backend" );
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
    cDebug() << ".." << devices.count() << "devices detected.";
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
                it != PartitionIterator::end( deviceInfo->device.data() ); ++it )
        {
            Partition* partition = *it;
            for ( auto jt = m_osproberLines.begin();
                    jt != m_osproberLines.end(); ++jt )
            {
                if ( jt->path == partition->partitionPath() &&
                        partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone &&
                        !partition->fileSystem().uuid().isEmpty() )
                    jt->uuid = partition->fileSystem().uuid();
            }
        }
    }

    for ( auto deviceInfo : m_deviceInfos )
        deviceInfo->partitionModel->init( deviceInfo->device.data(), m_osproberLines );

    m_bootLoaderModel->init( devices );

    //FIXME: this should be removed in favor of
    //       proper KPM support for EFI
    if ( PartUtils::isEfiSystem() )
        scanForEfiSystemPartitions();
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
        return nullptr;

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

        PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );
        CreatePartitionTableJob* job = new CreatePartitionTableJob( device, type );
        job->updatePreview();
        info->jobs << Calamares::job_ptr( job );
    }

    refresh();
}

void
PartitionCoreModule::createPartition( Device* device,
                                      Partition* partition,
                                      PartitionTable::Flags flags )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );
    CreatePartitionJob* job = new CreatePartitionJob( device, partition );
    job->updatePreview();

    deviceInfo->jobs << Calamares::job_ptr( job );

    if ( flags != PartitionTable::FlagNone )
    {
        SetPartFlagsJob* fJob = new SetPartFlagsJob( device, partition, flags );
        deviceInfo->jobs << Calamares::job_ptr( fJob );
    }

    refresh();
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );

    if ( partition->roles().has( PartitionRole::Extended ) )
    {
        // Delete all logical partitions first
        // I am not sure if we can iterate on Partition::children() while
        // deleting them, so let's play it safe and keep our own list.
        QList< Partition* > lst;
        for ( auto childPartition : partition->children() )
            if ( !KPMHelpers::isPartitionFreeSpace( childPartition ) )
                lst << childPartition;

        for ( auto childPartition : lst )
            deletePartition( device, childPartition );
    }

    QList< Calamares::job_ptr >& jobs = deviceInfo->jobs;
    if ( partition->state() == Partition::StateNew )
    {
        // First remove matching SetPartFlagsJobs
        for ( auto it = jobs.begin(); it != jobs.end(); )
        {
            SetPartFlagsJob* job = qobject_cast< SetPartFlagsJob* >( it->data() );
            if ( job && job->partition() == partition )
                it = jobs.erase( it );
            else
                ++it;
        }

        // Find matching CreatePartitionJob
        auto it = std::find_if( jobs.begin(), jobs.end(), [ partition ]( Calamares::job_ptr job )
        {
            CreatePartitionJob* createJob = qobject_cast< CreatePartitionJob* >( job.data() );
            return createJob && createJob->partition() == partition;
        } );
        if ( it == jobs.end() )
        {
            cDebug() << "Failed to find a CreatePartitionJob matching the partition to remove";
            return;
        }
        // Remove it
        if ( ! partition->parent()->remove( partition ) )
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
                it = jobs.erase( it );
            else
                ++it;
        }
        DeletePartitionJob* job = new DeletePartitionJob( device, partition );
        job->updatePreview();
        jobs << Calamares::job_ptr( job );
    }

    refresh();
}

void
PartitionCoreModule::formatPartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );

    FormatPartitionJob* job = new FormatPartitionJob( device, partition );
    deviceInfo->jobs << Calamares::job_ptr( job );

    refresh();
}

void
PartitionCoreModule::resizePartition( Device* device,
                                      Partition* partition,
                                      qint64 first,
                                      qint64 last )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );

    ResizePartitionJob* job = new ResizePartitionJob( device, partition, first, last );
    job->updatePreview();
    deviceInfo->jobs << Calamares::job_ptr( job );

    refresh();
}

void
PartitionCoreModule::setPartitionFlags( Device* device,
                                        Partition* partition,
                                        PartitionTable::Flags flags )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    PartitionModel::ResetHelper( partitionModelForDevice( device ) );

    SetPartFlagsJob* job = new SetPartFlagsJob( device, partition, flags );

    deviceInfo->jobs << Calamares::job_ptr( job );

    refresh();
}

QList< Calamares::job_ptr >
PartitionCoreModule::jobs() const
{
    QList< Calamares::job_ptr > lst;
    QList< Device* > devices;

    lst << Calamares::job_ptr( new ClearTempMountsJob() );

    for ( auto info : m_deviceInfos )
    {
        if ( info->isDirty() )
            lst << Calamares::job_ptr( new ClearMountsJob( info->device.data() ) );
    }

    for ( auto info : m_deviceInfos )
    {
        lst << info->jobs;
        devices << info->device.data();
    }
    cDebug() << "Creating FillGlobalStorageJob with bootLoader path" << m_bootLoaderInstallPath;
    lst << Calamares::job_ptr( new FillGlobalStorageJob( devices, m_bootLoaderInstallPath ) );


    QStringList jobsDebug;
    foreach ( auto job, lst )
        jobsDebug.append( job->prettyName() );

    cDebug() << "PartitionCodeModule has been asked for jobs. About to return:"
             << jobsDebug.join( "\n" );

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

void
PartitionCoreModule::dumpQueue() const
{
    cDebug() << "# Queue:";
    for ( auto info : m_deviceInfos )
    {
        cDebug() << "## Device:" << info->device->name();
        for ( auto job : info->jobs )
            cDebug() << "-" << job->prettyName();
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
    PartitionModel::ResetHelper helper( model );

    refresh();
}

void
PartitionCoreModule::refresh()
{
    updateHasRootMountPoint();
    updateIsDirty();
    m_bootLoaderModel->update();

    //FIXME: this should be removed in favor of
    //       proper KPM support for EFI
    if ( PartUtils::isEfiSystem() )
        scanForEfiSystemPartitions();
}

void PartitionCoreModule::updateHasRootMountPoint()
{
    bool oldValue = m_hasRootMountPoint;
    m_hasRootMountPoint = findPartitionByMountPoint( "/" );

    if ( oldValue != m_hasRootMountPoint )
        hasRootMountPointChanged( m_hasRootMountPoint );
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
        isDirtyChanged( m_isDirty );
}

void
PartitionCoreModule::scanForEfiSystemPartitions()
{
    m_efiSystemPartitions.clear();

    QList< Device* > devices;
    for ( int row = 0; row < deviceModel()->rowCount(); ++row )
    {
        Device* device = deviceModel()->deviceForIndex(
                             deviceModel()->index( row ) );
        devices.append( device );
    }

    QList< Partition* > efiSystemPartitions =
        KPMHelpers::findPartitions( devices, PartUtils::isEfiBootable );

    if ( efiSystemPartitions.isEmpty() )
        cWarning() << "system is EFI but no EFI system partitions found.";

    m_efiSystemPartitions = efiSystemPartitions;
}

PartitionCoreModule::DeviceInfo*
PartitionCoreModule::infoForDevice( const Device* device ) const
{
    for ( auto it = m_deviceInfos.constBegin();
            it != m_deviceInfos.constEnd(); ++it )
    {
        if ( ( *it )->device.data() == device )
            return *it;
        if ( ( *it )->immutableDevice.data() == device )
            return *it;
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
                return *it;
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
    foreach ( DeviceInfo* devInfo, m_deviceInfos )
        revertDevice( devInfo->device.data() );
    refresh();
}


void
PartitionCoreModule::revertDevice( Device* dev )
{
    QMutexLocker locker( &m_revertMutex );
    DeviceInfo* devInfo = infoForDevice( dev );
    if ( !devInfo )
        return;
    devInfo->forgetChanges();
    CoreBackend* backend = CoreBackendManager::self()->backend();
    Device* newDev = backend->scanDevice( devInfo->device->deviceNode() );
    devInfo->device.reset( newDev );
    devInfo->partitionModel->init( newDev, m_osproberLines );

    m_deviceModel->swapDevice( dev, newDev );

    QList< Device* > devices;
    foreach ( auto info, m_deviceInfos )
        devices.append( info->device.data() );

    m_bootLoaderModel->init( devices );

    refresh();
    emit deviceReverted( newDev );
}


void
PartitionCoreModule::asyncRevertDevice( Device* dev, std::function< void() > callback )
{
    QFutureWatcher< void >* watcher = new QFutureWatcher< void >();
    connect( watcher, &QFutureWatcher< void >::finished,
             this, [ watcher, callback ]
    {
        callback();
        watcher->deleteLater();
    } );

    QFuture< void > future = QtConcurrent::run( this, &PartitionCoreModule::revertDevice, dev );
    watcher->setFuture( future );
}


void
PartitionCoreModule::clearJobs()
{
    foreach ( DeviceInfo* deviceInfo, m_deviceInfos )
        deviceInfo->forgetChanges();
    updateIsDirty();
}


bool
PartitionCoreModule::isDirty()
{
    return m_isDirty;
}

QList< PartitionCoreModule::SummaryInfo >
PartitionCoreModule::createSummaryInfo() const
{
    QList< SummaryInfo > lst;
    for ( auto deviceInfo : m_deviceInfos )
    {
        if ( !deviceInfo->isDirty() )
            continue;
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
