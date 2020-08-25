/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PARTITIONJOB_H
#define PARTITIONJOB_H

#include "Job.h"
#include "partition/KPMManager.h"

class Partition;

/**
 * Base class for jobs which affect a partition and which use KPMCore.
 */
class PartitionJob : public Calamares::Job
{
    Q_OBJECT
public:
    PartitionJob( Partition* partition );

    Partition* partition() const { return m_partition; }

public slots:
    /** @brief Translate from KPMCore to Calamares progress.
     *
     * KPMCore presents progress as an integer percent from 0 .. 100,
     * while Calamares uses a qreal from 0 .. 1.00 .
     */
    void iprogress( int percent );

protected:
    CalamaresUtils::Partition::KPMManager m_kpmcore;
    Partition* m_partition;
};

#endif /* PARTITIONJOB_H */
