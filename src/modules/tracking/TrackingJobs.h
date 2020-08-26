/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef TRACKING_TRACKINGJOBS_H
#define TRACKING_TRACKINGJOBS_H

#include "Job.h"

class InstallTrackingConfig;
class MachineTrackingConfig;
class UserTrackingConfig;

class QSemaphore;

/** @section Tracking Jobs
 *
 * The tracking jobs do the actual work of configuring tracking on the
 * target machine. Tracking jobs may have *styles*, variations depending
 * on the distro or environment of the target system. At the root of
 * each family of tracking jobs (installation, machine, user) there is
 * a class with static method `addJob()` that takes the configuration
 * information from the relevant Config sub-object and optionally
 * adds the right job (subclass!) to the list of jobs.
 */

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
    Q_OBJECT
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
    Q_OBJECT
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

void addJob( Calamares::JobList& list, InstallTrackingConfig* config );
void addJob( Calamares::JobList& list, MachineTrackingConfig* config );
void addJob( Calamares::JobList& list, UserTrackingConfig* config );

#endif
