/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "ResizeFSJob.h"

#include <QProcess>
#include <QDateTime>
#include <QThread>

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/ops/resizeoperation.h>
#include <kpmcore/util/report.h>

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include "modules/partition/core/PartitionIterator.h"

ResizeFSJob::RelativeSize::RelativeSize()
    : m_value( 0 )
    , m_unit( None )
{
}


template<int N>
void matchUnitSuffix(
    const QString& s,
    const char ( &suffix )[N],
    ResizeFSJob::RelativeSize::Unit matchedUnit,
    int& value,
    ResizeFSJob::RelativeSize::Unit& unit
)
{
    if ( s.endsWith( suffix ) )
    {
        value = s.left( s.length() - N + 1 ).toInt();
        unit = matchedUnit;
    }
}


ResizeFSJob::RelativeSize::RelativeSize( const QString& s )
    : m_value( 0 )
    , m_unit( None )
{
    matchUnitSuffix( s, "%", Percent, m_value, m_unit );
    matchUnitSuffix( s, "MiB", Absolute, m_value, m_unit );

    if ( ( unit() == Percent ) && ( value() > 100 ) )
    {
        cDebug() << "Percent value" << value() << "is not valid.";
        m_value = 0;
        m_unit = None;
    }

    if ( !m_value )
        m_unit = None;
}

qint64
ResizeFSJob::RelativeSize::apply( qint64 totalSectors, qint64 sectorSize )
{
    if ( !isValid() )
        return -1;
    if ( sectorSize < 1 )
        return -1;

    switch ( m_unit )
    {
    case None:
        return -1;
    case Absolute:
        return CalamaresUtils::MiBtoBytes( value() ) / sectorSize;
    case Percent:
        if ( value() == 100 )
            return totalSectors;  // Common-case, avoid futzing around
        else
            return totalSectors * value() / 100;
    }

    // notreached
    return -1;
}

qint64
ResizeFSJob::RelativeSize::apply( Device* d )
{
    return apply( d->totalLogical(), d->logicalSize() );
}

ResizeFSJob::ResizeFSJob( QObject* parent )
    : Calamares::CppJob( parent )
    , m_required( false )
{
}


ResizeFSJob::~ResizeFSJob()
{
}


QString
ResizeFSJob::prettyName() const
{
    return tr( "Resize Filesystem Job" );
}

ResizeFSJob::PartitionMatch
ResizeFSJob::findPartition( CoreBackend* backend )
{
    using DeviceList = QList< Device* >;
    DeviceList devices = backend->scanDevices( false );
    cDebug() << "ResizeFSJob found" << devices.count() << "devices.";
    for ( DeviceList::iterator dev_it = devices.begin(); dev_it != devices.end(); ++dev_it )
    {
        if ( ! ( *dev_it ) )
            continue;
        cDebug() << "ResizeFSJob found" << ( *dev_it )->deviceNode();
        for ( auto part_it = PartitionIterator::begin( *dev_it ); part_it != PartitionIterator::end( *dev_it ); ++part_it )
        {
            cDebug() << ".." << ( *part_it )->mountPoint() << "on" << ( *part_it )->deviceNode();
            if ( ( !m_fsname.isEmpty() && ( *part_it )->mountPoint() == m_fsname ) ||
                    ( !m_devicename.isEmpty() && ( *part_it )->deviceNode() == m_devicename ) )
            {
                cDebug() << ".. matched configuration dev=" << m_devicename << "fs=" << m_fsname;
                return PartitionMatch( *dev_it, *part_it );
            }
        }
    }

    cDebug() << "No match for configuration dev=" << m_devicename << "fs=" << m_fsname;
    return PartitionMatch( nullptr, nullptr );
}

/** @brief Returns the last sector the matched partition should occupy.
 *
 * Returns a sector number. Returns -1 if something is wrong (e.g.
 * can't resize at all, or missing data). Returns 0 if the resize
 * won't fit because it doesn't satisfy the settings for atleast
 * and size (or won't grow at all because the partition is blocked
 * by occupied space after it).
 */
qint64
ResizeFSJob::findGrownEnd( ResizeFSJob::PartitionMatch m )
{
    if ( !m.first || !m.second )
        return -1;  // Missing device data
    if ( !ResizeOperation::canGrow( m.second ) )
        return -1;  // Operation is doomed
    if ( !m_size.isValid() )
        return -1;  // Must have a grow-size

    cDebug() << "Containing device size" << m.first->totalLogical();
    qint64 last_available = m.first->totalLogical() - 1;  // Numbered from 0
    qint64 last_currently = m.second->lastSector();
    cDebug() << "Growing partition" << m.second->firstSector() << '-' << last_currently;

    for ( auto part_it = PartitionIterator::begin( m.first ); part_it != PartitionIterator::end( m.first ); ++part_it )
    {
        qint64 next_start = ( *part_it )->firstSector();
        qint64 next_end = ( *part_it )->lastSector();
        if ( next_start > next_end )
        {
            cWarning() << "Corrupt partition has end" << next_end << " < start" << next_start;
            std::swap( next_start, next_end );
        }
        if ( ( *part_it )->roles().has( PartitionRole::Unallocated ) )
        {
            cDebug() << ".. ignoring unallocated" << next_start << '-' << next_end;
            continue;
        }
        cDebug() << ".. comparing" << next_start << '-' << next_end;
        if ( ( next_start > last_currently ) && ( next_start < last_available ) )
        {
            cDebug() << "  .. shrunk last available to" << next_start;
            last_available = next_start - 1;  // Before that one starts
        }
    }

    if ( !( last_available > last_currently ) )
    {
        cDebug() << "Partition cannot grow larger.";
        return 0;
    }

    qint64 expand = last_available - last_currently;  // number of sectors
    if ( m_atleast.isValid() )
    {
        qint64 required = m_atleast.apply( m.first );
        if ( expand < required )
        {
            cDebug() << ".. need to expand by" << required << "but only" << expand << "is available.";
            return 0;
        }
    }

    qint64 wanted = m_size.apply( expand, m.first->logicalSize() );
    if ( wanted < expand )
    {
        cDebug() << ".. only growing by" << wanted << "instead of full" << expand;
        last_available -= ( expand - wanted );
    }

    return last_available;
}


