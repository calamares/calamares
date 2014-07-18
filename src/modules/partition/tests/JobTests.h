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
    void onProgress( int current, int total, const QString& prettyName );
    void onFailed( const QString& message, const QString& details );
    Calamares::JobQueue* m_queue;
    bool m_done;
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

private:
    QScopedPointer< Device > m_device;
    Calamares::JobQueue m_queue;
    QueueRunner m_runner;

    void queuePartitionTableCreation( PartitionTable::TableType type );
    CreatePartitionJob* newCreatePartitionJob( Partition* freeSpacePartition, PartitionRole, FileSystem::Type type, qint64 size );
};

#endif /* JOBTESTS_H */
