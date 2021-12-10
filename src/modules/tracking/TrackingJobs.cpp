/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "TrackingJobs.h"

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "network/Manager.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <KMacroExpander>

#include <QCoreApplication>

#include <chrono>


// Namespace keeps all the actual jobs anonymous, the
// public API is the addJob() functions below the namespace.
namespace
{

/** @brief Install-tracking job (gets a URL)
 *
 * The install-tracking job (there is only one kind) does a GET
 * on a configured URL with some additional information about
 * the machine (if configured into the URL).
 *
 * No persistent tracking is done.
 */
class TrackingInstallJob : public Calamares::Job
{
public:
    TrackingInstallJob( const QString& url );
    ~TrackingInstallJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    const QString m_url;
};

/** @brief Tracking machines, update-manager style
 *
 * The machine has a machine-id, and this is sed(1)'ed into the
 * update-manager configuration, to report the machine-id back
 * to distro servers.
 */
class TrackingMachineUpdateManagerJob : public Calamares::Job
{
public:
    ~TrackingMachineUpdateManagerJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
};

/** @brief Turn on KUserFeedback in target system
 *
 * This writes suitable files for turning on KUserFeedback for the
 * normal user configured in Calamares. The feedback can be reconfigured
 * by the user through Plasma's user-feedback dialog.
 */
class TrackingKUserFeedbackJob : public Calamares::Job
{
public:
    TrackingKUserFeedbackJob( const QString& username, const QStringList& areas );
    ~TrackingKUserFeedbackJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QString m_username;
    QStringList m_areas;
};

TrackingInstallJob::TrackingInstallJob( const QString& url )
    : m_url( url )
{
}

TrackingInstallJob::~TrackingInstallJob() {}

QString
TrackingInstallJob::prettyName() const
{
    return QCoreApplication::translate( "TrackingInstallJob", "Installation feedback" );
}

QString
TrackingInstallJob::prettyStatusMessage() const
{
    return QCoreApplication::translate( "TrackingInstallJob", "Sending installation feedback." );
}

Calamares::JobResult
TrackingInstallJob::exec()
{
    using CalamaresUtils::Network::Manager;
    using CalamaresUtils::Network::RequestOptions;
    using CalamaresUtils::Network::RequestStatus;

    auto result = Manager::instance().synchronousPing(
        QUrl( m_url ),
        RequestOptions( RequestOptions::FollowRedirect | RequestOptions::FakeUserAgent,
                        RequestOptions::milliseconds( 5000 ) ) );
    if ( result.status == RequestStatus::Timeout )
    {
        cWarning() << "install-tracking request timed out.";
        return Calamares::JobResult::error(
            QCoreApplication::translate( "TrackingInstallJob", "Internal error in install-tracking." ),
            QCoreApplication::translate( "TrackingInstallJob", "HTTP request timed out." ) );
    }
    return Calamares::JobResult::ok();
}

TrackingMachineUpdateManagerJob::~TrackingMachineUpdateManagerJob() {}

QString
TrackingMachineUpdateManagerJob::prettyName() const
{
    return QCoreApplication::translate( "TrackingMachineUpdateManagerJob", "Machine feedback" );
}

QString
TrackingMachineUpdateManagerJob::prettyStatusMessage() const
{
    return QCoreApplication::translate( "TrackingMachineUpdateManagerJob", "Configuring machine feedback." );
}

Calamares::JobResult
TrackingMachineUpdateManagerJob::exec()
{
    static const auto script = QStringLiteral(
        "sed -i '/^URI/s,${MACHINE_ID},'`cat /etc/machine-id`',' /etc/update-manager/meta-release || true" );

    auto res = CalamaresUtils::System::instance()->runCommand( CalamaresUtils::System::RunLocation::RunInTarget,
                                                               QStringList { QStringLiteral( "/bin/sh" ) },
                                                               QString(),  // Working dir
                                                               script,  // standard input
                                                               std::chrono::seconds( 1 ) );
    int r = res.first;

    if ( r == 0 )
    {
        return Calamares::JobResult::ok();
    }
    else if ( r > 0 )
    {
        return Calamares::JobResult::error(
            QCoreApplication::translate( "TrackingMachineUpdateManagerJob",
                                         "Error in machine feedback configuration." ),
            QCoreApplication::translate( "TrackingMachineUpdateManagerJob",
                                         "Could not configure machine feedback correctly, script error %1." )
                .arg( r ) );
    }
    else
    {
        return Calamares::JobResult::error(
            QCoreApplication::translate( "TrackingMachineUpdateManagerJob",
                                         "Error in machine feedback configuration." ),
            QCoreApplication::translate( "TrackingMachineUpdateManagerJob",
                                         "Could not configure machine feedback correctly, Calamares error %1." )
                .arg( r ) );
    }
}

TrackingKUserFeedbackJob::TrackingKUserFeedbackJob( const QString& username, const QStringList& areas )
    : m_username( username )
    , m_areas( areas )
{
}

TrackingKUserFeedbackJob::~TrackingKUserFeedbackJob() {}

QString
TrackingKUserFeedbackJob::prettyName() const
{
    return QCoreApplication::translate( "TrackingKUserFeedbackJob", "KDE user feedback" );
}

QString
TrackingKUserFeedbackJob::prettyStatusMessage() const
{
    return QCoreApplication::translate( "TrackingKUserFeedbackJob", "Configuring KDE user feedback." );
}

Calamares::JobResult
TrackingKUserFeedbackJob::exec()
{
    // This is the contents of a config file to turn on some kind
    // of KUserFeedback tracking; the level (16) is chosen for minimal
    // but not zero tracking.
    static const char config[] = R"x([Global]
FeedbackLevel=16
)x";

