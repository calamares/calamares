/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "ProgressTreeItem.h"

#include "ProgressTreeModel.h"

#include "ViewManager.h"
#include "viewpages/ViewStep.h"


ProgressTreeItem::ProgressTreeItem( ProgressTreeItem* parent )
{
    m_parentItem = parent;
}


ProgressTreeItem::~ProgressTreeItem()
{
    qDeleteAll( m_childItems );
}


void
ProgressTreeItem::appendChild( ProgressTreeItem* item )
{
    m_childItems.append( item );
}


ProgressTreeItem*
ProgressTreeItem::child( int row )
{
    return m_childItems.value( row );
}


int
ProgressTreeItem::childCount() const
{
    return m_childItems.count();
}


int
ProgressTreeItem::columnCount() const
{
    return 1;
}


int
ProgressTreeItem::row() const
{
    if ( m_parentItem )
        return m_parentItem->m_childItems.indexOf(
                    const_cast< ProgressTreeItem* >( this ) );
    return 0;
}


ProgressTreeItem*
ProgressTreeItem::parent()
{
    return m_parentItem;
}


void
ProgressTreeItem::setViewStep( Calamares::ViewStep* step )
{
    m_step = step;
}


QVariant
ProgressTreeItem::data( int role ) const
{
    if ( role == ProgressTreeModel::ProgressTreeItemCurrentRole )
    {
        if ( m_step )
        {
            return Calamares::ViewManager::instance()->currentStep() == m_step;
        }
        else
        {
            return false;
        }
    }
    return QVariant();
}



ProgressTreeRoot::ProgressTreeRoot()
    : ProgressTreeItem()
{}


QVariant
ProgressTreeRoot::data( int role ) const
{
    if ( role == ProgressTreeModel::ProgressTreeItemTypeRole )
        return ProgressTreeModel::Invalid;
    if ( role == ProgressTreeModel::ProgressTreeItemRole )
        return this;
    return QVariant();
}
