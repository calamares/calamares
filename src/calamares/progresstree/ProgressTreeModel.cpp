/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "ProgressTreeModel.h"

#include "ViewStepItem.h"

#include "ViewManager.h"

ProgressTreeModel::ProgressTreeModel( QObject* parent )
    : QAbstractItemModel( parent )
    , m_rootItem( nullptr )
{
    setupModelData();
}


ProgressTreeModel::~ProgressTreeModel()
{
    delete m_rootItem;
}


Qt::ItemFlags
ProgressTreeModel::flags( const QModelIndex& index ) const
{
    if ( !index.isValid() )
    {
        return Qt::ItemFlags();
    }

    return Qt::ItemIsEnabled;
}


QModelIndex
ProgressTreeModel::index( int row, int column, const QModelIndex& parent ) const
{
    if ( !hasIndex( row, column, parent ) )
    {
        return QModelIndex();
    }

    ProgressTreeItem* parentItem;

    if ( !parent.isValid() )
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast< ProgressTreeItem* >( parent.internalPointer() );
    }

    ProgressTreeItem* childItem = parentItem->child( row );
    if ( childItem )
    {
        return createIndex( row, column, childItem );
    }
    else
    {
        return QModelIndex();
    }
}


QModelIndex
ProgressTreeModel::parent( const QModelIndex& index ) const
{
    if ( !index.isValid() )
    {
        return QModelIndex();
    }

    ProgressTreeItem* childItem = static_cast< ProgressTreeItem* >( index.internalPointer() );
    ProgressTreeItem* parentItem = childItem->parent();

    if ( parentItem == m_rootItem )
    {
        return QModelIndex();
    }

    return createIndex( parentItem->row(), 0, parentItem );
}


QVariant
ProgressTreeModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }

    ProgressTreeItem* item = static_cast< ProgressTreeItem* >( index.internalPointer() );

    return item->data( role );
}


QVariant
ProgressTreeModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    Q_UNUSED( section )
    Q_UNUSED( orientation )
    Q_UNUSED( role )

    return QVariant();
}


int
ProgressTreeModel::rowCount( const QModelIndex& parent ) const
{
    ProgressTreeItem* parentItem;
    if ( parent.column() > 0 )
    {
        return 0;
    }

    if ( !parent.isValid() )
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast< ProgressTreeItem* >( parent.internalPointer() );
    }

    return parentItem->childCount();
}


int
ProgressTreeModel::columnCount( const QModelIndex& parent ) const
{
    if ( parent.isValid() )
    {
        return static_cast< ProgressTreeItem* >( parent.internalPointer() )->columnCount();
    }
    else
    {
        return m_rootItem->columnCount();
    }
}


void
ProgressTreeModel::setupModelData()
{
    delete m_rootItem;

    m_rootItem = new ProgressTreeRoot();
    const Calamares::ViewManager* vm = Calamares::ViewManager::instance();

    const auto steps = vm->viewSteps();
    for ( const Calamares::ViewStep* step : steps )
    {
        m_rootItem->appendChild( new ViewStepItem( step, m_rootItem ) );
    }
}
