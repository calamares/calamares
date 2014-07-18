#include <JobTests.h>

#include <CreatePartitionJob.h>
#include <CreatePartitionTableJob.h>
#include <PMUtils.h>

// CalaPM
#include <CalaPM.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>
#include <fs/filesystemfactory.h>

// Qt
#include <QEventLoop>
#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( JobTests )

static const qint64 MB = 1024 * 1024;

using namespace Calamares;

QueueRunner::QueueRunner( JobQueue* queue )
    : m_queue( queue )
{
    connect( m_queue, &JobQueue::progress, this, &QueueRunner::onProgress );
    connect( m_queue, &JobQueue::failed, this, &QueueRunner::onFailed );
}

bool
QueueRunner::run()
{
    m_done = false;
    m_success = false;
    m_queue->start();
    QEventLoop loop;
    while ( !m_done )
        loop.processEvents();
    return m_success;
}

void
QueueRunner::onProgress( int current, int total, const QString& prettyName )
{
    QVERIFY( current <= total );
    if ( current < total )
        return;
    m_success = true;
    m_done = true;
}

void
QueueRunner::onFailed( const QString& message, const QString& details )
{
    m_done = true;
    QString msg = message + "\ndetails: " + details;
    QFAIL( qPrintable( msg ) );
}

//----------------------------------------------------------
JobTests::JobTests()
    : m_runner( &m_queue )
{}

void
JobTests::initTestCase()
{
    QString deviceName = qgetenv( "CALAMARES_TEST_DISK" );
    if ( deviceName.isEmpty() )
    {
        QSKIP( "Skipping test, CALAMARES_TEST_DISK is not set. It should point to a disk which can be safely formatted" );
    }

    QVERIFY( CalaPM::init() );

    CoreBackend* backend = CoreBackendManager::self()->backend();
    m_device.reset( backend->scanDevice( deviceName ) );
    QVERIFY( !m_device.isNull() );

    FileSystemFactory::init();
}

void
JobTests::testPartitionTable()
{
    queuePartitionTableCreation( PartitionTable::gpt );
    m_runner.run();
}

void
JobTests::queuePartitionTableCreation( PartitionTable::TableType type)
{
    auto job = new CreatePartitionTableJob( m_device.data(), type );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );
}

CreatePartitionJob*
JobTests::newCreatePartitionJob( Partition* freeSpacePartition, PartitionRole role, FileSystem::Type type, qint64 size )
{
    Q_ASSERT( freeSpacePartition );

    qint64 firstSector = freeSpacePartition->firstSector();
    qint64 lastSector;

    if ( size > 0 )
        lastSector = firstSector + size / m_device->logicalSectorSize();
    else
        lastSector = freeSpacePartition->lastSector();
    FileSystem* fs = FileSystemFactory::create( type, firstSector, lastSector );

    Partition* partition = new Partition(
        freeSpacePartition->parent(),
        *m_device,
        role,
        fs, firstSector, lastSector,
        QString() /* path */,
        PartitionTable::FlagNone /* availableFlags */,
        QString() /* mountPoint */,
        false /* mounted */,
        PartitionTable::FlagNone /* activeFlags */,
        Partition::StateNew
    );
    return new CreatePartitionJob( m_device.data(), partition );
}

static
Partition* firstFreePartition( PartitionNode* parent )
{
    for( auto child : parent->children() )
        if ( PMUtils::isPartitionFreeSpace( child ) )
            return child;
    return nullptr;
}

void
JobTests::testCreatePartition()
{
    queuePartitionTableCreation( PartitionTable::gpt );
    CreatePartitionJob* job;

    Partition* partition = firstFreePartition( m_device->partitionTable() );
    job = newCreatePartitionJob( partition, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, 10 * MB);
    QVERIFY( job );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    partition = firstFreePartition( m_device->partitionTable() );
    job = newCreatePartitionJob( partition, PartitionRole( PartitionRole::Primary ), FileSystem::LinuxSwap, 10 * MB);
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    partition = firstFreePartition( m_device->partitionTable() );
    job = newCreatePartitionJob( partition, PartitionRole( PartitionRole::Primary ), FileSystem::Btrfs, 10 * MB);
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    QVERIFY( m_runner.run() );
}

void
JobTests::testCreatePartitionExtended()
{
    queuePartitionTableCreation( PartitionTable::msdos );
    CreatePartitionJob* job;

    Partition* partition = firstFreePartition( m_device->partitionTable() );
    job = newCreatePartitionJob( partition, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, 10 * MB);
    QVERIFY( job );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    partition = firstFreePartition( m_device->partitionTable() );
    job = newCreatePartitionJob( partition, PartitionRole( PartitionRole::Extended ), FileSystem::Unformatted, 10 * MB);
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );
    Partition* extendedPartition = job->partition();

    partition = firstFreePartition( extendedPartition );
    job = newCreatePartitionJob( partition, PartitionRole( PartitionRole::Logical ), FileSystem::Ext4, 0);
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    QVERIFY( m_runner.run() );
}
