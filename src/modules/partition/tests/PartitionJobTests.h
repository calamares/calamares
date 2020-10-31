/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONJOBTESTS_H
#define PARTITIONJOBTESTS_H

#include "JobQueue.h"

#include "partition/KPMHelper.h"

// Qt
#include <QObject>
#include <QScopedPointer>

class QueueRunner : public QObject
{
public:
    QueueRunner( Calamares::JobQueue* queue );
    ~QueueRunner() override;

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

class PartitionJobTests : public QObject
{
    Q_OBJECT
public:
    PartitionJobTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
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
    CreatePartitionJob*
    newCreatePartitionJob( Partition* freeSpacePartition, PartitionRole, FileSystem::Type type, qint64 size );
    void refreshDevice();
};

#endif /* PARTITIONJOBTESTS_H */
