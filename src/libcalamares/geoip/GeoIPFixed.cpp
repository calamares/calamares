/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
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
 */

#include "GeoIPFixed.h"

namespace CalamaresUtils
{
namespace GeoIP
{

GeoIPFixed::GeoIPFixed( const QString& attribute )
    : Interface( attribute.isEmpty() ? QStringLiteral( "Europe/Amsterdam" ) : attribute )
{
}

QString
GeoIPFixed::rawReply( const QByteArray& )
{
    return m_element;
}

GeoIP::RegionZonePair
GeoIPFixed::processReply( const QByteArray& data )
{
    return splitTZString( rawReply( data ) );
}

}  // namespace GeoIP
}  // namespace CalamaresUtils
