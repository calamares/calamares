/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright (c) 2017, Kyle Robbertze <kyle@aims.ac.za>
 *   Copyright 2017-2018, 2020, Adriaan de Groot <groot@kde.org>
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

#include "PackageModel.h"

#include "utils/Variant.h"
#include "utils/Yaml.h"

PackageModel::PackageModel( QObject* parent )
    : QAbstractItemModel( parent )
{
}

PackageModel::~PackageModel()
{
    delete m_rootItem;
}

QModelIndex
PackageModel::index( int row, int column, const QModelIndex& parent ) const
{
    if ( !m_rootItem || !hasIndex( row, column, parent ) )
    {
        return QModelIndex();
    }

    PackageTreeItem* parentItem;

    if ( !parent.isValid() )
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast< PackageTreeItem* >( parent.internalPointer() );
    }

    PackageTreeItem* childItem = parentItem->child( row );
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
PackageModel::parent( const QModelIndex& index ) const
{
    if ( !m_rootItem || !index.isValid() )
    {
        return QModelIndex();
    }

    PackageTreeItem* child = static_cast< PackageTreeItem* >( index.internalPointer() );
    PackageTreeItem* parent = child->parentItem();

    if ( parent == m_rootItem )
    {
        return QModelIndex();
    }
    return createIndex( parent->row(), 0, parent );
}

int
PackageModel::rowCount( const QModelIndex& parent ) const
{
    if ( !m_rootItem || ( parent.column() > 0 ) )
    {
        return 0;
    }

    PackageTreeItem* parentItem;
    if ( !parent.isValid() )
    {
        parentItem = m_rootItem;
    }
    else
    {
        parentItem = static_cast< PackageTreeItem* >( parent.internalPointer() );
    }

    return parentItem->childCount();
}

int
PackageModel::columnCount( const QModelIndex& ) const
{
    return 2;
}

QVariant
PackageModel::data( const QModelIndex& index, int role ) const
{
    if ( !m_rootItem || !index.isValid() )
    {
        return QVariant();
    }

    PackageTreeItem* item = static_cast< PackageTreeItem* >( index.internalPointer() );
    switch ( role )
    {
    case Qt::CheckStateRole:
        return index.column() == NameColumn ? ( item->isImmutable() ? QVariant() : item->isSelected() ) : QVariant();
    case Qt::DisplayRole:
        return item->isHidden() ? QVariant() : item->data( index.column() );
    case MetaExpandRole:
        return item->isHidden() ? false : item->expandOnStart();
    default:
        return QVariant();
    }
}

bool
PackageModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if ( !m_rootItem )
    {
        return false;
    }

    if ( role == Qt::CheckStateRole && index.isValid() )
    {
        PackageTreeItem* item = static_cast< PackageTreeItem* >( index.internalPointer() );
        item->setSelected( static_cast< Qt::CheckState >( value.toInt() ) );

        emit dataChanged( this->index( 0, 0 ),
                          index.sibling( index.column(), index.row() + 1 ),
                          QVector< int >( Qt::CheckStateRole ) );
    }
    return true;
}

Qt::ItemFlags
PackageModel::flags( const QModelIndex& index ) const
{
    if ( !m_rootItem || !index.isValid() )
    {
        return Qt::ItemFlags();
    }
    if ( index.column() == NameColumn )
    {
        PackageTreeItem* item = static_cast< PackageTreeItem* >( index.internalPointer() );
        if ( item->isImmutable() )
        {
            return QAbstractItemModel::flags( index );  //Qt::NoItemFlags;
        }
        return Qt::ItemIsUserCheckable | QAbstractItemModel::flags( index );
    }
    return QAbstractItemModel::flags( index );
}

QVariant
PackageModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {
        return ( section == NameColumn ) ? tr( "Name" ) : tr( "Description" );
    }
    return QVariant();
}

PackageTreeItem::List
PackageModel::getPackages() const
{
    if ( !m_rootItem )
    {
        return PackageTreeItem::List();
    }

    auto items = getItemPackages( m_rootItem );
    for ( auto package : m_hiddenItems )
    {
        if ( package->hiddenSelected() )
        {
            items.append( getItemPackages( package ) );
        }
    }
    return items;
}

PackageTreeItem::List
PackageModel::getItemPackages( PackageTreeItem* item ) const
{
    PackageTreeItem::List selectedPackages;
    for ( int i = 0; i < item->childCount(); i++ )
    {
        auto* child = item->child( i );
        if ( child->isSelected() == Qt::Unchecked )
        {
            continue;
        }

        if ( child->isPackage() )  // package
        {
            selectedPackages.append( child );
        }
        else
        {
            selectedPackages.append( getItemPackages( child ) );
        }
    }
    return selectedPackages;
}

void
PackageModel::setupModelData( const QVariantList& groupList, PackageTreeItem* parent )
{
    for ( const auto& group : groupList )
    {
        QVariantMap groupMap = group.toMap();
        if ( groupMap.isEmpty() )
        {
            continue;
        }

        PackageTreeItem* item = new PackageTreeItem( groupMap, PackageTreeItem::GroupTag { parent } );
        if ( groupMap.contains( "selected" ) )
        {
            item->setSelected( CalamaresUtils::getBool( groupMap, "selected", false ) ? Qt::Checked : Qt::Unchecked );
        }
        if ( groupMap.contains( "packages" ) )
        {
            for ( const auto& packageName : groupMap.value( "packages" ).toList() )
            {
                if ( packageName.type() == QVariant::String )
                {
                    item->appendChild( new PackageTreeItem( packageName.toString(), item ) );
                }
                else
                {
                    QVariantMap m = packageName.toMap();
                    if ( !m.isEmpty() )
                    {
                        item->appendChild( new PackageTreeItem( m, PackageTreeItem::PackageTag { item } ) );
                    }
                }
            }
        }
        if ( groupMap.contains( "subgroups" ) )
        {
            QVariantList subgroups = groupMap.value( "subgroups" ).toList();
            if ( !subgroups.isEmpty() )
            {
                setupModelData( subgroups, item );
                // The children might be checked while the parent isn't (yet).
                // Children are added to their parent (below) without affecting
                // the checked-state -- do it manually.
                item->updateSelected();
            }
        }
        if ( item->isHidden() )
        {
            m_hiddenItems.append( item );
        }
        else
        {
            item->setCheckable( true );
            parent->appendChild( item );
        }
    }
}

void
PackageModel::setupModelData( const QVariantList& l )
{
    emit beginResetModel();
    delete m_rootItem;
    m_rootItem = new PackageTreeItem();
    setupModelData( l, m_rootItem );
    emit endResetModel();
}
