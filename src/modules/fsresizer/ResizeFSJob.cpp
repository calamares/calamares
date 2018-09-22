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

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

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
    auto backend_p = CoreBackendManager::self()->backend();
    if ( backend_p )
        cDebug() << "KPMCore backend @" << (void *)backend_p << backend_p->id() << backend_p->version();
    else
        cDebug() << "No KPMCore backend";

    if ( !isValid() )
        return Calamares::JobResult::error(
            tr( "Invalid configuration" ),
            tr( "The file-system resize job has an invalid configuration "
                "and will not run." ) );

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
