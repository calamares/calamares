/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
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

#ifndef GEOIP_GEOIPXML_H
#define GEOIP_GEOIPXML_H

#include "Interface.h"

namespace CalamaresUtils
{
namespace GeoIP
{
/** @brief GeoIP lookup with XML data
 *
 * The data is assumed to be in XML format with a
 *      <Response><TimeZone></TimeZone></Response>
 * element, which contains the text (string) for the region/zone. This
 * format is  expected by, e.g. the Ubiquity installer.
 *
 * @note This class is an implementation detail.
 */
class GeoIPXML : public Interface
{
public:
    /** @brief Configure the element tag which is selected.
     *
     * If an empty string is passed in (not a valid element tag),
     * then "TimeZone" is used.
     */
    explicit GeoIPXML( const QString& element = QString() );

    virtual RegionZonePair processReply( const QByteArray& ) override;
    virtual QString rawReply( const QByteArray& ) override;
};

}  // namespace GeoIP
}  // namespace CalamaresUtils
#endif
