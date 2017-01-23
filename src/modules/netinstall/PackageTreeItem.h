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

#ifndef PACKAGETREEITEM_H
#define PACKAGETREEITEM_H

#include "NetInstallPage.h"

#include <QList>
#include <QVariant>
#include <QStandardItem>

class PackageTreeItem : public QStandardItem
{
    public:
        struct ItemData {
            QString name;
            QString description;
            QString preScript;
            QString postScript;
        };
        explicit PackageTreeItem( const ItemData& data, PackageTreeItem* parent = 0 );
        explicit PackageTreeItem( const QString packageName, PackageTreeItem* parent = 0 );
        explicit PackageTreeItem( PackageTreeItem* parent = 0 );
        ~PackageTreeItem();

        void appendChild( PackageTreeItem* child );
        PackageTreeItem* child( int row );
        int childCount() const;
        int columnCount() const;
        QVariant data( int column ) const Q_DECL_OVERRIDE;
        int row() const;
        PackageTreeItem* parentItem();
        QString prettyName() const;
        QString description() const;
        QString preScript() const;
        QString packageName() const;
        QString postScript() const;
        bool isHidden() const;
        void setHidden( bool isHidden);
        bool isCritical() const;
        void setCritical( bool isCritical);
        Qt::CheckState isSelected() const;
        void setSelected( Qt::CheckState isSelected );
        void setChildrenSelected( Qt::CheckState isSelected );
        int type() const Q_DECL_OVERRIDE;

        static const int PreScriptRole = Qt::UserRole;
        static const int PackageNameRole = Qt::UserRole + 1;
        static const int PostScriptRole = Qt::UserRole + 2;
    private:
        QList<PackageTreeItem*> m_childItems;
        ItemData m_data;
        QString m_packageName;

        // See README.md for a description of these two fields.
        Qt::CheckState m_selected = Qt::Unchecked;
        bool m_hidden = false;
        bool m_critical = false;
        const int m_columns = 2; // Name, description
        PackageTreeItem* m_parentItem;
};

#endif // PACKAGETREEITEM_H
