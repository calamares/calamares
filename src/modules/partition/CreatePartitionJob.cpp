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

#include <CreatePartitionJob.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>

CreatePartitionJob::CreatePartitionJob( Device* device, Partition* freePartition, FileSystem* fs )
    : m_device( device )
    , m_freePartition( freePartition )
    , m_fs( fs )
{
}

QString
CreatePartitionJob::prettyName()
{
    return tr( "Create partition" ); // FIXME
}

void
CreatePartitionJob::exec()
{
}

void
CreatePartitionJob::createPreview()
{
    PartitionNode* parent = m_freePartition->parent();
    Partition* partition = new Partition(
        parent,
        *m_device,
        PartitionRole( PartitionRole::Primary ), // FIXME: Support extended partitions
        m_fs, m_fs->firstSector(), m_fs->lastSector(),
        QString() /* path */
    );

    m_device->partitionTable()->removeUnallocated();
    parent->insert( partition );
    m_device->partitionTable()->updateUnallocated( *m_device );
}
