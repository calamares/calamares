/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Based on the SetPartFlagsJob class from KDE Partition Manager,
 *   SPDX-FileCopyrightText: 2008 2010, Volker Lanz <vl@fidra.de>
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SETPARTITIONFLAGSJOB_H
#define SETPARTITIONFLAGSJOB_H

#include "PartitionJob.h"

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

#endif  // SETPARTITIONFLAGSJOB_H
