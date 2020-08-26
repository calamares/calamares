/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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


PlasmaLnfJob::~PlasmaLnfJob() {}


QString
PlasmaLnfJob::prettyName() const
{
    return tr( "Plasma Look-and-Feel Job" );
}

QString
PlasmaLnfJob::prettyStatusMessage() const
{
    return prettyName();
}


Calamares::JobResult
PlasmaLnfJob::exec()
{
    cDebug() << "Plasma Look-and-Feel Job";

    auto system = CalamaresUtils::System::instance();
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    QStringList command( { "sudo",
                           "-E",
                           "-H",
                           "-u",
                           gs->value( "username" ).toString(),
                           m_lnfPath,
                           "-platform",
                           "minimal",
                           "--resetLayout",
                           "--apply",
                           m_id } );

    int r = system->targetEnvCall( command );
    if ( r )
        return Calamares::JobResult::error( tr( "Could not select KDE Plasma Look-and-Feel package" ),
                                            tr( "Could not select KDE Plasma Look-and-Feel package" ) );

    return Calamares::JobResult::ok();
}
