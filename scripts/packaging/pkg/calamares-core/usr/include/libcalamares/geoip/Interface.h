/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef GEOIP_INTERFACE_H
#define GEOIP_INTERFACE_H

#include "DllMacro.h"

#include <QPair>
#include <QString>
#include <QUrl>

class QByteArray;

namespace CalamaresUtils
{
namespace GeoIP
{
/** @brief A Region, Zone pair of strings
 *
 * A GeoIP lookup returns a timezone, which is represented as a Region,
 * Zone pair of strings (e.g. "Europe" and "Amsterdam"). Generally,
 * pasting the strings back together with a "/" is the right thing to
 * do. The Zone **may** contain a "/" (e.g. "Kentucky/Monticello").
 */
class DLLEXPORT RegionZonePair : public QPair< QString, QString >
{
public:
    /** @brief Construct from an existing pair. */
    explicit RegionZonePair( const QPair& p )
        : QPair( p )
    {
    }
    /** @brief Construct from two strings, like qMakePair(). */
    RegionZonePair( const QString& region, const QString& zone )
        : QPair( region, zone )
    {
    }
    /** @brief An invalid zone pair (empty strings). */
    RegionZonePair()
        : QPair( QString(), QString() )
    {
    }

    bool isValid() const { return !first.isEmpty(); }
};

/** @brief Splits a region/zone string into a pair.
 *
 * Cleans up the string by removing backslashes (\\)
 * since some providers return silly-escaped names. Replaces
 * spaces with _ since some providers return human-readable names.
 * Splits on the first / in the resulting string, or returns a
 * pair of empty QStrings if it can't. (e.g. America/North Dakota/Beulah
 * will return "America", "North_Dakota/Beulah").
 */
DLLEXPORT RegionZonePair splitTZString( const QString& s );

/**
 * @brief Interface for GeoIP retrievers.
 *
 * A GeoIP retriever takes a configured URL (from the config file)
 * and can handle the data returned from its interpretation of that
 * configured URL, returning a region and zone.
 */
class DLLEXPORT Interface
{
public:
    virtual ~Interface();

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

    /** @brief Get the raw reply data. */
    virtual QString rawReply( const QByteArray& ) = 0;

protected:
    Interface( const QString& element = QString() );

    QString m_element;  // string for selecting from data
};

}  // namespace GeoIP
}  // namespace CalamaresUtils
#endif
