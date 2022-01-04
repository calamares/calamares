/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
