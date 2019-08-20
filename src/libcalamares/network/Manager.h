/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef LIBCALAMARES_NETWORK_MANAGER_H
#define LIBCALAMARES_NETWORK_MANAGER_H

#include "DllMacro.h"

#include <QObject>
#include <QUrl>

#include <memory>

namespace CalamaresUtils
{
namespace Network
{
class DLLEXPORT Manager : QObject
{
    Q_OBJECT

    Manager();

public:
    /** @brief Gets the single Manager instance.
     *
     * Typical code will use `auto& nam = Manager::instance();`
     * to keep the reference.
     */
    static Manager& instance();
    virtual ~Manager();

    /** @brief Checks if the given @p url returns data.
     *
     * Returns @c true if it does; @c false means no data, typically
     * because of an error or no network access.
     */
    bool synchronousPing( const QUrl& url );

    /// @brief Set the URL which is used for the general "is there internet" check.
    void setCheckHasInternetUrl( const QUrl& url );
    /** @brief Do an explicit check for internet connectivity.
     *
     * This **may** do a ping to the configured check URL, but can also
     * use other mechanisms.
     */
    bool checkHasInternet();
    /** @brief Is there internet connectivity?
     *
     * This returns the result of the last explicit check, or if there
     * is other information about the state of the internet connection,
     * whatever is known. @c true means you can expect (all) internet
     * connectivity to be present.
     */
    bool hasInternet();

private:
    struct Private;
    std::unique_ptr< Private > d;
};
}  // namespace Network
}  // namespace CalamaresUtils
#endif  // LIBCALAMARES_NETWORK_MANAGER_H
