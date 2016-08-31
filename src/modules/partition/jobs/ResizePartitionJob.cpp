/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#include "jobs/ResizePartitionJob.h"

#include "jobs/CheckFileSystemJob.h"
#include "jobs/MoveFileSystemJob.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/backend/corebackenddevice.h>
#include <kpmcore/backend/corebackendpartition.h>
#include <kpmcore/backend/corebackendpartitiontable.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/util/report.h>

// Qt
#include <QScopedPointer>

//- ResizeFileSystemJob --------------------------------------------------------
class ResizeFileSystemJob : public Calamares::Job
{
    Q_OBJECT
public:
    ResizeFileSystemJob( Device* device, CoreBackendPartitionTable* backendPartitionTable, Partition* partition, qint64 length )
        : m_device( device )
        , m_backendPartitionTable( backendPartitionTable )
        , m_partition( partition )
        , m_length( length )
    {}

    QString prettyName() const override
    {
        QString path = m_partition->partitionPath();
        return tr( "Resize file system on partition %1." ).arg( path );
    }

    Calamares::JobResult exec() override
    {
        Report report( nullptr );
        FileSystem& fs = m_partition->fileSystem();
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
            qint64 byteLength = m_device->logicalSize() * m_length;
            bool ok = fs.resize( report, m_partition->partitionPath(), byteLength );
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
    Device* m_device;
    CoreBackendPartitionTable* m_backendPartitionTable;
    Partition* m_partition;
    qint64 m_length;

    bool backendResize( Report* report )
    {
        bool ok = m_backendPartitionTable->resizeFileSystem( *report, *m_partition, m_length );
        if ( !ok )
            return false;
        m_backendPartitionTable->commit();
        return true;
    }
};

//- SetPartGeometryJob ---------------------------------------------------------
class SetPartGeometryJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetPartGeometryJob( CoreBackendPartitionTable* backendPartitionTable, Partition* partition, qint64 firstSector, qint64 length )
        : m_backendPartitionTable( backendPartitionTable )
        , m_partition( partition )
        , m_firstSector( firstSector )
        , m_length( length )
    {}

    QString prettyName() const override
    {
        QString path = m_partition->partitionPath();
        return tr( "Update geometry of partition %1." ).arg( path );
    }

    Calamares::JobResult exec() override
    {
        Report report( nullptr );
        qint64 lastSector = m_firstSector + m_length - 1;
        bool ok = m_backendPartitionTable->updateGeometry( report, *m_partition, m_firstSector, lastSector );
        if ( !ok )
        {
            return Calamares::JobResult::error(
                       QString(),
                       tr( "Failed to change the geometry of the partition." ) + '\n' + report.toText() );
        }
        m_partition->setFirstSector( m_firstSector );
        m_partition->setLastSector( lastSector );
        m_backendPartitionTable->commit();
        return Calamares::JobResult::ok();
    }

private:
    CoreBackendPartitionTable* m_backendPartitionTable;
    Partition* m_partition;
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
    // FIXME: Copy PM ResizeOperation code which generates a description of the
    // operation
    return tr( "Resize partition %1." ).arg( partition()->partitionPath() );
}


QString
ResizePartitionJob::prettyDescription() const
{
    return tr( "Resize <strong>%2MB</strong> partition <strong>%1</strong> to "
               "<strong>%3MB</strong>." )
            .arg( partition()->partitionPath() )
            .arg( ( m_oldLastSector - m_oldFirstSector ) * partition()->sectorSize() / 1024 / 1024 )
            .arg( ( m_newLastSector - m_newFirstSector + 1 ) * partition()->sectorSize() / 1024 / 1024 );
}


QString
ResizePartitionJob::prettyStatusMessage() const
{
    return tr( "Resizing %2MB partition %1 to "
               "%3MB." )
            .arg( partition()->partitionPath() )
            .arg( ( m_oldLastSector - m_oldFirstSector ) * partition()->sectorSize() / 1024 / 1024 )
            .arg( ( m_newLastSector - m_newFirstSector + 1 ) * partition()->sectorSize() / 1024 / 1024 );
}


Calamares::JobResult
ResizePartitionJob::exec()
{
    qint64 oldLength = m_oldLastSector - m_oldFirstSector + 1;
    qint64 newLength = m_newLastSector - m_newFirstSector + 1;

    // Assuming updatePreview() has been called, `partition` uses its new
    // position and size. Reset it to the old values: part of the libparted
    // backend relies on this (for example:
    // LibPartedPartitionTable::updateGeometry())
    // The jobs are responsible for updating the partition back when they are
    // done.
    m_partition->setFirstSector( m_oldFirstSector );
    m_partition->setLastSector( m_oldLastSector );

    CoreBackend* backend = CoreBackendManager::self()->backend();
    QScopedPointer<CoreBackendDevice> backendDevice( backend->openDevice( m_device->deviceNode() ) );
    if ( !backendDevice.data() )
    {
        QString errorMessage = tr( "The installer failed to resize partition %1 on disk '%2'." )
                               .arg( m_partition->partitionPath() )
                               .arg( m_device->name() );
        return Calamares::JobResult::error(
                   errorMessage,
                   tr( "Could not open device '%1'." ).arg( m_device->deviceNode() )
               );
    }
    QScopedPointer<CoreBackendPartitionTable> backendPartitionTable( backendDevice->openPartitionTable() );

    // Create jobs
    QList< Calamares::job_ptr > jobs;
    jobs << Calamares::job_ptr( new CheckFileSystemJob( partition() ) );
    if ( m_partition->roles().has( PartitionRole::Extended ) )
        jobs << Calamares::job_ptr( new SetPartGeometryJob( backendPartitionTable.data(), m_partition, m_newFirstSector, newLength ) );
    else
    {
        bool shrink = newLength < oldLength;
        bool grow = newLength > oldLength;
        bool moveRight = m_newFirstSector > m_oldFirstSector;
        bool moveLeft = m_newFirstSector < m_oldFirstSector;
        if ( shrink )
        {
            jobs << Calamares::job_ptr( new ResizeFileSystemJob( m_device, backendPartitionTable.data(), m_partition, newLength ) );
            jobs << Calamares::job_ptr( new SetPartGeometryJob( backendPartitionTable.data(), m_partition, m_oldFirstSector, newLength ) );
        }
        if ( moveRight || moveLeft )
        {
            // At this point, we need to set the partition's length to either the resized length, if it has already been
            // shrunk, or to the original length (it may or may not then later be grown, we don't care here)
            const qint64 length = shrink ? newLength : oldLength;
            jobs << Calamares::job_ptr( new SetPartGeometryJob( backendPartitionTable.data(), m_partition, m_newFirstSector, length ) );
            jobs << Calamares::job_ptr( new MoveFileSystemJob( m_device, m_partition, m_oldFirstSector, m_newFirstSector, length ) );
        }
        if ( grow )
        {
            jobs << Calamares::job_ptr( new SetPartGeometryJob( backendPartitionTable.data(), m_partition, m_newFirstSector, newLength ) );
            jobs << Calamares::job_ptr( new ResizeFileSystemJob( m_device, backendPartitionTable.data(), m_partition, newLength ) );
        }
    }
    jobs << Calamares::job_ptr( new CheckFileSystemJob( partition() ) );
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


Device*
ResizePartitionJob::device() const
{
    return m_device;
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
        cLog() << "- " + job->prettyName();
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

#include "ResizePartitionJob.moc"
