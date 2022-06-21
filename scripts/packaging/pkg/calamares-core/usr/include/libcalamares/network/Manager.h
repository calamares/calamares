/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARES_NETWORK_MANAGER_H
#define LIBCALAMARES_NETWORK_MANAGER_H

#include "DllMacro.h"

#include <QByteArray>
#include <QDebug>
#include <QObject>
#include <QUrl>
#include <QVector>

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
        HttpError,  // some other HTTP error (eg. SSL failed)
        Empty  // for ping(), response is empty
    };

    RequestStatus( State s = Ok )
        : status( s )
    {
    }
    operator bool() const { return status == Ok; }

    State status;
};

QDebug& operator<<( QDebug& s, const RequestStatus& e );

class DLLEXPORT Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY( bool hasInternet READ hasInternet NOTIFY hasInternetChanged FINAL )
    Q_PROPERTY( QVector< QUrl > checkInternetUrls READ getCheckInternetUrls WRITE setCheckHasInternetUrl )

    Manager();

public:
    /** @brief Gets the single Manager instance.
     *
     * Typical code will use `auto& nam = Manager::instance();`
     * to keep the reference.
     */
    static Manager& instance();
    ~Manager() override;

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

    /// @brief Adds an (extra) URL to check
    void addCheckHasInternetUrl( const QUrl& url );

    /// @brief Set a collection of URLs used for the general "is there internet" check.
    void setCheckHasInternetUrl( const QVector< QUrl >& urls );

    /// @brief What URLs are used to check for internet connectivity?
    QVector< QUrl > getCheckInternetUrls() const;

    /** @brief Do a network request asynchronously.
     *
     * Returns a pointer to the reply-from-the-request.
     * This may be a nullptr if an error occurs immediately.
     * The caller is responsible for cleaning up the reply (eventually).
     */
    QNetworkReply* asynchronousGet( const QUrl& url, const RequestOptions& options = RequestOptions() );

public Q_SLOTS:
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

signals:
    /** @brief Indicates that internet connectivity status has changed
     *
     * The value is that returned from hasInternet() -- @c true when there
     * is connectivity, @c false otherwise.
     */
    void hasInternetChanged( bool );

private:
    class Private;
    std::unique_ptr< Private > d;
};
}  // namespace Network
}  // namespace CalamaresUtils
#endif  // LIBCALAMARES_NETWORK_MANAGER_H
