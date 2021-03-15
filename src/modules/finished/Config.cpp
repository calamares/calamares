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

const NamedEnumTable< Config::RestartMode >&
restartModes()
{
    using M = Config::RestartMode;
    static const NamedEnumTable< M > table { { "never", M::Never },
                                             { "user-unchecked", M::UserDefaultUnchecked },
                                             { "unchecked", M::UserDefaultUnchecked },
                                             { "user-checked", M::UserDefaultChecked },
                                             { "checked", M::UserDefaultChecked },
                                             { "always", M::Always }

    };
    return table;
}


Config::Config( QObject* parent )
    : QObject( parent )
{
}

void
Config::setRestartNowMode( Config::RestartMode m )
{
    // Can only go "down" in state (Always > UserDefaultChecked > .. > Never)
    if ( m > m_restartNowMode )
    {
        return;
    }

    // If changing to an unconditional mode, also set other flag
    if ( m == RestartMode::Always || m == RestartMode::Never )
    {
        setRestartNowWanted( m == RestartMode::Always );
    }

    if ( m != m_restartNowMode )
    {
        m_restartNowMode = m;
        emit restartModeChanged( m );
    }
}

void
Config::setRestartNowWanted( bool w )
{
    // Follow the mode which may affect @p w
    if ( m_restartNowMode == RestartMode::Always )
    {
        w = true;
    }
    if ( m_restartNowMode == RestartMode::Never )
    {
        w = false;
    }

    if ( w != m_userWantsRestart )
    {
        m_userWantsRestart = w;
        emit restartNowWantedChanged( w );
    }
}

void
Config::onInstallationFailed( const QString& message, const QString& details )
{
    const bool msgChange = message != m_failureMessage;
    const bool detChange = details != m_failureDetails;
    m_failureMessage = message;
    m_failureDetails = details;
    if ( msgChange )
    {
        emit failureMessageChanged( message );
    }
    if ( detChange )
    {
        emit failureDetailsChanged( message );
    }
    if ( ( msgChange || detChange ) )
    {
        emit failureChanged( hasFailed() );
        if ( hasFailed() )
        {
            setRestartNowMode( Config::RestartMode::Never );
        }
    }
}


void
Config::doRestart( bool restartAnyway )
{
    cDebug() << "mode=" << restartModes().find( restartNowMode() ) << " user wants restart?" << restartNowWanted()
             << "force restart?" << restartAnyway;
    if ( restartNowMode() != RestartMode::Never && restartAnyway )
    {
        cDebug() << Logger::SubEntry << "Running restart command" << m_restartNowCommand;
        QProcess::execute( "/bin/sh", { "-c", m_restartNowCommand } );
    }
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
            title = Calamares::Settings::instance()->isSetupMode() ? tr( "Setup Failed" ) : tr( "Installation Failed" );
            message = Calamares::Settings::instance()->isSetupMode()
                ? tr( "The setup of %1 did not complete successfully." )
                : tr( "The installation of %1 did not complete successfully." );
        }
        else
        {
            title = Calamares::Settings::instance()->isSetupMode() ? tr( "Setup Complete" )
                                                                   : tr( "Installation Complete" );
            message = Calamares::Settings::instance()->isSetupMode() ? tr( "The setup of %1 is complete." )
                                                                     : tr( "The installation of %1 is complete." );
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


void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    RestartMode mode = RestartMode::Never;

    //TODO:3.3 remove deprecated restart settings
    QString restartMode = CalamaresUtils::getString( configurationMap, "restartNowMode" );
    if ( restartMode.isEmpty() )
    {
        if ( configurationMap.contains( "restartNowEnabled" ) )
        {
            cWarning() << "Configuring the finished module with deprecated restartNowEnabled settings";
        }

        bool restartNowEnabled = CalamaresUtils::getBool( configurationMap, "restartNowEnabled", false );
        bool restartNowChecked = CalamaresUtils::getBool( configurationMap, "restartNowChecked", false );

        if ( !restartNowEnabled )
        {
            mode = RestartMode::Never;
        }
        else
        {
            mode = restartNowChecked ? RestartMode::UserDefaultChecked : RestartMode::UserDefaultUnchecked;
        }
    }
    else
    {
        bool ok = false;
        mode = restartModes().find( restartMode, ok );
        if ( !ok )
        {
            cWarning() << "Configuring the finished module with bad restartNowMode" << restartMode;
        }
    }

    m_restartNowMode = mode;
    m_userWantsRestart = ( mode == RestartMode::Always || mode == RestartMode::UserDefaultChecked );
    emit restartModeChanged( m_restartNowMode );
    emit restartNowWantedChanged( m_userWantsRestart );

    if ( mode != RestartMode::Never )
    {
        QString restartNowCommand = CalamaresUtils::getString( configurationMap, "restartNowCommand" );
        if ( restartNowCommand.isEmpty() )
        {
            restartNowCommand = QStringLiteral( "shutdown -r now" );
        }
        m_restartNowCommand = restartNowCommand;
    }

    m_notifyOnFinished = CalamaresUtils::getBool( configurationMap, "notifyOnFinished", false );
}
