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

static
Partition* firstFreePartition( PartitionNode* parent )
{
    for( auto child : parent->children() )
        if ( PMUtils::isPartitionFreeSpace( child ) )
            return child;
    return nullptr;
}

QueueRunner::QueueRunner( JobQueue* queue )
    : m_queue( queue )
{
    connect( m_queue, &JobQueue::finished, this, &QueueRunner::onFinished );
    connect( m_queue, &JobQueue::failed, this, &QueueRunner::onFailed );
}

bool
QueueRunner::run()
{
    m_finished = false;
    m_success = true;
    m_queue->start();
    QEventLoop loop;
    while ( !m_finished )
        loop.processEvents();
    return m_success;
}

void
QueueRunner::onFinished()
{
    m_finished = true;
}

void
QueueRunner::onFailed( const QString& message, const QString& details )
{
    m_success = false;
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
    QString devicePath = qgetenv( "CALAMARES_TEST_DISK" );
    if ( devicePath.isEmpty() )
    {
        QSKIP( "Skipping test, CALAMARES_TEST_DISK is not set. It should point to a disk which can be safely formatted" );
    }

    QVERIFY( CalaPM::init() );

    CoreBackend* backend = CoreBackendManager::self()->backend();
    m_device.reset( backend->scanDevice( devicePath ) );
    QVERIFY( !m_device.isNull() );

    FileSystemFactory::init();
}

void
JobTests::testPartitionTable()
{
    queuePartitionTableCreation( PartitionTable::msdos );
    QVERIFY( m_runner.run() );
    QVERIFY( m_device->partitionTable() );
    QVERIFY( firstFreePartition( m_device->partitionTable() ) );

    queuePartitionTableCreation( PartitionTable::gpt );
    QVERIFY( m_runner.run() );
    QVERIFY( m_device->partitionTable() );
    QVERIFY( firstFreePartition( m_device->partitionTable() ) );
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

void
JobTests::testCreatePartition()
{
    queuePartitionTableCreation( PartitionTable::gpt );
    CreatePartitionJob* job;
    Partition* freePartition;

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, 1 * MB);
    Partition* partition1 = job->partition();
    QVERIFY( partition1 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::LinuxSwap, 1 * MB);
    Partition* partition2 = job->partition();
    QVERIFY( partition2 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::Fat32, 1 * MB);
    Partition* partition3 = job->partition();
    QVERIFY( partition3 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    QVERIFY( m_runner.run() );

    // Check partitionPath has been set. It is not known until the job has
    // executed.
    QString devicePath = m_device->deviceNode();
    QCOMPARE( partition1->partitionPath(), devicePath + "1" );
    QCOMPARE( partition2->partitionPath(), devicePath + "2" );
    QCOMPARE( partition3->partitionPath(), devicePath + "3" );
}

void
JobTests::testCreatePartitionExtended()
{
    queuePartitionTableCreation( PartitionTable::msdos );
    CreatePartitionJob* job;
    Partition* freePartition;

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, 10 * MB);
    Partition* partition1 = job->partition();
    QVERIFY( partition1 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Extended ), FileSystem::Extended, 10 * MB);
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );
    Partition* extendedPartition = job->partition();

    freePartition = firstFreePartition( extendedPartition );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Logical ), FileSystem::Ext4, 0);
    Partition* partition2 = job->partition();
    QVERIFY( partition2 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    QVERIFY( m_runner.run() );

    // Check partitionPath has been set. It is not known until the job has
    // executed.
    QString devicePath = m_device->deviceNode();
    QCOMPARE( partition1->partitionPath(), devicePath + "1" );
    QCOMPARE( extendedPartition->partitionPath(), devicePath + "2" );
    QCOMPARE( partition2->partitionPath(), devicePath + "5" );
}
