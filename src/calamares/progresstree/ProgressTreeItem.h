/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#ifndef PROGRESSTREEITEM_H
#define PROGRESSTREEITEM_H

#include <QList>
#include <QVariant>


/**
 * @brief The ProgressTreeItem class represents an item in the
 * ProgressTreeModel/ProgressTreeView.
 * Each item generally represents a ViewStep.
 */
class ProgressTreeItem
{
public:
    explicit ProgressTreeItem( ProgressTreeItem* parent = nullptr );

    virtual ~ProgressTreeItem();

    virtual void appendChild( ProgressTreeItem* item );

    virtual ProgressTreeItem* child( int row );
    virtual int childCount() const;
    virtual int columnCount() const;
    virtual QVariant data( int role ) const = 0;
    virtual int row() const;
    virtual ProgressTreeItem* parent();

private:
    QList< ProgressTreeItem* > m_childItems;
    ProgressTreeItem* m_parentItem;
};

class ProgressTreeRoot : public ProgressTreeItem
{
public:
    explicit ProgressTreeRoot();

    virtual QVariant data( int role ) const;
};

#endif // PROGRESSTREEITEM_H
