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

#ifndef GEOIP_H
#define GEOIP_H

#include <QPair>
#include <QString>
#include <QUrl>

class QByteArray;

/**
 * @brief Interface for GeoIP retrievers.
 *
 * A GeoIP retriever takes a configured URL (from the config file)
 * and can handle the data returned from its interpretation of that
 * configured URL, returning a region and zone.
 */
class GeoIP
{
public:
    using RegionZonePair = QPair<QString, QString>;

    virtual ~GeoIP();

    /** @brief Handle a (successful) request by interpreting the data.
     *
     * Should return a ( <zone>, <region> ) pair, e.g.
     * ( "Europe", "Amsterdam" ). This is called **only** if the
     * request to the fullUrl was successful; the handler
     * is free to read as much, or as little, data as it
     * likes. On error, returns a RegionZonePair with empty
     * strings (e.g. ( "", "" ) ).
     */
    virtual RegionZonePair processReply( const QByteArray& ) = 0;

    /** @brief Splits a region/zone string into a pair.
     *
     * Cleans up the string by removing backslashes (\\)
     * since some providers return silly-escaped names. Replaces
     * spaces with _ since some providers return human-readable names.
     * Splits on the first / in the resulting string, or returns a
     * pair of empty QStrings if it can't. (e.g. America/North Dakota/Beulah
     * will return "America", "North_Dakota/Beulah").
     */
    static RegionZonePair splitTZString( const QString& s );

protected:
    GeoIP( const QString& e = QString() );

    QString m_element;  // string for selecting from data
} ;

#endif
