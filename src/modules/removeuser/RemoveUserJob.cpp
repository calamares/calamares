/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017. Alf Gaida <agaida@siduction.org>
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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
