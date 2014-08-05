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

// This class is heavily based on the ResizeOperation class from KDE Partition
// Manager. Original copyright follow:

/***************************************************************************
 *   Copyright (C) 2008,2012 by Volker Lanz <vl@fidra.de>                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/

#include <ResizePartitionJob.h>

#include <MoveFileSystemJob.h>

// CalaPM
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>
#include <backend/corebackenddevice.h>
#include <backend/corebackendpartition.h>
#include <backend/corebackendpartitiontable.h>
#include <core/device.h>
#include <core/partition.h>
#include <util/report.h>

// Qt
#include <QScopedPointer>

//- Context --------------------------------------------------------------------
struct Context
{
    Context( ResizePartitionJob* job_ )
        : job( job_ )
    {}

    ResizePartitionJob* job;
    qint64 oldFirstSector;
    qint64 oldLastSector;

    QScopedPointer< CoreBackendPartitionTable > backendPartitionTable;
};

//- ResizeFileSystemJob --------------------------------------------------------
class ResizeFileSystemJob : public Calamares::Job
{
public:
    ResizeFileSystemJob( Context* context, qint64 length )
        : m_context( context )
        , m_length( length )
    {}

    QString prettyName() const override
    {
        return QString();
    }

    Calamares::JobResult exec() override
    {
        Report report( nullptr );
        Device* device = m_context->job->device();
        Partition* partition = m_context->job->partition();
        FileSystem& fs = partition->fileSystem();
        FileSystem::CommandSupportType support = m_length < fs.length() ? fs.supportShrink() : fs.supportGrow();

        switch ( support )
        {
        case FileSystem::cmdSupportBackend:
            if ( !backendResize( &report ) )
                return Calamares::JobResult::error(
                           QString(),
                           tr( "Parted failed to resize filesystem." ) + '\n' + report.toText()
                       );
            break;
        case FileSystem::cmdSupportFileSystem:
        {
            qint64 byteLength = device->logicalSectorSize() * m_length;
            bool ok = fs.resize( report, partition->partitionPath(), byteLength );
            if ( !ok )
                return Calamares::JobResult::error(
                           QString(),
                           tr( "Failed to resize filesystem." ) + '\n' + report.toText()
                       );
            break;
        }
        default:
            break;
        }

        fs.setLastSector( fs.firstSector() + m_length - 1 );
        return Calamares::JobResult::ok();
    }

private:
    Context* m_context;
    qint64 m_length;

    bool backendResize( Report* report )
    {
        Partition* partition = m_context->job->partition();
        bool ok = m_context->backendPartitionTable->resizeFileSystem( *report, *partition, m_length );
        if ( !ok )
            return false;
        m_context->backendPartitionTable->commit();
        return true;
    }
};

//- SetPartGeometryJob ---------------------------------------------------------
class SetPartGeometryJob : public Calamares::Job
{
public:
    SetPartGeometryJob( Context* context, qint64 firstSector, qint64 length )
        : m_context( context )
        , m_firstSector( firstSector )
        , m_length( length )
    {}

    QString prettyName() const override
    {
        return QString();
    }

    Calamares::JobResult exec() override
    {
        Report report( nullptr );
        Partition* partition =  m_context->job->partition();
        qint64 lastSector = m_firstSector + m_length - 1;
        bool ok = m_context->backendPartitionTable->updateGeometry( report, *partition, m_firstSector, lastSector );
        if ( !ok )
        {
            return Calamares::JobResult::error(
                       QString(),
                       tr( "Failed to change the geometry of the partition." ) + '\n' + report.toText() );
        }
        partition->setFirstSector( m_firstSector );
        partition->setLastSector( lastSector );
        m_context->backendPartitionTable->commit();
        return Calamares::JobResult::ok();
    }

private:
    Context* m_context;
    qint64 m_firstSector;
    qint64 m_length;
};

//- ResizePartitionJob ---------------------------------------------------------
ResizePartitionJob::ResizePartitionJob( Device* device, Partition* partition, qint64 firstSector, qint64 lastSector )
    : PartitionJob( partition )
    , m_device( device )
    , m_oldFirstSector( partition->firstSector() ) // Keep a copy of old sectors because they will be overwritten in updatePreview()
    , m_oldLastSector( partition->lastSector() )
    , m_newFirstSector( firstSector )
    , m_newLastSector( lastSector )
{
}

QString
ResizePartitionJob::prettyName() const
{
    /*
    return tr( "Format partition %1 (file system: %2, size: %3 MB) on %4." )
           .arg( m_partition->partitionPath() )
           .arg( m_partition->fileSystem().name() )
           .arg( m_partition->capacity() / 1024 / 1024 )
           .arg( m_device->name() );
    */
    return QString();
}

