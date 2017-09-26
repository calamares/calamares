/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright (c) 2017, Kyle Robbertze <kyle@aims.ac.za>
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

#include "PackageModel.h"

#include "utils/YamlUtils.h"

PackageModel::PackageModel( const YAML::Node& data, QObject* parent ) :
    QAbstractItemModel( parent ),
    m_columnHeadings()
{
    m_rootItem = new PackageTreeItem();
    setupModelData( data, m_rootItem );
}

PackageModel::~PackageModel()
{
    delete m_rootItem;
}

QModelIndex
PackageModel::index( int row, int column, const QModelIndex& parent ) const
{
    if ( !hasIndex( row, column, parent ) )
        return QModelIndex();

    PackageTreeItem* parentItem;

    if ( !parent.isValid() )
        parentItem = m_rootItem;
    else
        parentItem = static_cast<PackageTreeItem*>( parent.internalPointer() );

    PackageTreeItem* childItem = parentItem->child( row );
    if ( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}

QModelIndex
PackageModel::parent( const QModelIndex& index ) const
{
    if ( !index.isValid() )
        return QModelIndex();

    PackageTreeItem* child = static_cast<PackageTreeItem*>( index.internalPointer() );
    PackageTreeItem* parent = child->parentItem();

    if ( parent == m_rootItem )
        return QModelIndex();
    return createIndex( parent->row(), 0, parent );
}

int
PackageModel::rowCount( const QModelIndex& parent ) const
{
    if ( parent.column() > 0 )
        return 0;

    PackageTreeItem* parentItem;
    if ( !parent.isValid() )
        parentItem = m_rootItem;
    else
        parentItem = static_cast<PackageTreeItem*>( parent.internalPointer() );

    return parentItem->childCount();
}

int
PackageModel::columnCount( const QModelIndex& parent ) const
{
    if ( parent.isValid() )
        return static_cast<PackageTreeItem*>( parent.internalPointer() )->columnCount();
    return m_rootItem->columnCount();
}

QVariant
PackageModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    PackageTreeItem* item = static_cast<PackageTreeItem*>( index.internalPointer() );
    if ( index.column() == 0 && role == Qt::CheckStateRole )
        return item->isSelected();

    if ( item->isHidden() && role == Qt::DisplayRole ) // Hidden group
        return QVariant();

    if ( role == Qt::DisplayRole )
        return item->data( index.column() );
    return QVariant();
}

bool
PackageModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    if ( role == Qt::CheckStateRole && index.isValid() )
    {
        PackageTreeItem* item = static_cast<PackageTreeItem*>( index.internalPointer() );
        item->setSelected( static_cast<Qt::CheckState>( value.toInt() ) );

        emit dataChanged( this->index( 0, 0 ), index.sibling( index.column(), index.row() + 1 ),
                          QVector<int>( Qt::CheckStateRole ) );
    }
    return true;
}

bool
PackageModel::setHeaderData( int section, Qt::Orientation orientation,
                             const QVariant& value, int role )
{
    Q_UNUSED( role );

    if ( orientation == Qt::Horizontal )
    {
        if ( m_columnHeadings.value( section ) != QVariant() )
            m_columnHeadings.replace( section, value );
        else
            m_columnHeadings.insert( section, value );
        emit headerDataChanged( orientation, section, section );
    }
    return true;
}

Qt::ItemFlags
PackageModel::flags( const QModelIndex& index ) const
{
    if ( !index.isValid() )
        return 0;
    if ( index.column() == 0 )
        return Qt::ItemIsUserCheckable | QAbstractItemModel::flags( index );
    return QAbstractItemModel::flags( index );
}

QVariant
PackageModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        return m_columnHeadings.value( section );
    return QVariant();
}

QList<PackageTreeItem::ItemData>
PackageModel::getPackages() const
{
    QList<PackageTreeItem*> items = getItemPackages( m_rootItem );
    for ( auto package : m_hiddenItems )
        items.append( getItemPackages( package ) );
    QList<PackageTreeItem::ItemData> packages;
    for ( auto item : items )
    {
        PackageTreeItem::ItemData itemData;
        itemData.preScript = item->parentItem()->preScript(); // Only groups have hooks
        itemData.packageName = item->packageName(); // this seg faults
        itemData.postScript = item->parentItem()->postScript(); // Only groups have hooks
        itemData.isCritical = item->parentItem()->isCritical(); // Only groups are critical
        packages.append( itemData );
    }
    return packages;
}

QList<PackageTreeItem*>
PackageModel::getItemPackages( PackageTreeItem* item ) const
{
    QList<PackageTreeItem*> selectedPackages;
    for ( int i = 0; i < item->childCount(); i++ )
    {
        if ( item->child( i )->isSelected() == Qt::Unchecked )
            continue;

        if ( !item->child( i )->childCount() ) // package
            selectedPackages.append( item->child( i ) );
        else
            selectedPackages.append( getItemPackages( item->child( i ) ) );
    }
    return selectedPackages;

}

void
PackageModel::setupModelData( const YAML::Node& data, PackageTreeItem* parent )
{
    for ( YAML::const_iterator it = data.begin(); it != data.end(); ++it )
    {
        const YAML::Node itemDefinition = *it;

        QString name(
            tr( CalamaresUtils::yamlToVariant( itemDefinition["name"] ).toByteArray() ) );
        QString description(
            tr( CalamaresUtils::yamlToVariant( itemDefinition["description"] ).toByteArray() ) );

        PackageTreeItem::ItemData itemData;
        itemData.name = name;
        itemData.description = description;

        if ( itemDefinition["pre-install"] )
            itemData.preScript =
                CalamaresUtils::yamlToVariant( itemDefinition["pre-install"] ).toString();
        if ( itemDefinition["post-install"] )
            itemData.postScript =
                CalamaresUtils::yamlToVariant( itemDefinition["post-install"] ).toString();
        PackageTreeItem* item = new PackageTreeItem( itemData, parent );

        if ( itemDefinition["selected"] )
            item->setSelected(
                CalamaresUtils::yamlToVariant( itemDefinition["selected"] ).toBool() ?
                Qt::Checked : Qt::Unchecked );
        else
            item->setSelected( parent->isSelected() ); // Inherit from it's parent

        if ( itemDefinition["hidden"] )
            item->setHidden(
                CalamaresUtils::yamlToVariant( itemDefinition["hidden"] ).toBool() );

        if ( itemDefinition["critical"] )
            item->setCritical(
                CalamaresUtils::yamlToVariant( itemDefinition["critical"] ).toBool() );

        if ( itemDefinition["packages"] )
            for ( YAML::const_iterator packageIt = itemDefinition["packages"].begin();
                    packageIt != itemDefinition["packages"].end(); ++packageIt )
                item->appendChild(
                    new PackageTreeItem( CalamaresUtils::yamlToVariant( *packageIt ).toString(), item ) );

        if ( itemDefinition["subgroups"] )
            setupModelData( itemDefinition["subgroups"], item );

        if ( item->isHidden() )
            m_hiddenItems.append( item );
        else
        {
            item->setCheckable( true );
            parent->appendChild( item );
        }
    }
}
