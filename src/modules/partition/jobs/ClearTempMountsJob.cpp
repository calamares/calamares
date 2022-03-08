/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ClearTempMountsJob.h"

#include "partition/Mount.h"
#include "utils/Logger.h"
#include "utils/String.h"

#include <kpmcore/util/report.h>

#include <QFile>
#include <QProcess>
#include <QStringList>

#include <algorithm>

ClearTempMountsJob::ClearTempMountsJob()
    : Calamares::Job()
{
}


QString
ClearTempMountsJob::prettyName() const
{
    return tr( "Clear all temporary mounts." );
}


QString
ClearTempMountsJob::prettyStatusMessage() const
{
    return tr( "Clearing all temporary mounts." );
}


Calamares::JobResult
ClearTempMountsJob::exec()
{
    Logger::Once o;
    // Fetch a list of current mounts to Calamares temporary directories.
    using MtabInfo = CalamaresUtils::Partition::MtabInfo;
    auto targetMounts = MtabInfo::fromMtabFilteredByPrefix( QStringLiteral( "/tmp/calamares-" ) );

    if ( targetMounts.isEmpty() )
    {
        return Calamares::JobResult::ok();
    }
    std::sort( targetMounts.begin(), targetMounts.end(), MtabInfo::mountPointOrder );

    QStringList goodNews;
    for ( const auto& m : qAsConst( targetMounts ) )
    {
        cDebug() << o << "Will try to umount path" << m.mountPoint;
        if ( CalamaresUtils::Partition::unmount( m.mountPoint, { "-lv" } ) == 0 )
        {
            // Returns the program's exit code, so 0 is success
            goodNews.append( QString( "Successfully unmounted %1." ).arg( m.mountPoint ) );
        }
    }

    Calamares::JobResult ok = Calamares::JobResult::ok();
    ok.setMessage( tr( "Cleared all temporary mounts." ) );
    ok.setDetails( goodNews.join( "\n" ) );

    cDebug() << o << "ClearTempMountsJob finished. Here's what was done:\n" << Logger::DebugList( goodNews );

    return ok;
}
