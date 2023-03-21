/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PythonQtJob.h"

#include "utils/PythonQtUtils.h"

PythonQtJob::PythonQtJob( PythonQtObjectPtr cxt, PythonQtObjectPtr pyJob, QObject* parent )
    : Calamares::Job( parent )
    , m_cxt( cxt )
    , m_pyJob( pyJob )
{
}


QString
PythonQtJob::prettyName() const
{
    return CalamaresUtils::lookupAndCall( m_pyJob, { "prettyName", "prettyname", "pretty_name" } ).toString();
}


QString
PythonQtJob::prettyDescription() const
{
    return CalamaresUtils::lookupAndCall( m_pyJob, { "prettyDescription", "prettydescription", "pretty_description" } )
        .toString();
}


QString
PythonQtJob::prettyStatusMessage() const
{
    return CalamaresUtils::lookupAndCall( m_pyJob,
                                          { "prettyStatusMessage", "prettystatusmessage", "pretty_status_message" } )
        .toString();
}


Calamares::JobResult
PythonQtJob::exec()
{
    QVariant response = m_pyJob.call( "exec" );
    if ( response.isNull() )
    {
        return Calamares::JobResult::ok();
    }

    QVariantMap map = response.toMap();
    if ( map.isEmpty() || map.value( "ok" ).toBool() )
    {
        return Calamares::JobResult::ok();
    }

    return Calamares::JobResult::error( map.value( "message" ).toString(), map.value( "details" ).toString() );
}
