/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef CALAMARES_PROCESSJOB_H
#define CALAMARES_PROCESSJOB_H

#include "Job.h"

#include <chrono>

namespace Calamares
{

class ProcessJob : public Job
{
    Q_OBJECT
public:
    explicit ProcessJob( const QString& command,
                         const QString& workingPath,
                         bool runInChroot = false,
                         std::chrono::seconds secondsTimeout = std::chrono::seconds( 30 ),
                         QObject* parent = nullptr );
    virtual ~ProcessJob() override;

    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    JobResult exec() override;

private:
    QString m_command;
    QString m_workingPath;
    bool m_runInChroot;
    std::chrono::seconds m_timeoutSec;
};

}  // namespace Calamares

#endif  // CALAMARES_PROCESSJOB_H
