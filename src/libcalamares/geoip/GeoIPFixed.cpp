/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
