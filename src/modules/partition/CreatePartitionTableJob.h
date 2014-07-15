/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#ifndef CREATEPARTITIONTABLEJOB_H
#define CREATEPARTITIONTABLEJOB_H

#include <Job.h>

// CalaPM
#include <core/partitiontable.h>

class Device;

class CreatePartitionTableJob : public Calamares::Job
{
    Q_OBJECT
public:
    CreatePartitionTableJob( Device* device, PartitionTable::TableType type );
    QString prettyName() const override;
    Calamares::JobResult exec() override;

    void updatePreview();
    Device* device() const
    {
        return m_device;
    }

private:
    Device* m_device;
    PartitionTable::TableType m_type;
    PartitionTable* createTable();
};

#endif /* CREATEPARTITIONTABLEJOB_H */
