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
#include <DeletePartitionJob.h>
#include <DeviceModel.h>
#include <JobQueue.h>
#include <PartitionModel.h>
#include <Typedefs.h>
#include <utils/Logger.h>

// CalaPM
#include <CalaPM.h>
#include <core/device.h>
#include <core/partition.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>


//- DeviceInfo --------------------------------------------
PartitionCoreModule::DeviceInfo::DeviceInfo( Device* dev )
    : device( dev )
    , partitionModel( new PartitionModel )
{
    partitionModel->init( dev );
}

PartitionCoreModule::DeviceInfo::~DeviceInfo()
{
    delete partitionModel;
}

//- PartitionCoreModule -----------------------------------
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
    QList< Device* > lst = backend->scanDevices();
    m_deviceModel->init( lst );
    for ( auto device : lst )
    {
        m_devices << new DeviceInfo( device );
    }

}

PartitionCoreModule::~PartitionCoreModule()
{
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
    for ( auto it : m_devices )
    {
        if ( it->device == device )
        {
            return it->partitionModel;
        }
    }
    return nullptr;
}

void
PartitionCoreModule::createPartition( CreatePartitionJob* job )
{
    DeviceInfo* info = deviceInfoForDevice( job->device() );
    Q_ASSERT( info );
    job->updatePreview();
    info->partitionModel->reload();
    m_jobs << Calamares::job_ptr( job );

    dumpQueue();
}

PartitionCoreModule::DeviceInfo*
PartitionCoreModule::deviceInfoForDevice( Device* device ) const
{
    for ( auto info : m_devices )
    {
        if ( info->device == device )
        {
            return info;
        }
    }
    return nullptr;
}

void
PartitionCoreModule::deletePartition( Device* device, Partition* partition )
{
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

    DeviceInfo* info = deviceInfoForDevice( device );
    info->partitionModel->reload();

    dumpQueue();
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
