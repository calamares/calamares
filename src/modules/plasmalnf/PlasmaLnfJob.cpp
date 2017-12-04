/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "PlasmaLnfJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

PlasmaLnfJob::PlasmaLnfJob( const QString& lnfPath, const QString& id )
    : m_lnfPath( lnfPath )
    , m_id( id )
{
}


PlasmaLnfJob::~PlasmaLnfJob()
{
}


QString
PlasmaLnfJob::prettyName() const
{
    return tr( "Plasma Look-and-Feel Job" );
}

QString
PlasmaLnfJob::prettyDescription() const
{
    return prettyName();
}

QString PlasmaLnfJob::prettyStatusMessage() const
{
    return prettyName();
}


Calamares::JobResult
PlasmaLnfJob::exec()
{
    cDebug() << "Plasma Look-and-Feel Job";

    auto system = CalamaresUtils::System::instance();
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    QStringList command(
    {
        "sudo", "-E", "-H", "-u", gs->value( "username" ).toString(),
        m_lnfPath, "-platform", "minimal", "--resetLayout", "--apply", m_id
    } );

    int r = system->targetEnvCall( command );
    if ( r )
        return Calamares::JobResult::error(
                   tr( "Could not select KDE Plasma Look-and-Feel package" ),
                   tr( "Could not select KDE Plasma Look-and-Feel package" ) );

    return Calamares::JobResult::ok();
}

