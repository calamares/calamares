/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 */

#include "AutoMount.h"

#include "utils/Logger.h"

#include <QtDBus>

#include <optional>

namespace CalamaresUtils
{
namespace Partition
{

struct AutoMountInfo
{
    bool hasSolid = false;
    bool wasSolidModuleAutoLoaded = false;
};

/** @section Solid
 *
 * KDE Solid automount management.
 *
 * Solid can be influenced through DBus calls to kded5. The following code
 * handles Solid: if Solid exists (e.g. we're in a KDE Plasma desktop)
 * then try to turn off automount that way.
 */

/** @brief Boilerplate for a call to kded5
 *
 * Returns a method-call message, ready for arguments and call().
 */
static inline QDBusMessage
kdedCall( const QString& method )
{
    return QDBusMessage::createMethodCall(
        QStringLiteral( "org.kde.kded5" ), QStringLiteral( "/kded" ), QStringLiteral( "org.kde.kded5" ), method );
}

/** @brief Log a response from call()
 *
 * Logs without a function header so it is simple to use from an existing
 * logging-block. Assumes @p r is a reply or an error message.
 *
 * @internal
 */
static void
logDBusResponse( QDBusMessage&& r )
{
    if ( r.type() == QDBusMessage::ReplyMessage )
    {
        cDebug() << Logger::SubEntry << r.type() << "reply" << r.arguments();
    }
    else
    {
        cDebug() << Logger::SubEntry << r.type() << "error" << r.errorMessage();
    }
}

/** @brief Enables (or disables) automount for Solid
 *
 * If @p enable is @c true, enables automount. Otherwise, disables it.
 * This throws some DBbus messages on the wire and forgets about them.
 */
// This code comes, roughly, from the KCM for removable devices.
static void
enableSolidAutoMount( QDBusConnection& dbus, bool enable )
{
    const auto moduleName = QVariant( QStringLiteral( "device_automounter" ) );

    // Stop module from auto-loading
    {
        auto msg = kdedCall( QStringLiteral( "setModuleAutoloading" ) );
        msg.setArguments( { moduleName, QVariant( enable ) } );
        logDBusResponse( dbus.call( msg, QDBus::Block ) );
    }

    // Stop module
    {
        auto msg = kdedCall( enable ? QStringLiteral( "loadModule" ) : QStringLiteral( "unloadModule" ) );
        msg.setArguments( { moduleName } );
        logDBusResponse( dbus.call( msg, QDBus::Block ) );
    }
}

/** @brief Check if Solid exists and has automount set
 *
 * Updates the @p info object with the discovered information.
 * - if there is no Solid available on DBus, sets hasSolid to @c false
 * - if there is Solid available on DBusm, sets *hasSolid* to @c true
 *   and places the queried value of automounting in *wasSolidModuleAutoLoaded*.
 */
static void
querySolidAutoMount( QDBusConnection& dbus, AutoMountInfo& info )
{
    const auto moduleName = QVariant( QStringLiteral( "device_automounter" ) );

    // Find previous setting; this **does** need to block
    auto msg = kdedCall( QStringLiteral( "isModuleAutoloaded" ) );
    msg.setArguments( { moduleName } );
    std::optional< bool > result;
    QDBusMessage r = dbus.call( msg, QDBus::Block );
    if ( r.type() == QDBusMessage::ReplyMessage )
    {
        auto arg = r.arguments();
        if ( arg.length() == 1 )
        {
            auto v = arg.at( 0 );
            if ( v.isValid() && v.type() == QVariant::Bool )
            {
                result = v.toBool();
            }
        }
        if ( !result.has_value() )
        {
            cDebug() << "No viable response from Solid" << r.path();
        }
    }
    else
    {
        // It's an error message
        cDebug() << "Solid not available:" << r.errorMessage();
    }
    info.hasSolid = result.has_value();
    info.wasSolidModuleAutoLoaded = result.has_value() ? result.value() : false;
}

std::shared_ptr< AutoMountInfo >
automountDisable( bool disable )
{
    auto info = std::make_shared< AutoMountInfo >();
    QDBusConnection dbus = QDBusConnection::sessionBus();

    // KDE Plasma (Solid) handling
    querySolidAutoMount( dbus, *info );
    if ( info->hasSolid )
    {
        cDebug() << "Setting Solid automount to" << ( disable ? "disabled" : "enabled" );
        enableSolidAutoMount( dbus, !disable );
    }

    // TODO: other environments
    return info;
}


void
automountRestore( const std::shared_ptr< AutoMountInfo >& info )
{
    QDBusConnection dbus = QDBusConnection::sessionBus();

    // KDE Plasma (Solid) handling
    if ( info->hasSolid )
    {
        enableSolidAutoMount( dbus, info->wasSolidModuleAutoLoaded );
    }

    // TODO: other environments
}

}  // namespace Partition
}  // namespace CalamaresUtils
