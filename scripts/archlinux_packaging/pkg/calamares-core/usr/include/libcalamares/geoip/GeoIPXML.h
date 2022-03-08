/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
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
