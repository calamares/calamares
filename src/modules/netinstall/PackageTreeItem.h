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

#ifndef PACKAGETREEITEM_H
#define PACKAGETREEITEM_H

#include <QList>
#include <QVariant>
#include <QStandardItem>

class PackageTreeItem : public QStandardItem
{
public:
    struct ItemData
    {
        QString name;
        QString description;
        QString preScript;
        QString packageName;
        QString postScript;
        bool isCritical = false;
        bool isHidden = false;
        Qt::CheckState selected = Qt::Unchecked;
    };
    explicit PackageTreeItem( const ItemData& data, PackageTreeItem* parent = nullptr );
    explicit PackageTreeItem( const QString packageName, PackageTreeItem* parent = nullptr );
    explicit PackageTreeItem( PackageTreeItem* parent = nullptr );
    ~PackageTreeItem() override;

    void appendChild( PackageTreeItem* child );
    PackageTreeItem* child( int row );
    int childCount() const;
    int columnCount() const;
    QVariant data( int column ) const override;
    int row() const;
    PackageTreeItem* parentItem();
    QString prettyName() const;
    QString description() const;
    QString preScript() const;
    QString packageName() const;
    QString postScript() const;
    bool isHidden() const;
    void setHidden( bool isHidden );
    bool isCritical() const;
    void setCritical( bool isCritical );
    Qt::CheckState isSelected() const;
    void setSelected( Qt::CheckState isSelected );
    void setChildrenSelected( Qt::CheckState isSelected );
    int type() const override;
private:
    PackageTreeItem* m_parentItem;
    QList<PackageTreeItem*> m_childItems;
    ItemData m_data;
    const int m_columns = 2; // Name, description
};

#endif // PACKAGETREEITEM_H
