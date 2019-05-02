/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef GEOIP_HANDLER_H
#define GEOIP_HANDLER_H

#include "Interface.h"

#include <QString>
#include <QVariantMap>

namespace CalamaresUtils {}
namespace CalamaresUtils::GeoIP
{

/** @brief Handle one complete GeoIP lookup.
 *
 * This class handles one complete GeoIP lookup. Create it with
 * suitable configuration values, then call lookup(). This is a
 * synchronous API and will return an invalid zone pair on
 * error or if the configuration is not understood/
 */
class DLLEXPORT Handler
{
public:
    /** @brief An unconfigured handler; this always returns errors. */
    Handler();
    /** @brief A handler for a specific GeoIP source.
     *
     * The @p implementation name selects an implementation; currently JSON and XML
     * are supported. The @p url is retrieved by query() and then the @p selector
     * is used to select something from the data returned by the @url.
     */
    Handler( const QString& implementation, const QString& url, const QString& selector );
    /** @brief A handler for a specific GeoIP source.
     *
     * This is like the 3-QString Handler constructor, except the strings
     * are extracted from the map, which is typically part of the configuration
     * of a Calamares module. The strings are fetched from these keys:
     *  - implementation from "style" or "geoipStyle" (if the first does not exist)
     *  - url from "url" or "geoipUrl" (if the first does not exist)
     *  - selector from "selector" or "geoipSelector" (if the first does not exist)
     * Unlike the 3-QString Handler constructor, this also understands implementations
     * "legacy" and blank, which are interpreted as "JSON", except that the url is extended
     * by "/json/" before fetching.
     */
    Handler( const QVariantMap& config );

    ~Handler();

    RegionZonePair query() const;

    bool isValid() const;

private:
    Interface* m_interface;
    const QString m_url;
};

}  // namespace
#endif

