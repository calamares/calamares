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

#ifndef GEOIPXML_H
#define GEOIPXML_H

#include "GeoIP.h"

/** @brief GeoIP lookup with XML data
 *
 * The data is assumed to be in XML format with a
 *      <Response><TimeZone></TimeZone></Response>
 * element, which contains the text (string) for the region/zone. This
 * format is  expected by, e.g. the Ubiquity installer.
 */
struct XMLGeoIP : public GeoIP
{
    virtual RegionZonePair processReply( const QByteArray& );
} ;

#endif
