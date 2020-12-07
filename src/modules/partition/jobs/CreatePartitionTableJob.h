/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CREATEPARTITIONTABLEJOB_H
#define CREATEPARTITIONTABLEJOB_H

#include "Job.h"
#include "partition/KPMManager.h"

// KPMcore
#include <kpmcore/core/partitiontable.h>

class Device;

/**
 * Creates a partition table on a device. It supports MBR and GPT partition
 * tables.
 *
 * This wipes all the data from the device.
 */
class CreatePartitionTableJob : public Calamares::Job
{
    Q_OBJECT
public:
    CreatePartitionTableJob( Device* device, PartitionTable::TableType type );
    QString prettyName() const override;
    QString prettyDescription() const override;
    QString prettyStatusMessage() const override;
    Calamares::JobResult exec() override;

    void updatePreview();
    Device* device() const { return m_device; }

private:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    Device* m_device;
    PartitionTable::TableType m_type;
    PartitionTable* createTable();
};

#endif /* CREATEPARTITIONTABLEJOB_H */
