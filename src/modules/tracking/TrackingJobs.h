/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    static void addJob( Calamares::JobList& list, InstallTrackingConfig* config );

private:
    const QString m_url;
};

/** @brief Base class for machine-tracking jobs
 *
 * Machine-tracking configuraiton depends on the distro / style of machine
 * being tracked, so it has subclasses to switch on the relevant kind
 * of tracking. A machine is tracked persistently.
 */
class TrackingMachineJob : public Calamares::Job
{
public:
    static void addJob( Calamares::JobList& list, MachineTrackingConfig* config );
};

/** @brief Tracking machines, update-manager style
 *
 * The machine has a machine-id, and this is sed(1)'ed into the
 * update-manager configuration, to report the machine-id back
 * to distro servers.
 */
class TrackingMachineUpdateManagerJob : public TrackingMachineJob
{
    Q_OBJECT
public:
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
};

/** @brief Base class for user-tracking jobs
 *
 * User-tracking configuration depends on the distro / style of user
 * tracking being implemented, so there are subclasses to switch on the
 * relevant kind of tracking. Users are tracked persistently (the user
 * can of course configure the tracking again once the system is restarted).
 */
class TrackingUserJob : public Calamares::Job
{
public:
    static void addJob( Calamares::JobList& list, UserTrackingConfig* config );
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

    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    QString m_username;
    QStringList m_areas;
};

#endif
