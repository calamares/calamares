/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "RemoveUserJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QFile>

RemoveUserJob::RemoveUserJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}


RemoveUserJob::~RemoveUserJob() {}


QString
RemoveUserJob::prettyName() const
{
    return tr( "Remove live user from target system" );
}

Calamares::JobResult
RemoveUserJob::exec()
{
    if ( m_username.isEmpty() )
    {
        cWarning() << "Ignoring an empty username.";
        return Calamares::JobResult::ok();
    }

    auto* s = CalamaresUtils::System::instance();
    auto r = s->targetEnvCommand( { QStringLiteral( "userdel" ),
                                    QStringLiteral( "-f" ),  // force
                                    QStringLiteral( "-r" ),  // remove home-dir and mail
                                    m_username } );
    if ( r.getExitCode() != 0 )
    {
        cWarning() << "Cannot remove user" << m_username << "userdel terminated with exit code" << r.getExitCode();
    }
    return Calamares::JobResult::ok();
}


void
RemoveUserJob::setConfigurationMap( const QVariantMap& map )
{
    m_username = CalamaresUtils::getString( map, "username" );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( RemoveUserJobFactory, registerPlugin< RemoveUserJob >(); )
