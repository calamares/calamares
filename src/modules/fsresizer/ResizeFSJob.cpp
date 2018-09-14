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

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

ResizeFSJob::RelativeSize::RelativeSize()
    : m_unit( None )
    , m_value( 0 )
{
}


ResizeFSJob::RelativeSize::RelativeSize( const QString& s)
    : m_unit( None )
    , m_value( 0 )
{
    QString valuePart;

    if ( s.endsWith( '%' ) )
    {
        valuePart = s.left( s.length() - 1 );
        m_unit = Percent;
    }
    if ( s.endsWith( "MiB" ) )
    {
        valuePart = s.left( s.length() - 3 );
        m_unit = Absolute;
    }

    if ( ( m_unit != None ) && !valuePart.isEmpty() )
        m_value = valuePart.toInt();

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
