/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#include "Interface.h"

#include "utils/Logger.h"
#include "utils/String.h"

namespace CalamaresUtils
{
namespace GeoIP
{

Interface::Interface( const QString& e )
    : m_element( e )
{
}

Interface::~Interface() {}

RegionZonePair
splitTZString( const QString& tz )
{
    QString timezoneString( tz );
    timezoneString.remove( '\\' );
    timezoneString.replace( ' ', '_' );

    QStringList tzParts = timezoneString.split( '/', SplitSkipEmptyParts );
    if ( tzParts.size() >= 2 )
    {
        cDebug() << "GeoIP reporting" << timezoneString;
        QString region = tzParts.takeFirst();
        QString zone = tzParts.join( '/' );
        return RegionZonePair( region, zone );
    }

    return RegionZonePair( QString(), QString() );
}

}  // namespace GeoIP
}  // namespace CalamaresUtils
