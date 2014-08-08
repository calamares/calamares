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

#ifndef PARTITIONJOBTESTS_H
#define PARTITIONJOBTESTS_H

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

class PartitionJobTests : public QObject
{
    Q_OBJECT
public:
    PartitionJobTests();

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

#endif /* PARTITIONJOBTESTS_H */
