/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "Sync.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

void CalamaresUtils::Partition::sync()
{
    auto* s = CalamaresUtils::System::instance();

    auto r = s->runCommand( CalamaresUtils::System::RunLocation::RunInHost,
                   { "/sbin/udevadm", "settle" },
                   QString(),
                   QString(),
                   10 // timeout seconds
    );

    if ( r.getExitCode() != 0 )
    {
        cWarning() << "Could not settle disks.";
        r.explainProcess( "udevadm", 10 );
    }

    s->runCommand( CalamaresUtils::System::RunLocation::RunInHost,
                   { "/bin/sync" },
                   QString(),
                   QString(),
                   10 // timeout seconds
    );
}
