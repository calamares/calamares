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

/** @section Tracking Jobs
 *
 * The tracking jobs do the actual work of configuring tracking on the
 * target machine. Tracking jobs may have *styles*, variations depending
 * on the distro or environment of the target system. At the root of
 * each family of tracking jobs (installation, machine, user) there is
 * free function `addJob()` that takes the configuration
 * information from the relevant Config sub-object and optionally
 * adds the right job (subclass!) to the list of jobs.
 *
 * There are no job-classes defined here because you need to be using the
 * `addJob()` interface instead.
 */

void addJob( Calamares::JobList& list, InstallTrackingConfig* config );
void addJob( Calamares::JobList& list, MachineTrackingConfig* config );
void addJob( Calamares::JobList& list, UserTrackingConfig* config );

#endif
