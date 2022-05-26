/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "FlatPartitionModel.h"
#include "core/PartitionModel.h"

PartitionListModel::PartitionListModel( PartitionModel* model, QObject* parent )
    : QAbstractListModel( parent )
    , m_model( model )
{
    connect( m_model, &PartitionModel::rowsInserted, this, &PartitionListModel::rowsInserted );
    connect( m_model, &PartitionModel::rowsRemoved, this, &PartitionListModel::rowsRemoved );
    connect( m_model, &PartitionModel::dataChanged, this, &PartitionListModel::dataChanged );
}

int PartitionListModel::rowCount( const QModelIndex& parent ) const
{
    return m_model->rowCount( parent );
}

QHash< int, QByteArray > PartitionListModel::roleNames() const
{
    QHash< int, QByteArray > roles = m_model->roleNames();
    roles.insert( Qt::UserRole + 1, "size" );
    roles.insert( Qt::UserRole + 2, "partitionData" );

    return roles;
}

QVariant PartitionListModel::data( const QModelIndex& index, int role ) const
{
    // Convert the treeview index to a flat index
    QModelIndex flatIndex = m_model->index( index.row(), 0, index.parent() );
    QVariant data = m_model->data( flatIndex, role );
    if ( role == PartitionModel::SizeRole )
    {
        data = m_model->data( flatIndex, PartitionModel::SizeRole );
    }
    if ( role == Qt::UserRole + 2 )
    {
        QVariantMap partitionData;
        partitionData.insert( "IsFreeSpaceRole", m_model->data( flatIndex, PartitionModel::IsFreeSpaceRole ) );
        partitionData.insert( "IsPartitionNewRole", m_model->data( flatIndex, PartitionModel::IsPartitionNewRole ) );
        partitionData.insert( "FileSystemLabelRole", m_model->data( flatIndex, PartitionModel::FileSystemLabelRole ) );
        partitionData.insert( "FileSystemTypeRole", m_model->data( flatIndex, PartitionModel::FileSystemTypeRole ) );
        partitionData.insert( "PartitionPathRole", m_model->data( flatIndex, PartitionModel::PartitionPathRole ) );
        partitionData.insert( "PartitionPtrRole", m_model->data( flatIndex, PartitionModel::PartitionPtrRole ) );
        partitionData.insert( "OsproberNameRole", m_model->data( flatIndex, PartitionModel::OsproberNameRole ) );
        partitionData.insert( "OsproberPathRole", m_model->data( flatIndex, PartitionModel::OsproberPathRole ) );
        partitionData.insert( "OsproberCanBeResizedRole", m_model->data( flatIndex, PartitionModel::OsproberCanBeResizedRole ) );
        partitionData.insert( "OsproberRawLineRole", m_model->data( flatIndex, PartitionModel::OsproberRawLineRole ) );
        partitionData.insert( "OsproberHomePartitionPathRole", m_model->data( flatIndex, PartitionModel::OsproberHomePartitionPathRole ) );
        data.setValue( partitionData );
    }
    return data;
}

QVariantMap PartitionListModel::get( int row ) const
{
    return data( index( row, 0 ), Qt::DisplayRole ).toList().first().toMap();
}

QModelIndex PartitionListModel::mapToSource( const QModelIndex& index ) const
{
    return m_model->index( index.row(), 0, index.parent() );
}
