#include <JobTests.h>

#include <CreatePartitionJob.h>
#include <CreatePartitionTableJob.h>
#include <ResizePartitionJob.h>
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
    FileSystemFactory::init();

    refreshDevice();
}

void
JobTests::refreshDevice()
{
    QString devicePath = qgetenv( "CALAMARES_TEST_DISK" );
    CoreBackend* backend = CoreBackendManager::self()->backend();
    m_device.reset( backend->scanDevice( devicePath ) );
    QVERIFY( !m_device.isNull() );
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

void
JobTests::testResizePartition_data()
{
    QTest::addColumn< int >( "oldStartMB" );
    QTest::addColumn< int >( "oldSizeMB" );
    QTest::addColumn< int >( "newStartMB" );
    QTest::addColumn< int >( "newSizeMB" );

    QTest::newRow("grow")      << 10 << 5 << 10 << 7;
    QTest::newRow("shrink")    << 10 << 6 << 10 << 3;
    QTest::newRow("moveLeft")  << 10 << 5 << 8 << 5;
    QTest::newRow("moveRight") << 10 << 5 << 12 << 5;
}

void
JobTests::testResizePartition()
{
    QFETCH( int, oldStartMB );
    QFETCH( int, oldSizeMB );
    QFETCH( int, newStartMB );
    QFETCH( int, newSizeMB );

    const qint64 sectorSize = m_device->logicalSectorSize();
    const qint64 sectorForMB = MB / sectorSize;

    qint64 oldFirst = sectorForMB * oldStartMB;
    qint64 oldLast  = oldFirst + sectorForMB * oldSizeMB - 1;
    qint64 newFirst = sectorForMB * newStartMB;
    qint64 newLast  = newFirst + sectorForMB * newSizeMB - 1;

    // Setup: create the test partition
    {
        queuePartitionTableCreation( PartitionTable::msdos );

        Partition* freePartition = firstFreePartition( m_device->partitionTable() );
        QVERIFY( freePartition );
        Partition* partition = PMUtils::createNewPartition( freePartition->parent(), *m_device, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, oldFirst, oldLast );
        CreatePartitionJob* job = new CreatePartitionJob( m_device.data(), partition );
        job->updatePreview();
        m_queue.enqueue( job_ptr( job ) );

        QVERIFY( m_runner.run() );
    }

    // Resize
    {
        refreshDevice();
        QVERIFY( m_device->partitionTable() );
        Partition* partition = m_device->partitionTable()->findPartitionBySector( oldFirst, PartitionRole( PartitionRole::Primary ) );
        QVERIFY( partition );

        ResizePartitionJob* job = new ResizePartitionJob( m_device.data(), partition, newFirst, newLast );
        job->updatePreview();
        m_queue.enqueue( job_ptr( job ) );
        QVERIFY( m_runner.run() );
    }

    // Test
    {
        refreshDevice();
        QVERIFY( m_device->partitionTable() );
        Partition* partition = m_device->partitionTable()->findPartitionBySector( newFirst, PartitionRole( PartitionRole::Primary ) );
        QVERIFY( partition );
        QCOMPARE( partition->firstSector(), newFirst );
        QCOMPARE( partition->lastSector(), newLast );
        QCOMPARE( partition->fileSystem().firstSector(), newFirst );
        QCOMPARE( partition->fileSystem().lastSector(), newLast );
    }
}
