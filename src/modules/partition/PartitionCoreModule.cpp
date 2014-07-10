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
    m_devices = backend->scanDevices();
    for ( auto device : m_devices )
    {
        PartitionModel* model = new PartitionModel;
        model->init( device, &m_infoForPartitionHash );
        m_partitionModelForDeviceHash[ device ] = model;
    }
    m_deviceModel->init( m_devices );

}

PartitionCoreModule::~PartitionCoreModule()
{
    qDeleteAll( m_infoForPartitionHash );
    qDeleteAll( m_devices );
}

DeviceModel*
PartitionCoreModule::deviceModel() const
{
    return m_deviceModel;
}

PartitionModel*
PartitionCoreModule::partitionModelForDevice( Device* device ) const
{
    return m_partitionModelForDeviceHash[ device ];
}

void
PartitionCoreModule::createPartitionTable( Device* device )
{
    CreatePartitionTableJob* job = new CreatePartitionTableJob( device );
    job->updatePreview();
    refreshPartitionModel( device );

    // FIXME: Remove all jobs queued for this device, as well as all partition
    // info
    m_jobs << Calamares::job_ptr( job );
    updateHasRootMountPoint();
}

void
PartitionCoreModule::createPartition( Device* device, PartitionInfo* partitionInfo )
{
    auto partition = partitionInfo->partition;
    Q_ASSERT( !m_infoForPartitionHash.contains( partition ) );
    m_infoForPartitionHash[ partition ] = partitionInfo;

    CreatePartitionJob* job = new CreatePartitionJob( device, partition );
    job->updatePreview();

    refreshPartitionModel( device );

    m_jobs << Calamares::job_ptr( job );

    updateHasRootMountPoint();
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
    auto it = m_infoForPartitionHash.find( partition );
    if ( it != m_infoForPartitionHash.end() )
    {
        m_infoForPartitionHash.erase( it );
    }

    if ( partition->state() == Partition::StateNew )
    {
        // Find matching CreatePartitionJob
        auto it = std::find_if( m_jobs.begin(), m_jobs.end(), [ partition ]( Calamares::job_ptr job )
        {
            CreatePartitionJob* createJob = qobject_cast< CreatePartitionJob* >( job.data() );
            return createJob && createJob->partition() == partition;
        } );
        if ( it == m_jobs.end() )
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
        m_jobs.erase( it );
        // The partition is no longer referenced by either a job or the device
        // partition list, so we have to delete it
        delete partition;
    }
    else
    {
        DeletePartitionJob* job = new DeletePartitionJob( device, partition );
        job->updatePreview();
        m_jobs << Calamares::job_ptr( job );
    }

    refreshPartitionModel( device );
    updateHasRootMountPoint();
}

void
PartitionCoreModule::dumpQueue() const
{
    cDebug() << "Queue:";
    for ( auto job : m_jobs )
    {
        cDebug() << job->prettyName();
    }
}

void
PartitionCoreModule::refreshPartitionModel( Device* device )
{
    auto model = m_partitionModelForDeviceHash.value( device );
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
