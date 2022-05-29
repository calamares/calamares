/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ResizeFSJob.h"

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/PartitionIterator.h"
#include "utils/Logger.h"
#include "utils/Units.h"
#include "utils/Variant.h"

#include <QDateTime>
#include <QThread>

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/ops/resizeoperation.h>
#include <kpmcore/util/report.h>

using CalamaresUtils::Partition::PartitionIterator;

ResizeFSJob::ResizeFSJob( QObject* parent )
    : Calamares::CppJob( parent )
    , m_required( false )
{
}


ResizeFSJob::~ResizeFSJob() {}


QString
ResizeFSJob::prettyName() const
{
    return tr( "Resize Filesystem Job" );
}

ResizeFSJob::PartitionMatch
ResizeFSJob::findPartition()
{
    using DeviceList = QList< Device* >;
    DeviceList devices
        = m_kpmcore.backend()->scanDevices( /* not includeReadOnly, not includeLoopback */ ScanFlag( 0 ) );

    cDebug() << "ResizeFSJob found" << devices.count() << "devices.";
    for ( DeviceList::iterator dev_it = devices.begin(); dev_it != devices.end(); ++dev_it )
    {
        if ( !( *dev_it ) )
        {
            continue;
        }
        cDebug() << "ResizeFSJob found" << ( *dev_it )->deviceNode();
        for ( auto part_it = PartitionIterator::begin( *dev_it ); part_it != PartitionIterator::end( *dev_it );
              ++part_it )
        {
            cDebug() << Logger::SubEntry << ( *part_it )->mountPoint() << "on" << ( *part_it )->deviceNode();
            if ( ( !m_fsname.isEmpty() && ( *part_it )->mountPoint() == m_fsname )
                 || ( !m_devicename.isEmpty() && ( *part_it )->deviceNode() == m_devicename ) )
            {
                cDebug() << Logger::SubEntry << "matched configuration dev=" << m_devicename << "fs=" << m_fsname;
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
    {
        return -1;  // Missing device data
    }
    if ( !ResizeOperation::canGrow( m.second ) )
    {
        return -1;  // Operation is doomed
    }
    if ( !m_size.isValid() )
    {
        return -1;  // Must have a grow-size
    }

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
            cDebug() << Logger::SubEntry << "ignoring unallocated" << next_start << '-' << next_end;
            continue;
        }
        cDebug() << Logger::SubEntry << "comparing" << next_start << '-' << next_end;
        if ( ( next_start > last_currently ) && ( next_start < last_available ) )
        {
            cDebug() << Logger::SubEntry << "shrunk last available to" << next_start;
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
        qint64 required = m_atleast.toSectors( m.first->totalLogical(), m.first->logicalSize() );
        if ( expand < required )
        {
            cDebug() << Logger::SubEntry << "need to expand by" << required << "but only" << expand << "is available.";
            return 0;
        }
    }

    qint64 wanted = m_size.toSectors( expand, m.first->logicalSize() );
    if ( wanted < expand )
    {
        cDebug() << Logger::SubEntry << "only growing by" << wanted << "instead of full" << expand;
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

    if ( !m_kpmcore )
    {
        cWarning() << "Could not load KPMCore backend (2).";
        return Calamares::JobResult::error( tr( "KPMCore not Available" ),
                                            tr( "Calamares cannot start KPMCore for the file-system resize job." ) );
    }
    m_kpmcore.backend()->initFSSupport();  // Might not be enough, see below

    // Now get the partition and FS we want to work on
    PartitionMatch m = findPartition();
    if ( !m.first || !m.second )
        return Calamares::JobResult::error(
            tr( "Resize Failed" ),
            !m_fsname.isEmpty()
                ? tr( "The filesystem %1 could not be found in this system, and cannot be resized." ).arg( m_fsname )
                : tr( "The device %1 could not be found in this system, and cannot be resized." ).arg( m_devicename ) );

    m.second->fileSystem().init();  // Initialize support for specific FS
    if ( !ResizeOperation::canGrow( m.second ) )
    {
        cDebug() << "canGrow() returned false.";
        return Calamares::JobResult::error( tr( "Resize Failed" ),
                                            !m_fsname.isEmpty()
                                                ? tr( "The filesystem %1 cannot be resized." ).arg( m_fsname )
                                                : tr( "The device %1 cannot be resized." ).arg( m_devicename ) );
    }

    qint64 new_end = findGrownEnd( m );
    cDebug() << "Resize from" << m.second->firstSector() << '-' << m.second->lastSector() << '(' << m.second->length()
             << ')' << "to -" << new_end;

    if ( new_end < 0 )
        return Calamares::JobResult::error( tr( "Resize Failed" ),
                                            !m_fsname.isEmpty()
                                                ? tr( "The filesystem %1 cannot be resized." ).arg( m_fsname )
                                                : tr( "The device %1 cannot be resized." ).arg( m_devicename ) );
    if ( new_end == 0 )
    {
        cWarning() << "Resize operation on" << m_fsname << m_devicename << "skipped as not-useful.";
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
        {
            cDebug() << "Resize operation OK.";
        }
        else
        {
            cDebug() << "Resize failed." << op_report.output();
            return Calamares::JobResult::error( tr( "Resize Failed" ), op_report.toText() );
        }
    }

    return Calamares::JobResult::ok();
}


void
ResizeFSJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_fsname = configurationMap[ "fs" ].toString();
    m_devicename = configurationMap[ "dev" ].toString();

    if ( m_fsname.isEmpty() && m_devicename.isEmpty() )
    {
        cWarning() << "No fs or dev configured for resize.";
        return;
    }

    m_size = PartitionSize( configurationMap[ "size" ].toString() );
    m_atleast = PartitionSize( configurationMap[ "atleast" ].toString() );

    m_required = CalamaresUtils::getBool( configurationMap, "required", false );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ResizeFSJobFactory, registerPlugin< ResizeFSJob >(); )
