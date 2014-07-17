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
#include <PartitionInfo.h>
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

class PartitionIterator
{
public:
    Partition* operator*() const
    {
        return m_current;
    }

    void operator++()
    {
        if ( !m_current )
            return;
        if ( m_current->hasChildren() )
        {
            // Go to the first child
            m_current = static_cast< Partition* >( m_current->children().first() );
            return;
        }
        PartitionNode* parent = m_current->parent();
        Partition* successor = parent->successor( *m_current );
        if ( successor )
        {
            // Go to the next sibling
            m_current = successor;
            return;
        }
        if ( parent->isRoot() )
        {
            // We reached the end
            m_current = nullptr;
            return;
        }
        // Try to go to the next sibling of our parent

        PartitionNode* grandParent = parent->parent();
        Q_ASSERT( grandParent );
        // If parent is not root, then it's not a PartitionTable but a
        // Partition, we can static_cast it.
        m_current = grandParent->successor( *static_cast< Partition* >( parent ) );
    }

    bool operator==( const PartitionIterator& other ) const
    {
        return m_device == other.m_device && m_current == other.m_current;
    }

    bool operator!=( const PartitionIterator& other ) const
    {
        return ! ( *this == other );
    }

    static PartitionIterator begin( Device* device )
    {
        auto it = PartitionIterator( device );
        PartitionTable* table = device->partitionTable();
        if ( !table )
            return it;
        it.m_current = table->children().first();
        return it;
    }

    static PartitionIterator end( Device* device )
    {
        return PartitionIterator( device );
    }

private:
    PartitionIterator( Device* device )
        : m_device( device )
    {}

    Device* m_device;
    Partition* m_current = nullptr;
};

//- DeviceInfo ---------------------------------------------
PartitionCoreModule::DeviceInfo::DeviceInfo( Device* _device )
    : device( _device )
    , partitionModel( new PartitionModel )
{}

PartitionCoreModule::DeviceInfo::~DeviceInfo()
{
}

bool
PartitionCoreModule::DeviceInfo::hasRootMountPoint() const
{
    for ( auto it = PartitionIterator::begin( device.data() ); it != PartitionIterator::end( device.data() ); ++it )
    {
        if ( PartitionInfo::mountPoint( *it ) == "/" )
            return true;
    }
    return false;
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
        DeletePartitionJob* job = new DeletePartitionJob( device, partition );
        job->updatePreview();
        jobs << Calamares::job_ptr( job );
    }

    refresh( device );
}

void
PartitionCoreModule::formatPartition( Device* device, Partition* partition )
{
}

QList< Calamares::job_ptr >
PartitionCoreModule::jobs() const
{
    dumpQueue();

    QList< Calamares::job_ptr > lst;
    for ( auto info : m_deviceInfos )
        lst << info->jobs;
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
}

void PartitionCoreModule::updateHasRootMountPoint()
{
    bool oldValue = m_hasRootMountPoint;

    m_hasRootMountPoint = false;
    for ( auto deviceInfo : m_deviceInfos )
    {
        if ( deviceInfo->hasRootMountPoint() )
        {
            m_hasRootMountPoint = true;
            break;
        }
    }

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
