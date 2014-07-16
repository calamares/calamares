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

#include <PartitionInfo.h>
#include <PMUtils.h>
#include <utils/Logger.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>

// KF5
#include <KFormat>

PartitionInfoProvider::~PartitionInfoProvider()
{}

PartitionModel::PartitionModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

void
PartitionModel::init( Device* device, PartitionInfoProvider* infoProvider )
{
    m_device = device;
    m_infoProvider = infoProvider;
    reload();
}

void
PartitionModel::reload()
{
    beginResetModel();
    m_partitionList.clear();
    if ( m_device )
        fillPartitionList( m_device->partitionTable() );
    endResetModel();
}

int
PartitionModel::columnCount( const QModelIndex& parent ) const
{
    return LastColumn;
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
        return QVariant();

    Partition* partition = m_partitionList.at( row );

    switch ( role )
    {
    case Qt::DisplayRole:
    {
        int col = index.column();
        if ( col == NameColumn )
        {
            // FIXME: Turn model into a tree model, will make implementing the
            // preview easier
            QString prefix = partition->roles().has( PartitionRole::Logical )
                             ? QStringLiteral( "    " ) : QStringLiteral();
            if ( PMUtils::isPartitionFreeSpace( partition ) )
                return prefix + tr( "Free Space" );
            else
            {
                return prefix + ( PMUtils::isPartitionNew( partition )
                                  ? tr( "New partition" )
                                  : partition->partitionPath() );
            }
        }
        if ( col == FileSystemColumn )
            return partition->fileSystem().name();
        if ( col == MountPointColumn )
        {
            PartitionInfo* info = m_infoProvider->infoForPartition( partition );
            return info ? info->mountPoint : QString();
        }
        if ( col == SizeColumn )
        {
            qint64 size = ( partition->lastSector() - partition->firstSector() + 1 ) * m_device->logicalSectorSize();
            return KFormat().formatByteSize( size );
        }
        cDebug() << "Unknown column" << col;
        return QVariant();
    }
    case IsNewPartitionRole:
        return PMUtils::isPartitionNew( partition );
    default:
        return QVariant();
    }
}

void
PartitionModel::fillPartitionList( PartitionNode* parent )
{
    if ( !parent )
        return;
    for ( auto partition : parent->children() )
    {
        m_partitionList << partition;
        fillPartitionList( partition );
    }
}

Partition*
PartitionModel::partitionForIndex( const QModelIndex& index ) const
{
    int row = index.row();
    if ( row < 0 || row >= m_partitionList.count() )
        return nullptr;
    return m_partitionList.at( row );
}

PartitionInfo*
PartitionModel::partitionInfoForIndex( const QModelIndex& index ) const
{
    Partition* partition = partitionForIndex( index );
    if (!partition )
        return nullptr;
    return m_infoProvider->infoForPartition( partition );
}
