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

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

#include "modules/partition/core/PartitionIterator.h"

ResizeFSJob::RelativeSize::RelativeSize()
    : m_value( 0 )
    , m_unit( None )
{
}


template<int N>
void matchUnitSuffix(
    const QString& s,
    const char (&suffix)[N],
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


ResizeFSJob::RelativeSize::RelativeSize( const QString& s)
    : m_value( 0 )
    , m_unit( None )
{
    matchUnitSuffix( s, "%", Percent, m_value, m_unit );
    matchUnitSuffix( s, "MiB", Absolute, m_value, m_unit );

    if ( !m_value )
        m_unit = None;
}


ResizeFSJob::ResizeFSJob( QObject* parent )
    : Calamares::CppJob( parent )
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


Calamares::JobResult
ResizeFSJob::exec()
{
    if ( !isValid() )
        return Calamares::JobResult::error(
            tr( "Invalid configuration" ),
            tr( "The file-system resize job has an invalid configuration "
                "and will not run." ) );

    // Get KPMCore
    auto backend_p = CoreBackendManager::self()->backend();
    if ( backend_p )
        cDebug() << "KPMCore backend @" << (void *)backend_p << backend_p->id() << backend_p->version();
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

    Device* resize_this_device = nullptr;
    Partition* resize_this_partition = nullptr;

    using DeviceList = QList< Device* >;
    DeviceList devices = backend_p->scanDevices( false );
    cDebug() << "ResizeFSJob found" << devices.count() << "devices.";
    for ( DeviceList::iterator dev_it = devices.begin(); dev_it != devices.end(); ++dev_it )
    {
        if ( ! (*dev_it) )
            continue;
        cDebug() << "ResizeFSJob found" << ( *dev_it )->deviceNode();
        for ( auto part_it = PartitionIterator::begin( *dev_it); part_it != PartitionIterator::end( *dev_it ); ++part_it )
        {
            cDebug() << ".." << ( *part_it )->mountPoint() << "on" << ( *part_it )->deviceNode();
            if ( ( !m_fsname.isEmpty() && ( *part_it )->mountPoint() == m_fsname ) ||
                 ( !m_devicename.isEmpty() && ( *part_it )->deviceNode() == m_devicename ) )
            {
                resize_this_device = ( *dev_it );
                resize_this_partition = ( *part_it );
                cDebug() << ".. matched configuration dev=" << m_devicename << "fs=" << m_fsname;
                break;
            }
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
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ResizeFSJobFactory, registerPlugin<ResizeFSJob>(); )
