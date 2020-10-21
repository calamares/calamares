/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "MiscJobs.h"

#include "Config.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Permissions.h"

SetupSudoJob::SetupSudoJob( const QString& group )
    : m_sudoGroup( group )
{
}

QString
SetupSudoJob::prettyName() const
{
    return tr( "Configure <pre>sudo</pre> users." );
}

Calamares::JobResult
SetupSudoJob::exec()
{
    if ( m_sudoGroup.isEmpty() )
    {
        return Calamares::JobResult::ok();
    }

    QString sudoersLine = QString( "%%1 ALL=(ALL) ALL\n" ).arg( m_sudoGroup );
    auto fileResult
        = CalamaresUtils::System::instance()->createTargetFile( QStringLiteral( "/etc/sudoers.d/10-installer" ),
                                                                sudoersLine.toUtf8().constData(),
                                                                CalamaresUtils::System::WriteMode::Overwrite );

    if ( fileResult )
    {
        if ( !CalamaresUtils::Permissions::apply( fileResult.path(), 0440 ) )
        {
            return Calamares::JobResult::error( tr( "Cannot chmod sudoers file." ) );
        }
    }
    else
    {
        return Calamares::JobResult::error( tr( "Cannot create sudoers file for writing." ) );
    }

    return Calamares::JobResult::ok();
}
