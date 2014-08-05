#ifndef JOBTESTS_H
#define JOBTESTS_H

#include <JobQueue.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitionrole.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>

// Qt
#include <QObject>
#include <QScopedPointer>

class QueueRunner : public QObject
{
public:
    QueueRunner( Calamares::JobQueue* queue );

    /**
     * Synchronously runs the queue. Returns true on success
     */
    bool run();

private:
    void onFailed( const QString& message, const QString& details );
    void onFinished();
    Calamares::JobQueue* m_queue;
    bool m_finished;
    bool m_success;
};

class JobTests : public QObject
{
    Q_OBJECT
public:
    JobTests();

private Q_SLOTS:
    void initTestCase();
    void testPartitionTable();
    void testCreatePartition();
    void testCreatePartitionExtended();
    void testResizePartition_data();
    void testResizePartition();

private:
    QScopedPointer< Device > m_device;
    Calamares::JobQueue m_queue;
    QueueRunner m_runner;

    void queuePartitionTableCreation( PartitionTable::TableType type );
    CreatePartitionJob* newCreatePartitionJob( Partition* freeSpacePartition, PartitionRole, FileSystem::Type type, qint64 size );
    void refreshDevice();
};

#endif /* JOBTESTS_H */
