/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/**@file Various small jobs
 *
 * This file collects miscellaneous jobs that need to be run to prepare
 * the system for the user-creation job.
 */

#ifndef USERS_MISCJOBS_H
#define USERS_MISCJOBS_H

#include "Config.h"

#include "Job.h"

class SetupSudoJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetupSudoJob( const QString& group, Config::SudoStyle style );
    QString prettyName() const override;
    Calamares::JobResult exec() override;

public:
    QString m_sudoGroup;
    Config::SudoStyle m_sudoStyle;
};

class SetupGroupsJob : public Calamares::Job
{
    Q_OBJECT

public:
    SetupGroupsJob( const Config* config );
    QString prettyName() const override;
    Calamares::JobResult exec() override;

public:
    const Config* m_config;
};

#endif
