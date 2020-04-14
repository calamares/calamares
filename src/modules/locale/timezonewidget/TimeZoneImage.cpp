/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "TimeZoneImage.h"

#include "utils/Logger.h"

#include <QDir>

static const char* zoneNames[] =
          { "0.0",  "1.0",  "2.0",  "3.0",  "3.5",  "4.0",  "4.5",  "5.0",  "5.5",   "5.75", "6.0",   "6.5",  "7.0",
            "8.0",  "9.0",  "9.5",  "10.0", "10.5", "11.0", "11.5", "12.0", "12.75", "13.0", "-1.0",  "-2.0", "-3.0",
            "-3.5", "-4.0", "-4.5", "-5.0", "-5.5", "-6.0", "-7.0", "-8.0", "-9.0",  "-9.5", "-10.0", "-11.0" } ;

TimeZoneImageList::TimeZoneImageList()
{
}

TimeZoneImageList TimeZoneImageList::fromQRC()
{
    TimeZoneImageList l;
    for ( const auto* zoneName : zoneNames )
    {
        l.append( QImage( QStringLiteral( ":/images/timezone_" ) + zoneName + ".png" ) );
        l.last().setText( QStringLiteral( "zone" ), zoneName );
    }

    return l;
}

TimeZoneImageList TimeZoneImageList::fromDirectory(const QString& dirName)
{
    TimeZoneImageList l;
    QDir dir( dirName );
    if ( !dir.exists() )
    {
        cWarning() << "TimeZone images directory" << dirName << "does not exist.";
        return l;
    }

    for ( const auto* zoneName : zoneNames )
    {
        l.append( QImage( dir.filePath( QStringLiteral("timezone_" ) + zoneName + ".png" ) ) );
        l.last().setText( QStringLiteral( "zone" ), zoneName );
    }

    return l;
}

int TimeZoneImageList::zoneCount()
{
    return sizeof(zoneNames) / sizeof(zoneNames[0]);
}
