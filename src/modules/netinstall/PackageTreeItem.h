/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright (c) 2017, Kyle Robbertze <kyle@aims.ac.za>
 *   Copyright 2017, 2020, Adriaan de Groot <groot@kde.org>
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
#include <QStandardItem>
#include <QVariant>

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
        bool startExpanded = false;  // Only for groups
        Qt::CheckState selected = Qt::Unchecked;

        /** @brief Turns this item into a variant for PackageOperations use
         *
         * For "plain" items, this is just the package name; items with
         * scripts return a map. See the package module for how it's interpreted.
         */
        QVariant toOperation() const;
    };
    explicit PackageTreeItem( const ItemData& data, PackageTreeItem* parent = nullptr );
    explicit PackageTreeItem( const QString packageName, PackageTreeItem* parent = nullptr );
    explicit PackageTreeItem( PackageTreeItem* parent );
    explicit PackageTreeItem();  // The root of the tree; always selected, named <root>
    ~PackageTreeItem() override;

    void appendChild( PackageTreeItem* child );
    PackageTreeItem* child( int row );
    int childCount() const;
    QVariant data( int column ) const override;
    int row() const;

    PackageTreeItem* parentItem();
    const PackageTreeItem* parentItem() const;

    QString prettyName() const;
    QString description() const;
    QString preScript() const;
    QString packageName() const;
    QString postScript() const;

    /** @brief Is this item hidden?
     *
     * Hidden items (generally only groups) are maintained separately,
     * not shown to the user, but do enter into the package-installation process.
     */
    bool isHidden() const;

    /** @brief Is this hidden item, considered "selected"?
     *
     * This asserts when called on a non-hidden item.
     * A hidden item has its own selected state, but really
     * falls under the selectedness of the parent item.
     */
    bool hiddenSelected() const;

    /** @brief Is this group critical?
     *
     * A critical group must be successfully installed, for the Calamares
     * installation to continue.
     */
    bool isCritical() const;

    /** @brief Is this group expanded on start?
     *
     * This does not affect installation, only the UI. A group
     * that expands on start is shown expanded (not collapsed)
     * in the treeview when the page is loaded.
     */
    bool expandOnStart() const { return m_data.startExpanded; }

    Qt::CheckState isSelected() const;
    void setSelected( Qt::CheckState isSelected );
    void setChildrenSelected( Qt::CheckState isSelected );
    int type() const override;

private:
    PackageTreeItem* m_parentItem;
    QList< PackageTreeItem* > m_childItems;
    ItemData m_data;
};

#endif  // PACKAGETREEITEM_H
