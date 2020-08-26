/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
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
