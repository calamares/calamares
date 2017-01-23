/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright (c) 2017, Kyle Robbertze <kyle@aims.ac.za>
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

#include "PackageTreeItem.h"

#include "utils/Logger.h" // TODO:Remove

PackageTreeItem::PackageTreeItem( const ItemData& data, PackageTreeItem* parent ) :
    m_data( data ),
    m_parentItem( parent )
{ }

PackageTreeItem::PackageTreeItem( const QString packageName, PackageTreeItem* parent ) :
    m_packageName( packageName ),
    m_parentItem( parent ),
    m_selected( parent->isSelected() )
{   }

PackageTreeItem::PackageTreeItem( PackageTreeItem* parent ) :
    m_parentItem( parent )
{   }

PackageTreeItem::~PackageTreeItem()
{
    qDeleteAll( m_childItems );
}

void
PackageTreeItem::appendChild( PackageTreeItem* child )
{
    m_childItems.append( child );
}

PackageTreeItem*
PackageTreeItem::child( int row )
{
    return m_childItems.value( row );
}

int
PackageTreeItem::childCount() const
{
    return m_childItems.count();
}

int
PackageTreeItem::row() const
{
    if ( m_parentItem )
        return m_parentItem->m_childItems.indexOf( const_cast<PackageTreeItem*>( this ) );
    return 0;
}

int
PackageTreeItem::columnCount() const
{
    return m_columns;
}

QVariant
PackageTreeItem::data( int column ) const
{
    if ( m_packageName != nullptr ) // package
    {
        if ( column == 1 )
            return QVariant( packageName() );
        return QVariant();
    }
    switch ( column ) // group
    {
    case 0:
        return QVariant( prettyName() );
    case 1:
        return QVariant( description() );
    default:
        return QVariant();
    }
}

PackageTreeItem*
PackageTreeItem::parentItem()
{
    return m_parentItem;
}

QString
PackageTreeItem::prettyName() const
{
    return m_data.name;
}

QString
PackageTreeItem::description() const
{
    return m_data.description;
}

QString
PackageTreeItem::preScript() const
{
    return m_data.preScript;
}

QString
PackageTreeItem::packageName() const
{
    return m_packageName;
}

QString
PackageTreeItem::postScript() const
{
    return m_data.postScript;
}

bool
PackageTreeItem::isHidden() const
{
    return m_hidden;
}

void
PackageTreeItem::setHidden( bool isHidden )
{
    m_hidden = isHidden;
}

bool
PackageTreeItem::isCritical() const
{
    return m_critical;
}

void
PackageTreeItem::setCritical( bool isCritical )
{
    m_critical = isCritical;
}

Qt::CheckState
PackageTreeItem::isSelected() const
{
    return m_selected;
}

void
PackageTreeItem::setSelected( Qt::CheckState isSelected )
{
    m_selected = isSelected;
    setChildrenSelected( isSelected );
    PackageTreeItem* currentItem = parentItem();
    while ( currentItem != nullptr )
    {
        int childrenSelected = 0;
        bool isChildPartiallySelected = false;
        for ( int i = 0; i < currentItem->childCount(); i++ )
        {
            if ( currentItem->child( i )->isSelected() == Qt::Checked )
                childrenSelected++;
            if ( currentItem->child( i )->isSelected() == Qt::PartiallyChecked )
                isChildPartiallySelected = true;
        }
        if ( !childrenSelected  && !isChildPartiallySelected )
            currentItem->m_selected = Qt::Unchecked;
        else if ( childrenSelected == currentItem->childCount() )
            currentItem->m_selected = Qt::Checked;
        else
            currentItem->m_selected = Qt::PartiallyChecked;
        currentItem = currentItem->parentItem();
    }
}

void
PackageTreeItem::setChildrenSelected( Qt::CheckState isSelected )
{
    if ( isSelected != Qt::PartiallyChecked )
        for ( auto child : m_childItems )
        {
            child->m_selected = isSelected;
            child->setChildrenSelected( isSelected );
        }
}

int
PackageTreeItem::type() const
{
    return QStandardItem::UserType;
}
