/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
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

#include "Mount.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <QDir>

namespace CalamaresUtils
{
namespace Partition
{

int
mount( const QString& devicePath, const QString& mountPoint, const QString& filesystemName, const QString& options )
{
    if ( devicePath.isEmpty() || mountPoint.isEmpty() )
    {
        if ( devicePath.isEmpty() )
        {
            cWarning() << "Can't mount an empty device.";
        }
        if ( mountPoint.isEmpty() )
        {
            cWarning() << "Can't mount on an empty mountpoint.";
        }

        return static_cast< int >( ProcessResult::Code::NoWorkingDirectory );
    }

    QDir mountPointDir( mountPoint );
    if ( !mountPointDir.exists() )
    {
        bool ok = mountPointDir.mkpath( mountPoint );
        if ( !ok )
        {
            cWarning() << "Could not create mountpoint" << mountPoint;
            return static_cast< int >( ProcessResult::Code::NoWorkingDirectory );
        }
    }

    QStringList args = { "mount", devicePath, mountPoint };

    if ( !filesystemName.isEmpty() )
    {
        args << "-t" << filesystemName;
    }
    if ( !options.isEmpty() )
    {
        args << "-o" << options;
    }

    auto r = CalamaresUtils::System::instance()->runCommand(
        CalamaresUtils::System::RunLocation::RunInHost, args, QString(), QString(), 10 );
    return r.getExitCode();
}

}  // namespace Partition
}  // namespace CalamaresUtils
