/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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
#include "core/DeviceModel.h"
#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"
#include "core/PartitionModel.h"
#include "core/PMUtils.h"
#include "jobs/ClearMountsJob.h"
#include "jobs/ClearTempMountsJob.h"
#include "jobs/CreatePartitionJob.h"
#include "jobs/CreatePartitionTableJob.h"
#include "jobs/DeletePartitionJob.h"
#include "jobs/FillGlobalStorageJob.h"
#include "jobs/FormatPartitionJob.h"
#include "jobs/ResizePartitionJob.h"

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

static bool
hasRootPartition( Device* device )
{
    for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        if ( ( *it )->mountPoint() == "/" )
            return true;
    return false;
}

//- DeviceInfo ---------------------------------------------
PartitionCoreModule::DeviceInfo::DeviceInfo( Device* _device )
    : device( _device )
    , partitionModel( new PartitionModel )
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
    if ( !PMUtils::initKPMcore() )
        qFatal( "Failed to initialize KPMcore backend" );
    FileSystemFactory::init();
    init();
}

void
PartitionCoreModule::init()
{
    CoreBackend* backend = CoreBackendManager::self()->backend();
    auto devices = backend->scanDevices();

    // Remove the device which contains / from the list
    for ( auto it = devices.begin(); it != devices.end(); )
        if ( hasRootPartition( *it ) )
            it = devices.erase( it );
        else
            ++it;

    for ( auto device : devices )
    {
        auto deviceInfo = new DeviceInfo( device );
        m_deviceInfos << deviceInfo;

        deviceInfo->partitionModel->init( device );
    }
    m_deviceModel->init( devices );

    m_bootLoaderModel->init( devices );

    if ( QDir( "/sys/firmware/efi/efivars" ).exists() )
        scanForEfiSystemPartitions(); //FIXME: this should be removed in favor of
                                      //       proper KPM support for EFI
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
PartitionCoreModule::partitionModelForDevice( Device* device ) const
{
    DeviceInfo* info = infoForDevice( device );
    Q_ASSERT( info );
    return info->partitionModel.data();
}


Device*
PartitionCoreModule::createImmutableDeviceCopy( Device* device ) const
{
    CoreBackend* backend = CoreBackendManager::self()->backend();

    Device* deviceBefore = backend->scanDevice( device->deviceNode() );
    return deviceBefore;
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
PartitionCoreModule::createPartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );
    CreatePartitionJob* job = new CreatePartitionJob( device, partition );
    job->updatePreview();

    deviceInfo->jobs << Calamares::job_ptr( job );

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
            if ( !PMUtils::isPartitionFreeSpace( childPartition ) )
                lst << childPartition;

        for ( auto partition : lst )
            deletePartition( device, partition );
    }

    QList< Calamares::job_ptr >& jobs = deviceInfo->jobs;
    if ( partition->state() == Partition::StateNew )
    {
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
PartitionCoreModule::resizePartition( Device* device, Partition* partition, qint64 first, qint64 last )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    PartitionModel::ResetHelper helper( partitionModelForDevice( device ) );

    ResizePartitionJob* job = new ResizePartitionJob( device, partition, first, last );
    job->updatePreview();
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
    lst << Calamares::job_ptr( new FillGlobalStorageJob( devices, m_bootLoaderInstallPath ) );


    QStringList jobsDebug;
    foreach ( auto job, lst )
    {
        jobsDebug.append( job->prettyName() );
    }

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

void
PartitionCoreModule::refreshPartition( Device* device, Partition* partition )
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

    //FIXME: Unfortunately right now we have to call sgdisk manually because
    //       the KPM submodule does not expose the ESP flag from libparted.
    //       The following findPartitions call and lambda should be scrapped and
    //       rewritten based on libKPM.     -- Teo 5/2015
    QList< Partition* > efiSystemPartitions =
        PMUtils::findPartitions( devices,
                                 []( Partition* partition ) -> bool
    {
        QProcess process;
        process.setProgram( "sgdisk" );
        process.setArguments( { "-i",
                                QString::number( partition->number() ),
                                partition->devicePath() } );
        process.setProcessChannelMode( QProcess::MergedChannels );
        process.start();
        if ( process.waitForFinished() )
        {
            if ( process.readAllStandardOutput()
                    .contains( "C12A7328-F81F-11D2-BA4B-00A0C93EC93B" ) )
            {
                cDebug() << "Found EFI system partition at" << partition->partitionPath();
                return true;
            }
        }
        return false;
    } );

    if ( efiSystemPartitions.isEmpty() )
        cDebug() << "WARNING: system is EFI but no EFI system partitions found.";

    m_efiSystemPartitions = efiSystemPartitions;
}

PartitionCoreModule::DeviceInfo*
PartitionCoreModule::infoForDevice( Device* device ) const
{
    for ( auto deviceInfo : m_deviceInfos )
    {
        if ( deviceInfo->device.data() == device )
            return deviceInfo;
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
    m_bootLoaderInstallPath = path;
}

void
PartitionCoreModule::revert()
{
    qDeleteAll( m_deviceInfos );
    m_deviceInfos.clear();
    init();
    updateIsDirty();
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

QList< PartitionCoreModule::SummaryInfo >
PartitionCoreModule::createSummaryInfo() const
{
    QList< SummaryInfo > lst;
    CoreBackend* backend = CoreBackendManager::self()->backend();
    for ( auto deviceInfo : m_deviceInfos )
    {
        if ( !deviceInfo->isDirty() )
            continue;
        SummaryInfo summaryInfo;
        summaryInfo.deviceName = deviceInfo->device->name();
        summaryInfo.deviceNode = deviceInfo->device->deviceNode();

        Device* deviceBefore = backend->scanDevice( deviceInfo->device->deviceNode() );
        summaryInfo.partitionModelBefore = new PartitionModel;
        summaryInfo.partitionModelBefore->init( deviceBefore );
        // Make deviceBefore a child of partitionModelBefore so that it is not
        // leaked (as long as partitionModelBefore is deleted)
        deviceBefore->setParent( summaryInfo.partitionModelBefore );

        summaryInfo.partitionModelAfter = new PartitionModel;
        summaryInfo.partitionModelAfter->init( deviceInfo->device.data() );

        lst << summaryInfo;
    }
    return lst;
}
