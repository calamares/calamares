/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "ContextualProcessJob.h"

#include <QProcess>
#include <QDateTime>
#include <QThread>

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/Logger.h"

ContextualProcessJob::ContextualProcessJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


ContextualProcessJob::~ContextualProcessJob()
{
}


QString
ContextualProcessJob::prettyName() const
{
    return tr( "Contextual Processes Job" );
}


Calamares::JobResult
ContextualProcessJob::exec()
{
    QThread::sleep( 3 );

    return Calamares::JobResult::ok();
}


void
ContextualProcessJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_configurationMap = configurationMap;
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( ContextualProcessJobFactory, registerPlugin<ContextualProcessJob>(); )
