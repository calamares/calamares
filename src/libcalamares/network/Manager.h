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

#include <QByteArray>
#include <QObject>
#include <QUrl>

#include <chrono>
#include <memory>

class QNetworkReply;
class QNetworkRequest;

namespace CalamaresUtils
{
namespace Network
{
class DLLEXPORT RequestOptions
{
public:
    using milliseconds = std::chrono::milliseconds;

    enum Flag
    {
        FollowRedirect = 0x1,
        FakeUserAgent = 0x100
    };
    Q_DECLARE_FLAGS( Flags, Flag )

    RequestOptions()
        : m_flags( Flags() )
        , m_timeout( -1 )
    {
    }

    RequestOptions( Flags f, milliseconds timeout = milliseconds( -1 ) )
        : m_flags( f )
        , m_timeout( timeout )
    {
    }

    void applyToRequest( QNetworkRequest* ) const;

    bool hasTimeout() const { return m_timeout > milliseconds( 0 ); }
    auto timeout() const { return m_timeout; }

private:
    Flags m_flags;
    milliseconds m_timeout;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( RequestOptions::Flags );

struct RequestStatus
{
    enum State
    {
        Ok,
        Timeout,  // Timeout exceeded
        Failed,  // bad Url
        Empty  // for ping(), response is empty
    };

    RequestStatus( State s = Ok )
        : status( s )
    {
    }
    operator bool() const { return status == Ok; }

    State status;
};

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
     * Returns a RequestStatus, which converts to @c true if the ping
     * was successful. Other status reasons convert to @c false,
     * typically because of no data, a Url error or no network access.
     *
     * May return Empty if the request was successful but returned
     * no data at all.
     */
    RequestStatus synchronousPing( const QUrl& url, const RequestOptions& options = RequestOptions() );

    /** @brief Downloads the data from a given @p url
     *
     * Returns the data as a QByteArray, or an empty
     * array if any error occurred (or no data was returned).
     */
    QByteArray synchronousGet( const QUrl& url, const RequestOptions& options = RequestOptions() );

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

    /** @brief Do a network request asynchronously.
     *
     * Returns a pointer to the reply-from-the-request.
     * This may be a nullptr if an error occurs immediately.
     * The caller is responsible for cleaning up the reply (eventually).
     */
    QNetworkReply* asynchronousGet( const QUrl& url, const RequestOptions& options = RequestOptions() );

private:
    class Private;
    std::unique_ptr< Private > d;
};
}  // namespace Network
}  // namespace CalamaresUtils
#endif  // LIBCALAMARES_NETWORK_MANAGER_H
