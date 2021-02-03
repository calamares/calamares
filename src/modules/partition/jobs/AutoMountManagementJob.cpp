/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "AutoMountManagementJob.h"

#include "utils/Logger.h"

AutoMountManagementJob::AutoMountManagementJob( bool disable )
    : m_disable( disable )
{
}

QString
AutoMountManagementJob::prettyName() const
{
    return tr( "Manage auto-mount settings" );
}

Calamares::JobResult
AutoMountManagementJob::exec()
{
    Logger::CDebug( Logger::LOGVERBOSE ) << "this" << Logger::Pointer( this ) << "value" << Logger::Pointer( m_stored )
                                         << ( m_stored ? "restore" : m_disable ? "disable" : "enable" );
    if ( m_stored )
    {
        CalamaresUtils::Partition::automountRestore( m_stored );
        m_stored.reset();
    }
    else
    {
        m_stored = CalamaresUtils::Partition::automountDisable( m_disable );
    }
    return Calamares::JobResult::ok();
}
