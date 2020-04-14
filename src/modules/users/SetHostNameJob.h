/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Rohan Garg <rohan@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef SETHOSTNAMEJOB_CPP_H
#define SETHOSTNAMEJOB_CPP_H

#include "Job.h"

class SetHostNameJob : public Calamares::Job
{
    Q_OBJECT
public:
    enum Action
    {
        None = 0x0,
        EtcHostname = 0x1,  // Write to /etc/hostname directly
        SystemdHostname = 0x2,  // Set via hostnamed(1)
        WriteEtcHosts = 0x4  // Write /etc/hosts (127.0.1.1 is this host)
    };
    Q_DECLARE_FLAGS( Actions, Action )


    SetHostNameJob( const QString& hostname, Actions a );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

private:
    const QString m_hostname;
    const Actions m_actions;
};

Q_DECLARE_OPERATORS_FOR_FLAGS( SetHostNameJob::Actions )

#endif  // SETHOSTNAMEJOB_CPP_H
