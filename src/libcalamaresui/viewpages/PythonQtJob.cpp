/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include "PythonQtJob.h"

#include "utils/PythonQtUtils.h"

PythonQtJob::PythonQtJob( PythonQtObjectPtr cxt,
                          PythonQtObjectPtr pyJob,
                          QObject* parent )
    : Calamares::Job( parent )
    , m_cxt( cxt )
    , m_pyJob( pyJob )
{

}


QString
PythonQtJob::prettyName() const
{
    return CalamaresUtils::lookupAndCall( m_pyJob,
                                          { "prettyName",
                                            "prettyname",
                                            "pretty_name" } ).toString();
}


QString
PythonQtJob::prettyDescription() const
{
    return CalamaresUtils::lookupAndCall( m_pyJob,
                                          { "prettyDescription",
                                            "prettydescription",
                                            "pretty_description" } ).toString();
}


QString
PythonQtJob::prettyStatusMessage() const
{
    return CalamaresUtils::lookupAndCall( m_pyJob,
                                          { "prettyStatusMessage",
                                            "prettystatusmessage",
                                            "pretty_status_message" } ).toString();
}


Calamares::JobResult
PythonQtJob::exec()
{
    QVariant response = m_pyJob.call( "exec" );
    if ( response.isNull() )
        return Calamares::JobResult::ok();

    QVariantMap map = response.toMap();
    if ( map.isEmpty() || map.value( "ok" ).toBool() )
        return Calamares::JobResult::ok();

    return Calamares::JobResult::error( map.value( "message" ).toString(),
                                        map.value( "details" ).toString() );
}
