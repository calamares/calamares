/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <PartitionJobTests.h>

#include "utils/Units.h"

#include <jobs/CreatePartitionJob.h>
#include <jobs/CreatePartitionTableJob.h>
#include <jobs/ResizePartitionJob.h>
#include <core/KPMHelpers.h>

// CalaPM
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>
#include <fs/filesystemfactory.h>

// Qt
#include <QEventLoop>
#include <QProcess>
#include <QtTest/QtTest>

QTEST_GUILESS_MAIN( PartitionJobTests )

using namespace Calamares;
using CalamaresUtils::operator""_MiB;

class PartitionMounter
{
public:
    PartitionMounter( const QString& devicePath )
        : m_mountPointDir( "calamares-partitiontests-mountpoint" )
    {
        QStringList args = QStringList() << devicePath << m_mountPointDir.path();
        int ret = QProcess::execute( "mount", args );
        m_mounted = ret == 0;
        QCOMPARE( ret, 0 );
    }

    ~PartitionMounter()
    {
        if ( !m_mounted )
            return;
        int ret = QProcess::execute( "umount", QStringList() << m_mountPointDir.path() );
        QCOMPARE( ret, 0 );
    }

    QString mountPoint() const
    {
        return m_mounted ? m_mountPointDir.path() : QString();
    }

private:
    QString m_devicePath;
    QTemporaryDir m_mountPointDir;
    bool m_mounted;
};

static QByteArray
generateTestData( qint64 size )
{
    QByteArray ba;
    ba.resize( size );
    // Fill the array explicitly to keep Valgrind happy
    for ( auto it = ba.data() ; it < ba.data() + size ; ++it )
    {
        *it = char( rand() & 0xff );
    }
    return ba;
}

static void
writeFile( const QString& path, const QByteArray data )
{
    QFile file( path );
    QVERIFY( file.open( QIODevice::WriteOnly ) );

    const char* ptr = data.constData();
    const char* end = data.constData() + data.size();
    const qint64 chunkSize = 16384;

    while ( ptr < end )
    {
        qint64 count = file.write( ptr, chunkSize );
        if ( count < 0 )
        {
            QString msg = QString( "Writing file failed. Only %1 bytes written out of %2. Error: '%3'." )
                .arg( ptr - data.constData() )
                .arg( data.size() )
                .arg( file.errorString() );
            QFAIL( qPrintable( msg ) );
        }
        ptr += count;
    }
}

static Partition*
firstFreePartition( PartitionNode* parent )
{
    for( auto child : parent->children() )
        if ( KPMHelpers::isPartitionFreeSpace( child ) )
            return child;
    return nullptr;
}

//- QueueRunner ---------------------------------------------------------------
QueueRunner::QueueRunner( JobQueue* queue )
    : m_queue( queue )
    , m_finished( false )  // Same initalizations as in ::run()
    , m_success( true )
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

//- PartitionJobTests ------------------------------------------------------------------
PartitionJobTests::PartitionJobTests()
    : m_runner( &m_queue )
{}

void
PartitionJobTests::initTestCase()
{
    QString devicePath = qgetenv( "CALAMARES_TEST_DISK" );
    if ( devicePath.isEmpty() )
    {
        QSKIP( "Skipping test, CALAMARES_TEST_DISK is not set. It should point to a disk which can be safely formatted" );
    }

    QVERIFY( KPMHelpers::initKPMcore() );
    FileSystemFactory::init();

    refreshDevice();
}

void
PartitionJobTests::refreshDevice()
{
    QString devicePath = qgetenv( "CALAMARES_TEST_DISK" );
    CoreBackend* backend = CoreBackendManager::self()->backend();
    m_device.reset( backend->scanDevice( devicePath ) );
    QVERIFY( !m_device.isNull() );
}

void
PartitionJobTests::testPartitionTable()
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
PartitionJobTests::queuePartitionTableCreation( PartitionTable::TableType type)
{
    auto job = new CreatePartitionTableJob( m_device.data(), type );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );
}

