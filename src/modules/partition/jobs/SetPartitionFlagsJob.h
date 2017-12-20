/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *
 *   Based on the SetPartFlagsJob class from KDE Partition Manager,
 *   Copyright 2008, 2010, Volker Lanz <vl@fidra.de>
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

#ifndef SETPARTITIONFLAGSJOB_H
#define SETPARTITIONFLAGSJOB_H

#include <jobs/PartitionJob.h>

#include <kpmcore/core/partitiontable.h>

class Device;
class Partition;

/**
 * This job changes the flags on an existing partition.
 */
class SetPartFlagsJob : public PartitionJob
{
    Q_OBJECT
public:
    SetPartFlagsJob( Device* device, Partition* partition, PartitionTable::Flags flags );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    Device* device() const;

private:
    Device* m_device;
    PartitionTable::Flags m_flags;
};

#endif // SETPARTITIONFLAGSJOB_H