Calamares::JobResult
ResizePartitionJob::exec()
{
    qint64 oldLength = m_oldLastSector - m_oldFirstSector + 1;
    qint64 newLength = m_newLastSector - m_newFirstSector + 1;

    // Setup context
    QString partitionPath = m_partition->partitionPath();
    Context context( this );
    context.oldFirstSector = m_oldFirstSector;
    context.oldLastSector = m_oldLastSector;

    CoreBackend* backend = CoreBackendManager::self()->backend();
    QScopedPointer<CoreBackendDevice> backendDevice( backend->openDevice( m_device->deviceNode() ) );
    if ( !backendDevice.data() )
    {
        return Calamares::JobResult::error(
                   QString(),
                   tr( "Could not open device '%1'." ).arg( m_device->deviceNode() )
               );
    }
    context.backendPartitionTable.reset( backendDevice->openPartitionTable() );

    // Create jobs
    QList< Calamares::job_ptr > jobs;
    if ( m_partition->roles().has( PartitionRole::Extended ) )
        jobs << Calamares::job_ptr( new SetPartGeometryJob( &context, m_newFirstSector, newLength ) );
    else
    {
        bool shrink = newLength < oldLength;
        bool grow = newLength > oldLength;
        bool moveRight = m_newFirstSector > m_partition->firstSector();
        bool moveLeft = m_newFirstSector < m_partition->firstSector();
        if ( shrink )
        {
            jobs << Calamares::job_ptr( new ResizeFileSystemJob( &context, newLength ) );
            jobs << Calamares::job_ptr( new SetPartGeometryJob( &context, m_partition->firstSector(), newLength ) );
        }
        if ( moveRight || moveLeft )
        {
            // At this point, we need to set the partition's length to either the resized length, if it has already been
            // shrunk, or to the original length (it may or may not then later be grown, we don't care here)
            const qint64 length = shrink ? newLength : oldLength;
            jobs << Calamares::job_ptr( new SetPartGeometryJob( &context, m_newFirstSector, length ) );
            jobs << Calamares::job_ptr( new MoveFileSystemJob( m_device, m_partition, m_newFirstSector ) );
        }
        if ( grow )
        {
            jobs << Calamares::job_ptr( new SetPartGeometryJob( &context, m_newFirstSector, newLength ) );
            jobs << Calamares::job_ptr( new ResizeFileSystemJob( &context, newLength ) );
        }
    }
    return execJobList( jobs );
}

void
ResizePartitionJob::updatePreview()
{
    m_device->partitionTable()->removeUnallocated();
    m_partition->parent()->remove( m_partition );
    m_partition->setFirstSector( m_newFirstSector );
    m_partition->setLastSector( m_newLastSector );
    m_partition->parent()->insert( m_partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}

Calamares::JobResult
ResizePartitionJob::execJobList( const QList< Calamares::job_ptr >& jobs )
{
    QString errorMessage = tr( "The installer failed to resize partition %1 on disk '%2'." )
                           .arg( m_partition->partitionPath() )
                           .arg( m_device->name() );

    int nbJobs = jobs.size();
    int count = 0;
    for ( Calamares::job_ptr job : jobs )
    {
        Calamares::JobResult result = job->exec();
        if ( !result )
        {
            if ( result.message().isEmpty() )
                result.setMessage( errorMessage );
            return result;
        }
        ++count;
        progress( qreal( count ) / nbJobs );
    }
    return Calamares::JobResult::ok();
}