CreatePartitionJob*
PartitionJobTests::newCreatePartitionJob( Partition* freeSpacePartition, PartitionRole role, FileSystem::Type type, qint64 size )
{
    Q_ASSERT( freeSpacePartition );

    qint64 firstSector = freeSpacePartition->firstSector();
    qint64 lastSector;

    if ( size > 0 )
        lastSector = firstSector + size / m_device->logicalSize();
    else
        lastSector = freeSpacePartition->lastSector();
    FileSystem* fs = FileSystemFactory::create( type, firstSector, lastSector
#ifdef WITH_KPMCORE22
        ,m_device->logicalSize()
#endif
    );

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
PartitionJobTests::testCreatePartition()
{
    queuePartitionTableCreation( PartitionTable::gpt );
    CreatePartitionJob* job;
    Partition* freePartition;

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, 1_MiB);
    Partition* partition1 = job->partition();
    QVERIFY( partition1 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::LinuxSwap, 1_MiB);
    Partition* partition2 = job->partition();
    QVERIFY( partition2 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::Fat32, 1_MiB);
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
PartitionJobTests::testCreatePartitionExtended()
{
    queuePartitionTableCreation( PartitionTable::msdos );
    CreatePartitionJob* job;
    Partition* freePartition;

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, 10_MiB);
    Partition* partition1 = job->partition();
    QVERIFY( partition1 );
    job->updatePreview();
    m_queue.enqueue( job_ptr( job ) );

    freePartition = firstFreePartition( m_device->partitionTable() );
    QVERIFY( freePartition );
    job = newCreatePartitionJob( freePartition, PartitionRole( PartitionRole::Extended ), FileSystem::Extended, 10_MiB);
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
PartitionJobTests::testResizePartition_data()
{
    QTest::addColumn< int >( "oldStartMB" );
    QTest::addColumn< int >( "oldSizeMB" );
    QTest::addColumn< int >( "newStartMB" );
    QTest::addColumn< int >( "newSizeMB" );

    QTest::newRow("grow")      << 10 << 50 << 10 << 70;
    QTest::newRow("shrink")    << 10 << 70 << 10 << 50;
    QTest::newRow("moveLeft")  << 10 << 50 << 8 << 50;
    QTest::newRow("moveRight") << 10 << 50 << 12 << 50;
}

void
PartitionJobTests::testResizePartition()
{
    QFETCH( int, oldStartMB );
    QFETCH( int, oldSizeMB );
    QFETCH( int, newStartMB );
    QFETCH( int, newSizeMB );

    const qint64 sectorForMB = 1_MiB / m_device->logicalSize();

    qint64 oldFirst = sectorForMB * oldStartMB;
    qint64 oldLast  = oldFirst + sectorForMB * oldSizeMB - 1;
    qint64 newFirst = sectorForMB * newStartMB;
    qint64 newLast  = newFirst + sectorForMB * newSizeMB - 1;

    // Make the test data file smaller than the full size of the partition to
    // accomodate for the file system overhead
    const QByteArray testData = generateTestData( CalamaresUtils::MiBtoBytes( qMin( oldSizeMB, newSizeMB ) ) * 3 / 4 );
    const QString testName = "test.data";

    // Setup: create the test partition
    {
        queuePartitionTableCreation( PartitionTable::msdos );

        Partition* freePartition = firstFreePartition( m_device->partitionTable() );
        QVERIFY( freePartition );
        Partition* partition = KPMHelpers::createNewPartition( freePartition->parent(), *m_device, PartitionRole( PartitionRole::Primary ), FileSystem::Ext4, oldFirst, oldLast );
        CreatePartitionJob* job = new CreatePartitionJob( m_device.data(), partition );
        job->updatePreview();
        m_queue.enqueue( job_ptr( job ) );

        QVERIFY( m_runner.run() );
    }

    {
        // Write a test file in the partition
        refreshDevice();
        QVERIFY( m_device->partitionTable() );
        Partition* partition = m_device->partitionTable()->findPartitionBySector( oldFirst, PartitionRole( PartitionRole::Primary ) );
        QVERIFY( partition );
        QCOMPARE( partition->firstSector(), oldFirst );
        QCOMPARE( partition->lastSector(), oldLast );
        {
            PartitionMounter mounter( partition->partitionPath() );
            QString mountPoint = mounter.mountPoint();
            QVERIFY( !mountPoint.isEmpty() );
            writeFile( mountPoint + '/' + testName, testData );
        }

        // Resize
        ResizePartitionJob* job = new ResizePartitionJob( m_device.data(), partition, newFirst, newLast );
        job->updatePreview();
        m_queue.enqueue( job_ptr( job ) );
        QVERIFY( m_runner.run() );

        QCOMPARE( partition->firstSector(), newFirst );
        QCOMPARE( partition->lastSector(), newLast );
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


        PartitionMounter mounter( partition->partitionPath() );
        QString mountPoint = mounter.mountPoint();
        QVERIFY( !mountPoint.isEmpty() );
        {
            QFile file( mountPoint + '/' + testName );
            QVERIFY( file.open( QIODevice::ReadOnly ) );
            QByteArray outData = file.readAll();
            QCOMPARE( outData.size(), testData.size() );
            QCOMPARE( outData, testData );
        }
    }
}
