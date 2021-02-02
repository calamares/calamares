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
    bool wasSolidModuleAutoLoaded = false;
};

static inline QDBusMessage
kdedCall( const QString& method )
{
    return QDBusMessage::createMethodCall(
        QStringLiteral( "org.kde.kded5" ), QStringLiteral( "/kded" ), QStringLiteral( "org.kde.kded5" ), method );
}

// This code comes, roughly, from the KCM for removable devices.
static void
enableSolidAutoMount( QDBusConnection& dbus, bool enable )
{
    const auto moduleName = QVariant( QStringLiteral( "device_automounter" ) );

    // Stop module from auto-loading
    {
        auto msg = kdedCall( QStringLiteral( "setModuleAutoloading" ) );
        msg.setArguments( { moduleName, QVariant( enable ) } );
        dbus.call( msg, QDBus::NoBlock );
    }

    // Stop module
    {
        auto msg = kdedCall( enable ? QStringLiteral( "loadModule" ) : QStringLiteral( "unloadModule" ) );
        msg.setArguments( { moduleName } );
        dbus.call( msg, QDBus::NoBlock );
    }
}

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
    }
    info.wasSolidModuleAutoLoaded = result.has_value() ? result.value() : false;
}

std::shared_ptr< AutoMountInfo >
automountDisable( bool disable )
{
    auto u = std::make_shared< AutoMountInfo >();
    QDBusConnection dbus = QDBusConnection::sessionBus();
    querySolidAutoMount( dbus, *u );
    enableSolidAutoMount( dbus, !disable );
    return u;
}


void
automountRestore( const std::shared_ptr< AutoMountInfo >& t )
{
    QDBusConnection dbus = QDBusConnection::sessionBus();
    enableSolidAutoMount( dbus, t->wasSolidModuleAutoLoaded );
}

}  // namespace Partition
}  // namespace CalamaresUtils