    for ( const QString& area : m_areas )
    {
        QString path = QStringLiteral( "/home/%1/.config/%2" ).arg( m_username, area );
        cDebug() << "Configuring KUserFeedback" << path;

        int r = CalamaresUtils::System::instance()->createTargetFile( path, config );
        if ( r > 0 )
        {
            return Calamares::JobResult::error(
                QCoreApplication::translate( "TrackingKUserFeedbackJob", "Error in KDE user feedback configuration." ),
                QCoreApplication::translate( "TrackingKUserFeedbackJob",
                                             "Could not configure KDE user feedback correctly, script error %1." )
                    .arg( r ) );
        }
        else if ( r < 0 )
        {
            return Calamares::JobResult::error(
                QCoreApplication::translate( "TrackingKUserFeedbackJob", "Error in KDE user feedback configuration." ),
                QCoreApplication::translate( "TrackingKUserFeedbackJob",
                                             "Could not configure KDE user feedback correctly, Calamares error %1." )
                    .arg( r ) );
        }
    }

    return Calamares::JobResult::ok();
}

}  // namespace

void
addJob( Calamares::JobList& list, InstallTrackingConfig* config )
{
    if ( config->isEnabled() )
    {
        const auto* s = CalamaresUtils::System::instance();
        QHash< QString, QString > map { std::initializer_list< std::pair< QString, QString > > {
            { QStringLiteral( "CPU" ), s->getCpuDescription() },
            { QStringLiteral( "MEMORY" ), QString::number( s->getTotalMemoryB().first ) },
            { QStringLiteral( "DISK" ), QString::number( s->getTotalDiskB() ) } } };
        QString installUrl = KMacroExpander::expandMacros( config->installTrackingUrl(), map );

        cDebug() << Logger::SubEntry << "install-tracking URL" << installUrl;

        list.append( Calamares::job_ptr( new TrackingInstallJob( installUrl ) ) );
    }
}

void
addJob( Calamares::JobList& list, MachineTrackingConfig* config )
{
    if ( config->isEnabled() )
    {
        const auto style = config->machineTrackingStyle();
        if ( style == "updatemanager" )
        {
            list.append( Calamares::job_ptr( new TrackingMachineUpdateManagerJob() ) );
        }
        else
        {
            cWarning() << "Unsupported machine tracking style" << style;
        }
    }
}


void
addJob( Calamares::JobList& list, UserTrackingConfig* config )
{
    if ( config->isEnabled() )
    {
        const auto* gs = Calamares::JobQueue::instance()->globalStorage();
        static const auto key = QStringLiteral( "username" );
        QString username = ( gs && gs->contains( key ) ) ? gs->value( key ).toString() : QString();

        if ( username.isEmpty() )
        {
            cWarning() << "No username is set in GlobalStorage, skipping user-tracking.";
            return;
        }

        const auto style = config->userTrackingStyle();
        if ( style == "kuserfeedback" )
        {
            list.append( Calamares::job_ptr( new TrackingKUserFeedbackJob( username, config->userTrackingAreas() ) ) );
        }
        else
        {
            cWarning() << "Unsupported user tracking style" << style;
        }
    }
}
