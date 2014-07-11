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

#include <CreatePartitionJob.h>
#include <CreatePartitionTableJob.h>
#include <DeletePartitionJob.h>
#include <DeviceModel.h>
#include <PartitionModel.h>
#include <Typedefs.h>
#include <utils/Logger.h>

// CalaPM
#include <CalaPM.h>
#include <core/device.h>
#include <core/partition.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>


//- DeviceInfo ---------------------------------------------
PartitionCoreModule::DeviceInfo::DeviceInfo( Device* _device )
    : device( _device )
    , partitionModel( new PartitionModel )
{}

//- PartitionCoreModule ------------------------------------
PartitionCoreModule::PartitionCoreModule( QObject* parent )
    : QObject( parent )
    , m_deviceModel( new DeviceModel( this ) )
{
    // FIXME: Should be done at startup
    if ( !CalaPM::init() )
    {
        qFatal( "Failed to init CalaPM" );
    }

    CoreBackend* backend = CoreBackendManager::self()->backend();
    auto devices = backend->scanDevices();
    for ( auto device : devices )
    {
        auto deviceInfo = new DeviceInfo( device );
        m_deviceInfos << deviceInfo;

        deviceInfo->partitionModel->init( device, &m_infoForPartitionHash );
    }
    m_deviceModel->init( devices );

}

PartitionCoreModule::~PartitionCoreModule()
{
    qDeleteAll( m_infoForPartitionHash );
    qDeleteAll( m_deviceInfos );
}

DeviceModel*
PartitionCoreModule::deviceModel() const
{
    return m_deviceModel;
}

PartitionModel*
PartitionCoreModule::partitionModelForDevice( Device* device ) const
{
    DeviceInfo* info = infoForDevice( device );
    Q_ASSERT( info );
    return info->partitionModel.data();
}

void
PartitionCoreModule::createPartitionTable( Device* device )
{
    CreatePartitionTableJob* job = new CreatePartitionTableJob( device );
    job->updatePreview();
    refreshPartitionModel( device );

    // FIXME: Remove all jobs queued for this device, as well as all partition
    // info
    infoForDevice( device )->jobs << Calamares::job_ptr( job );
    updateHasRootMountPoint();
}

void
PartitionCoreModule::createPartition( Device* device, PartitionInfo* partitionInfo )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    auto partition = partitionInfo->partition;
    Q_ASSERT( !m_infoForPartitionHash.contains( partition ) );
    m_infoForPartitionHash[ partition ] = partitionInfo;

    CreatePartitionJob* job = new CreatePartitionJob( device, partition );
    job->updatePreview();

    refreshPartitionModel( device );

    deviceInfo->jobs << Calamares::job_ptr( job );

    updateHasRootMountPoint();
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
    auto deviceInfo = infoForDevice( device );
    Q_ASSERT( deviceInfo );
    auto it = m_infoForPartitionHash.find( partition );
    if ( it != m_infoForPartitionHash.end() )
    {
        m_infoForPartitionHash.erase( it );
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
        DeletePartitionJob* job = new DeletePartitionJob( device, partition );
        job->updatePreview();
        jobs << Calamares::job_ptr( job );
    }

    refreshPartitionModel( device );
    updateHasRootMountPoint();
}

QList< Calamares::job_ptr >
PartitionCoreModule::jobs() const
{
    QList< Calamares::job_ptr > lst;
    for ( auto info : m_deviceInfos )
    {
        lst << info->jobs;
    }
    return lst;
}

void
PartitionCoreModule::dumpQueue() const
{
    cDebug() << "Queue:";
    for ( auto info : m_deviceInfos )
    {
        cDebug() << "Device:" << info->device->name();
        for ( auto job : info->jobs )
        {
            cDebug() << job->prettyName();
        }
    }
}

void
PartitionCoreModule::refreshPartitionModel( Device* device )
{
    auto model = partitionModelForDevice( device );
    Q_ASSERT( model );
    model->reload();
}

void PartitionCoreModule::updateHasRootMountPoint()
{
    bool oldValue = m_hasRootMountPoint;

    m_hasRootMountPoint = false;
    for ( auto it : m_infoForPartitionHash )
    {
        if ( it->mountPoint == "/" )
        {
            m_hasRootMountPoint = true;
        }
    }

    if ( oldValue != m_hasRootMountPoint )
    {
        hasRootMountPointChanged( m_hasRootMountPoint );
    }
}

PartitionCoreModule::DeviceInfo*
PartitionCoreModule::infoForDevice( Device* device ) const
{
    for ( auto deviceInfo : m_deviceInfos )
    {
        if ( deviceInfo->device.data() == device )
        {
            return deviceInfo;
        }
    }
    return nullptr;
}
