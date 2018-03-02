/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CLEARTEMPMOUNTSJOB_H
#define CLEARTEMPMOUNTSJOB_H

#include <Job.h>

class Device;

/**
 * This job tries to free all temporary mounts used by Calamares, so partitioning
 * operations can proceed.
 */
class ClearTempMountsJob : public Calamares::Job
{
    Q_OBJECT
public:
    explicit ClearTempMountsJob();
    QString prettyName() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;
};

#endif // CLEARTEMPMOUNTSJOB_H
