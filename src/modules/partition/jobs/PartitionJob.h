/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#ifndef PARTITIONJOB_H
#define PARTITIONJOB_H

#include <Job.h>

class Partition;

/**
 * Base class for jobs which affect a partition.
 */
class PartitionJob : public Calamares::Job
{
    Q_OBJECT
public:
    PartitionJob( Partition* partition );

    Partition* partition() const
    {
        return m_partition;
    }

public slots:
    /** @brief Translate from KPMCore to Calamares progress.
     *
     * KPMCore presents progress as an integer percent from 0 .. 100,
     * while Calamares uses a qreal from 0 .. 1.00 .
     */
    void iprogress( int percent );

protected:
    Partition* m_partition;
};

#endif /* PARTITIONJOB_H */
