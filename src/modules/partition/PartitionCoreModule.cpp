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

#include <PartitionCoreModule.h>

#include <BootLoaderModel.h>
#include <CreatePartitionJob.h>
#include <CreatePartitionTableJob.h>
#include <DeletePartitionJob.h>
#include <FillGlobalStorageJob.h>
#include <FormatPartitionJob.h>
#include <DeviceModel.h>
#include <PartitionInfo.h>
#include <PartitionIterator.h>
#include <PartitionModel.h>
#include <PMUtils.h>
#include <Typedefs.h>
#include <utils/Logger.h>

// CalaPM
#include <CalaPM.h>
#include <core/device.h>
#include <core/partition.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>

// Qt
#include <QStandardItemModel>

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

//- PartitionCoreModule ------------------------------------
PartitionCoreModule::PartitionCoreModule( QObject* parent )
    : QObject( parent )
    , m_deviceModel( new DeviceModel( this ) )
    , m_bootLoaderModel( new BootLoaderModel( this ) )
{
    // FIXME: Should be done at startup
    if ( !CalaPM::init() )
        qFatal( "Failed to init CalaPM" );

    CoreBackend* backend = CoreBackendManager::self()->backend();
    auto devices = backend->scanDevices();
    for ( auto device : devices )
    {
        auto deviceInfo = new DeviceInfo( device );
        m_deviceInfos << deviceInfo;

        deviceInfo->partitionModel->init( device );
    }
    m_deviceModel->init( devices );

    m_bootLoaderModel->init( devices );
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

void
PartitionCoreModule::createPartitionTable( Device* device, PartitionTable::TableType type )
{
    DeviceInfo* info = infoForDevice( device );
    // Creating a partition table wipes all the disk, so there is no need to
    // keep previous changes
    info->forgetChanges();

    CreatePartitionTableJob* job = new CreatePartitionTableJob( device, type );
    job->updatePreview();
    info->jobs << Calamares::job_ptr( job );

    refresh( device );
}

void
PartitionCoreModule::createPartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    CreatePartitionJob* job = new CreatePartitionJob( device, partition );
    job->updatePreview();

    deviceInfo->jobs << Calamares::job_ptr( job );

    refresh( device );
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

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

    refresh( device );
}

void
PartitionCoreModule::formatPartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );

    FormatPartitionJob* job = new FormatPartitionJob( device, partition );
    deviceInfo->jobs << Calamares::job_ptr( job );

    refresh( device );
}

QList< Calamares::job_ptr >
PartitionCoreModule::jobs() const
{
    QList< Calamares::job_ptr > lst;
    QList< Device* > devices;
    for ( auto info : m_deviceInfos )
    {
        lst << info->jobs;
        devices << info->device.data();
    }
    lst << Calamares::job_ptr( new FillGlobalStorageJob( devices, m_bootLoaderInstallPath ) );
    return lst;
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
PartitionCoreModule::refresh( Device* device )
{
    auto model = partitionModelForDevice( device );
    Q_ASSERT( model );
    model->reload();
    updateHasRootMountPoint();
    m_bootLoaderModel->update();
}

void PartitionCoreModule::updateHasRootMountPoint()
{
    bool oldValue = m_hasRootMountPoint;
    m_hasRootMountPoint = findPartitionByMountPoint( "/" );

    if ( oldValue != m_hasRootMountPoint )
        hasRootMountPointChanged( m_hasRootMountPoint );
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
