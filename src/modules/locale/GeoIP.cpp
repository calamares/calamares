/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "GeoIP.h"

#include "utils/Logger.h"

GeoIP::~GeoIP()
{
}

GeoIP::RegionZonePair
GeoIP::splitTZString( const QString& timezoneString )
{
    QStringList tzParts = timezoneString.split( '/', QString::SkipEmptyParts );
    if ( tzParts.size() >= 2 )
    {
        cDebug() << "GeoIP reporting" << timezoneString;
        QString region = tzParts.takeFirst();
        QString zone = tzParts.join( '/' );
        return qMakePair( region, zone );
    }

    return qMakePair( QString(), QString() );
}