Calamares::JobResult
ResizeFSJob::exec()
{
    if ( !isValid() )
        return Calamares::JobResult::error(
            tr( "Invalid configuration" ),
            tr( "The file-system resize job has an invalid configuration and will not run." ) );

    // Get KPMCore
    auto backend_p = CoreBackendManager::self()->backend();
    if ( backend_p )
        cDebug() << "KPMCore backend @" << ( void* )backend_p << backend_p->id() << backend_p->version();
    else
    {
        cDebug() << "No KPMCore backend loaded yet";
        QByteArray backendName = qgetenv( "KPMCORE_BACKEND" );
        if ( !CoreBackendManager::self()->load( backendName.isEmpty() ? CoreBackendManager::defaultBackendName() : backendName ) )
        {
            cWarning() << "Could not load KPMCore backend.";
            return Calamares::JobResult::error(
                tr( "KPMCore not Available" ),
                tr( "Calamares cannot start KPMCore for the file-system resize job." ) );
        }

        backend_p = CoreBackendManager::self()->backend();
    }
    if ( !backend_p )
    {
        cWarning() << "Could not load KPMCore backend (2).";
        return Calamares::JobResult::error(
            tr( "KPMCore not Available" ),
            tr( "Calamares cannot start KPMCore for the file-system resize job." ) );
    }
    backend_p->initFSSupport();  // Might not be enough, see below

    // Now get the partition and FS we want to work on
    PartitionMatch m = findPartition( backend_p );
    if ( !m.first || !m.second )
        return Calamares::JobResult::error(
            tr( "Resize Failed" ),
            !m_fsname.isEmpty() ? tr( "The filesystem %1 could not be found in this system, and cannot be resized." ).arg( m_fsname )
                                : tr( "The device %1 could not be found in this system, and cannot be resized." ).arg( m_devicename ) );

    m.second->fileSystem().init();  // Initialize support for specific FS
    if ( !ResizeOperation::canGrow( m.second ) )
    {
        cDebug() << "canGrow() returned false.";
        return Calamares::JobResult::error(
            tr( "Resize Failed" ),
            !m_fsname.isEmpty() ? tr( "The filesystem %1 cannot be resized." ).arg( m_fsname )
                                : tr( "The device %1 cannot be resized." ).arg( m_devicename ) );
    }

    qint64 new_end = findGrownEnd( m );
    cDebug() << "Resize from"
             << m.second->firstSector() << '-' << m.second->lastSector()
             << '(' << m.second->length() << ')'
             << "to -" << new_end;

    if ( new_end < 0 )
        return Calamares::JobResult::error(
            tr( "Resize Failed" ),
            !m_fsname.isEmpty() ? tr( "The filesystem %1 cannot be resized." ).arg( m_fsname )
                                : tr( "The device %1 cannot be resized." ).arg( m_devicename ) );
    if ( new_end == 0 )
    {
        cWarning() << "Resize operation on" << m_fsname << m_devicename
                   << "skipped as not-useful.";
        if ( m_required )
            return Calamares::JobResult::error(
                tr( "Resize Failed" ),
                !m_fsname.isEmpty() ? tr( "The filesystem %1 must be resized, but cannot." ).arg( m_fsname )
                                    : tr( "The device %1 must be resized, but cannot" ).arg( m_fsname ) );

        return Calamares::JobResult::ok();
    }

    if ( ( new_end > 0 ) && ( new_end > m.second->lastSector() ) )
    {
        ResizeOperation op( *m.first, *m.second, m.second->firstSector(), new_end );
        Report op_report( nullptr );
        if ( op.execute( op_report ) )
            cDebug() << "Resize operation OK.";
        else
        {
            cDebug() << "Resize failed." << op_report.output();
            return Calamares::JobResult::error(
                       tr( "Resize Failed" ),
                       op_report.toText() );
        }
    }

    return Calamares::JobResult::ok();
}


void
ResizeFSJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_fsname = configurationMap["fs"].toString();
    m_devicename = configurationMap["dev"].toString();

    if ( m_fsname.isEmpty() && m_devicename.isEmpty() )
    {
        cWarning() << "No fs or dev configured for resize.";
        return;
    }

    m_size = RelativeSize( configurationMap["size"].toString() );
    m_atleast = RelativeSize( configurationMap["atleast"].toString() );

    m_required = CalamaresUtils::getBool( configurationMap, "required", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ResizeFSJobFactory, registerPlugin<ResizeFSJob>(); )
