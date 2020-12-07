/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Sync.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

void
CalamaresUtils::Partition::sync()
{
    /* I would normally use full paths here, e.g. /sbin/udevadm and /bin/sync,
     * but there's enough variation / opinion on where these executables
     * should live, that full paths would need to be configurable.
     * Instead, just run them and assume they're found in PATH;
     * either chroot(8) or env(1) is used to run the command,
     * and they do suitable lookup.
     */
    auto r = CalamaresUtils::System::runCommand( { "udevadm", "settle" }, std::chrono::seconds( 10 ) );

    if ( r.getExitCode() != 0 )
    {
        cWarning() << "Could not settle disks.";
        r.explainProcess( "udevadm", std::chrono::seconds( 10 ) );
    }

    CalamaresUtils::System::runCommand( { "sync" }, std::chrono::seconds( 10 ) );
}
