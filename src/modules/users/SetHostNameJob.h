/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Rohan Garg <rohan@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SETHOSTNAMEJOB_CPP_H
#define SETHOSTNAMEJOB_CPP_H

#include "Config.h"

#include "Job.h"

class SetHostNameJob : public Calamares::Job
{
    Q_OBJECT
public:
    SetHostNameJob( const QString& hostname, HostNameActions a );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    const QString m_hostname;
    const HostNameActions m_actions;
};

#endif  // SETHOSTNAMEJOB_CPP_H
