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

#ifndef GEOIP_GEOIPFIXED_H
#define GEOIP_GEOIPFIXED_H

#include "Interface.h"

namespace CalamaresUtils
{
namespace GeoIP
{
/** @brief GeoIP with a fixed return value
 *
 * The data is ignored entirely and the attribute value is returned unchanged.
 * Note that you still need to provide a usable URL for a successful GeoIP
 * lookup -- the URL's data is just ignored.
 *
 * @note This class is an implementation detail.
 */
class GeoIPFixed : public Interface
{
public:
    /** @brief Configure the value to return from rawReply()
     *
     * An empty string, which would not be a valid zone name, is
     * translated to "Europe/Amsterdam".
     */
    explicit GeoIPFixed( const QString& value = QString() );

    virtual RegionZonePair processReply( const QByteArray& ) override;
    virtual QString rawReply( const QByteArray& ) override;
};

}  // namespace GeoIP
}  // namespace CalamaresUtils
#endif
