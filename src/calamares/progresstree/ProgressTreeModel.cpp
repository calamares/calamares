/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "progresstree/ViewStepItem.h"
#include "ViewManager.h"

ProgressTreeModel::ProgressTreeModel( QObject* parent )
    : QAbstractItemModel( parent )
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
        return 0;

    return Qt::ItemIsEnabled;
}


QModelIndex
ProgressTreeModel::index( int row, int column, const QModelIndex& parent ) const
{
    if ( !hasIndex( row, column, parent ) )
        return QModelIndex();

    ProgressTreeItem* parentItem;

    if ( !parent.isValid() )
        parentItem = m_rootItem;
    else
        parentItem = static_cast< ProgressTreeItem* >( parent.internalPointer() );

    ProgressTreeItem* childItem = parentItem->child( row );
    if ( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}


QModelIndex
ProgressTreeModel::parent( const QModelIndex& index ) const
{
    if ( !index.isValid() )
        return QModelIndex();

    ProgressTreeItem* childItem = static_cast< ProgressTreeItem* >( index.internalPointer() );
    ProgressTreeItem* parentItem = childItem->parent();

    if ( parentItem == m_rootItem )
        return QModelIndex();

    return createIndex( parentItem->row(), 0, parentItem );
}


QVariant
ProgressTreeModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    ProgressTreeItem* item = static_cast< ProgressTreeItem* >( index.internalPointer() );

    return item->data( role );
}


QVariant
ProgressTreeModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    Q_UNUSED( section );
    Q_UNUSED( orientation );
    Q_UNUSED( role );

    return QVariant();
}


int
ProgressTreeModel::rowCount( const QModelIndex& parent ) const
{
    ProgressTreeItem* parentItem;
    if ( parent.column() > 0 )
        return 0;

    if ( !parent.isValid() )
        parentItem = m_rootItem;
    else
        parentItem = static_cast< ProgressTreeItem* >( parent.internalPointer() );

    return parentItem->childCount();
}


int
ProgressTreeModel::columnCount( const QModelIndex& parent ) const
{
    if ( parent.isValid() )
        return static_cast< ProgressTreeItem* >( parent.internalPointer() )->columnCount();
    else
        return m_rootItem->columnCount();
}


void
ProgressTreeModel::setupModelData()
{
    m_rootItem = new ProgressTreeRoot();
    const Calamares::ViewManager* vm = Calamares::ViewManager::instance();

    const auto steps = vm->viewSteps();
    for ( const Calamares::ViewStep* step : steps )
    {
        m_rootItem->appendChild( new ViewStepItem( step, m_rootItem ) );
    }
}


QModelIndex
ProgressTreeModel::indexFromItem( ProgressTreeItem* item )
{
    if ( !item || !item->parent() )
        return QModelIndex();

    // Reconstructs a QModelIndex from a ProgressTreeItem that is somewhere in the tree.
    // Traverses the item to the root node, then rebuilds the qmodelindices from there
    // back down; each int is the row of that item in the parent.
    /**
     * In this diagram, if the item is G, childIndexList will contain [0, 2, 0]
     *
     *    A
     *      D
     *      E
     *      F
     *        G
     *        H
     *    B
     *    C
     *
     **/
    QList< int > childIndexList;
    ProgressTreeItem* curItem = item;
    while ( curItem != m_rootItem ) {
        int row  = curItem->row(); //relative to its parent
        if ( row < 0 ) // something went wrong, bail
            return QModelIndex();

        childIndexList << row;

        curItem = curItem->parent();
    }

    // Now we rebuild the QModelIndex we need
    QModelIndex idx;
    for ( int i = childIndexList.size() - 1; i >= 0 ; i-- )
    {
        idx = index( childIndexList[ i ], 0, idx );
    }

    return idx;
}
