/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "FinishedViewStep.h"
#include "FinishedPage.h"

#include "Branding.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

#include <QVariantMap>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

static const NamedEnumTable< FinishedViewStep::RestartMode >&
modeNames()
{
    using Mode = FinishedViewStep::RestartMode;

    static const NamedEnumTable< Mode > names { { QStringLiteral( "never" ), Mode::Never },
                                                { QStringLiteral( "user-unchecked" ), Mode::UserUnchecked },
                                                { QStringLiteral( "user-checked" ), Mode::UserChecked },
                                                { QStringLiteral( "always" ), Mode::Always } };

    return names;
}

FinishedViewStep::FinishedViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new FinishedPage() )
    , installFailed( false )
    , m_notifyOnFinished( false )
{
    auto jq = Calamares::JobQueue::instance();
    connect( jq, &Calamares::JobQueue::failed, m_widget, &FinishedPage::onInstallationFailed );
    connect( jq, &Calamares::JobQueue::failed, this, &FinishedViewStep::onInstallationFailed );

    emit nextStatusChanged( true );
}


FinishedViewStep::~FinishedViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
FinishedViewStep::prettyName() const
{
    return tr( "Finish" );
}


QWidget*
FinishedViewStep::widget()
{
    return m_widget;
}


bool
FinishedViewStep::isNextEnabled() const
{
    return false;
}


bool
FinishedViewStep::isBackEnabled() const
{
    return false;
}


bool
FinishedViewStep::isAtBeginning() const
{
    return true;
}


bool
FinishedViewStep::isAtEnd() const
{
    return true;
}

void
FinishedViewStep::sendNotification()
{
    // If the installation failed, don't send notification popup;
    // there's a (modal) dialog popped up with the failure notice.
    if ( installFailed )
    {
        return;
    }

    QDBusInterface notify(
        "org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications" );
    if ( notify.isValid() )
    {
        const auto* branding = Calamares::Branding::instance();
        QDBusReply< uint > r = notify.call(
            "Notify",
            QString( "Calamares" ),
            QVariant( 0U ),
            QString( "calamares" ),
            Calamares::Settings::instance()->isSetupMode() ? tr( "Setup Complete" ) : tr( "Installation Complete" ),
            Calamares::Settings::instance()->isSetupMode()
                ? tr( "The setup of %1 is complete." ).arg( branding->versionedName() )
                : tr( "The installation of %1 is complete." ).arg( branding->versionedName() ),
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
FinishedViewStep::onActivate()
{
    m_widget->setUpRestart();

    if ( m_notifyOnFinished )
    {
        sendNotification();
    }
}


Calamares::JobList
FinishedViewStep::jobs() const
{
    return Calamares::JobList();
}

void
FinishedViewStep::onInstallationFailed( const QString& message, const QString& details )
{
    Q_UNUSED( message )
    Q_UNUSED( details )
    installFailed = true;
}

void
FinishedViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    RestartMode mode = RestartMode::Never;

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
            mode = restartNowChecked ? RestartMode::UserChecked : RestartMode::UserUnchecked;
        }
    }
    else
    {
        bool ok = false;
        mode = modeNames().find( restartMode, ok );
        if ( !ok )
        {
            cWarning() << "Configuring the finished module with bad restartNowMode" << restartMode;
        }
    }

    m_widget->setRestart( mode );

    if ( mode != RestartMode::Never )
    {
        QString restartNowCommand = CalamaresUtils::getString( configurationMap, "restartNowCommand" );
        if ( restartNowCommand.isEmpty() )
        {
            restartNowCommand = QStringLiteral( "shutdown -r now" );
        }
        m_widget->setRestartNowCommand( restartNowCommand );
    }

    m_notifyOnFinished = CalamaresUtils::getBool( configurationMap, "notifyOnFinished", false );
}

QString
FinishedViewStep::modeName( FinishedViewStep::RestartMode m )
{
    bool ok = false;
    return modeNames().find( m, ok );  // May be QString()
}


CALAMARES_PLUGIN_FACTORY_DEFINITION( FinishedViewStepFactory, registerPlugin< FinishedViewStep >(); )
