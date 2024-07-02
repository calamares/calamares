/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "Branding.h"
#include "Settings.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QProcess>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

#if 0
    static const NamedEnumTable< M > table { { "never", M::Never },
                                             { "user-unchecked", M::UserDefaultUnchecked },
                                             { "unchecked", M::UserDefaultUnchecked },
                                             { "user-checked", M::UserDefaultChecked },
                                             { "checked", M::UserDefaultChecked },
                                             { "always", M::Always }

    };
#endif

Config::Config( QObject* parent )
    : QObject( parent )
{
}

void
Config::onInstallationFailed( const QString& message, const QString& details )
{
    const bool messageChange = message != m_failureMessage;
    const bool detailsChange = details != m_failureDetails;
    m_failureMessage = message;
    m_failureDetails = details;
    if ( messageChange )
    {
        emit failureMessageChanged( message );
    }
    if ( detailsChange )
    {
        emit failureDetailsChanged( message );
    }
    if ( ( messageChange || detailsChange ) )
    {
        emit failureChanged( hasFailed() );
    }
}

void
Config::doRestart()
{
}

void
Config::doNotify( bool hasFailed, bool sendAnyway )
{
    const char* const failName = hasFailed ? "failed" : "succeeded";

    if ( !sendAnyway )
    {
        cDebug() << "Notification not sent; completion:" << failName;
        return;
    }

    QDBusInterface notify(
        "org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications" );
    if ( notify.isValid() )
    {
        cDebug() << "Sending notification of completion:" << failName;

        QString title;
        QString message;
        if ( hasFailed )
        {
            title = Calamares::Settings::instance()->isSetupMode() ? tr( "Setup Failed", "@title" )
                                                                   : tr( "Installation Failed", "@title" );
            message = Calamares::Settings::instance()->isSetupMode()
                ? tr( "The setup of %1 did not complete successfully.", "@info" )
                : tr( "The installation of %1 did not complete successfully.", "@info" );
        }
        else
        {
            title = Calamares::Settings::instance()->isSetupMode() ? tr( "Setup Complete", "@title" )
                                                                   : tr( "Installation Complete", "@title" );
            message = Calamares::Settings::instance()->isSetupMode()
                ? tr( "The setup of %1 is complete.", "@info" )
                : tr( "The installation of %1 is complete.", "@info" );
        }

        const auto* branding = Calamares::Branding::instance();
        QDBusReply< uint > r = notify.call( "Notify",
                                            QString( "Calamares" ),
                                            QVariant( 0U ),
                                            QString( "calamares" ),
                                            title,
                                            message.arg( branding->versionedName() ),
                                            QStringList(),
                                            QVariantMap(),
                                            QVariant( 0 ) );
        if ( !r.isValid() )
        {
            cWarning() << "Could not call org.freedesktop.Notifications.Notify at end of installation." << r.error();
        }
    }
    else
    {
        cWarning() << "Could not get dbus interface for notifications at end of installation." << notify.lastError();
    }
}

using Choices = int;

static Choices loadLive(bool isSelected)
{
    return isSelected ? 1 : 0;
}

static Choices loadRestart(bool isSelected, const QString & /* command */ )
{
    return isSelected ? 1 : 0;
}

static Choices loadFromV3(const QVariantList & items, const QString & defaultChoice )
{
    return 0;
}

static Choices loadFromV2(const QString & restartNowMode, const QString & restartNowCommand)
{
    if (restartNowMode == QStringLiteral( "never"))
    {
        return loadLive(true);
    }

    // Empty if not specified, defaults to user-unchecked according to the suggested config
    if (restartNowMode == QStringLiteral("user-unchecked") || restartNowMode == QStringLiteral("unchecked") || restartNowMode.isEmpty())
    {
        Choices c = loadLive(true);
        c += loadRestart(false, restartNowCommand);
        return c;
    }

    if (restartNowMode == QStringLiteral("user-checked") || restartNowMode == QStringLiteral("checked"))
    {
        Choices c = loadLive(false);
        c += loadRestart(true, restartNowCommand);
        return c;
    }

    if (restartNowMode == QStringLiteral("always"))
    {
        return loadRestart(true, restartNowCommand);
    }

    cError() << "Unknown v2 restart mode" << restartNowMode << "using 'never'";
    return loadLive(true);
}

static Choices loadFromV1(bool restartNowEnabled, bool restartNowChecked, const QString & restartNowCommand)
{
    if (!restartNowEnabled)
    {
        return loadFromV2( QStringLiteral("never"), QString());
    }
    if (restartNowChecked)
    {
        return loadFromV2( QStringLiteral("user-checked"), restartNowCommand);
    }
    else
    {
        return loadFromV2( QStringLiteral("user-unchecked"), restartNowCommand);
    }
}


void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_notifyOnFinished = Calamares::getBool( configurationMap, "notifyOnFinished", false );

    const auto v1Enabled = QStringLiteral( "restartNowEnabled" );
    const auto v1Checked = QStringLiteral( "restartNowChecked" );

    const auto v2Mode = QStringLiteral("restartNowMode");
    const auto v2Command = QStringLiteral("restartNowCommand");

    if(configurationMap.contains( v1Enabled) || configurationMap.contains(v1Checked))
    {
        cWarning() << "Configuration uses v1 settings" << v1Enabled << "and" << v1Checked;
        loadFromV1(Calamares::getBool(configurationMap, v1Enabled, true), Calamares::getBool(configurationMap, v1Checked, false), Calamares::getString(configurationMap, v2Command));
    }
    else if(configurationMap.contains( v2Mode) || configurationMap.contains(v2Command))
    {
        cWarning() << "Configuration uses v2 settings" << v2Mode << "and" << v2Command;
        loadFromV2(Calamares::getString(configurationMap, v2Mode, QStringLiteral("user-unchecked")), Calamares::getString(configurationMap, v2Command));
    }
    else
    {
        loadFromV3(Calamares::getList(configurationMap, QStringLiteral("choices")), Calamares::getString(configurationMap, QStringLiteral("defaultChoice")));
    }
}
