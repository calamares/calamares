/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef GEOIP_HANDLER_H
#define GEOIP_HANDLER_H

#include "Interface.h"

#include <QString>
#include <QVariantMap>
#include <QtConcurrent/QtConcurrentRun>

namespace CalamaresUtils
{
namespace GeoIP
{

/** @brief Handle one complete GeoIP lookup.
 *
 * This class handles one complete GeoIP lookup. Create it with
 * suitable configuration values, then call get(). This is a
 * synchronous API and will return an invalid zone pair on
 * error or if the configuration is not understood. For an
 * async API, use query().
 */
class DLLEXPORT Handler
{
public:
    enum class Type
    {
        None,  // No lookup, returns empty string
        JSON,  // JSON-formatted data, returns extracted field
        XML,  // XML-formatted data, returns extracted field
        Fixed  // Returns selector string verbatim
    };

    /** @brief An unconfigured handler; this always returns errors. */
    Handler();
    /** @brief A handler for a specific GeoIP source.
     *
     * The @p implementation name selects an implementation; currently JSON and XML
     * are supported. The @p url is retrieved by query() and then the @p selector
     * is used to select something from the data returned by the @url.
     */
    Handler( const QString& implementation, const QString& url, const QString& selector );

    ~Handler();

    /** @brief Synchronously get the GeoIP result.
     *
     * If the Handler is valid, then do the actual fetching and interpretation
     * of data and return the result. An invalid Handler will return an
     * invalid (empty) result.
     */
    RegionZonePair get() const;
    /// @brief Like get, but don't interpret the contents
    QString getRaw() const;

    /** @brief Asynchronously get the GeoIP result.
     *
     * See get() for the return value.
     */
    QFuture< RegionZonePair > query() const;
    /// @brief Like query, but don't interpret the contents
    QFuture< QString > queryRaw() const;

    bool isValid() const { return m_type != Type::None; }
    Type type() const { return m_type; }
    QString url() const { return m_url; }
    QString selector() const { return m_selector; }

private:
    Type m_type;
    const QString m_url;
    const QString m_selector;
};

}  // namespace GeoIP
}  // namespace CalamaresUtils
#endif
