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

#ifndef GEOIP_GEOIPJSON_H
#define GEOIP_GEOIPJSON_H

#include "Interface.h"

namespace CalamaresUtils
{
namespace GeoIP
{
/** @brief GeoIP lookup for services that return JSON.
 *
 * This is the original implementation of GeoIP lookup,
 * (e.g. using the FreeGeoIP.net service), or similar.
 *
 * The data is assumed to be in JSON format with a time_zone attribute.
 *
 * @note This class is an implementation detail.
 */
class GeoIPJSON : public Interface
{
public:
    /** @brief Configure the attribute name which is selected.
     *
     * If an empty string is passed in (not a valid attribute name),
     * then "time_zone" is used.
     */
    explicit GeoIPJSON( const QString& attribute = QString() );

    virtual RegionZonePair processReply( const QByteArray& ) override;
    virtual QString rawReply( const QByteArray& ) override;
};

}  // namespace GeoIP
}  // namespace CalamaresUtils
#endif
