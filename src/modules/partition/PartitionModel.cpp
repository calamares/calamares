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
#include <PartitionModel.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>

PartitionModel::PartitionModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

void
PartitionModel::init( Device* device )
{
    beginResetModel();
    m_device = device;
    m_partitionList.clear();
    if ( device )
    {
        fillPartitionList( m_device->partitionTable() );
    }
    endResetModel();
}

int
PartitionModel::rowCount( const QModelIndex& parent ) const
{
    return parent.isValid() ? 0 : m_partitionList.count();
}

QVariant
PartitionModel::data( const QModelIndex& index, int role ) const
{
    int row = index.row();
    if ( row < 0 || row >= m_partitionList.count() )
    {
        return QVariant();
    }

    Partition* partition = m_partitionList.at( row );

    switch ( role )
    {
    case Qt::DisplayRole:
        if ( partition->partitionPath().isEmpty() )
        {
            return tr( "Free Space" );
        }
        return partition->partitionPath() + " " + partition->fileSystem().name() + " " + partition->mountPoint();
    default:
        return QVariant();
    }
}

void
PartitionModel::fillPartitionList( PartitionNode* parent )
{
    for ( auto partition : parent->children() )
    {
        m_partitionList << partition;
        fillPartitionList( partition );
    }
}
