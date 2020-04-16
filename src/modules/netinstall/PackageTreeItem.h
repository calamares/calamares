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
    using List = QList< PackageTreeItem* >;

    ///@brief A tag class to distinguish package-from-map from group-from-map
    struct PackageTag
    {
        PackageTreeItem* parent;
    };
    ///@brief A tag class to distinguish group-from-map from package-from-map
    struct GroupTag
    {
        PackageTreeItem* parent;
    };

    ///@brief A package (individual package)
    explicit PackageTreeItem( const QString& packageName, PackageTreeItem* parent = nullptr );
    ///@brief A package (individual package with description)
    explicit PackageTreeItem( const QVariantMap& packageData, PackageTag&& parent );
    ///@brief A group (sub-items and sub-groups are ignored)
    explicit PackageTreeItem( const QVariantMap& groupData, GroupTag&& parent );
    ///@brief A root item, always selected, named "<root>"
    explicit PackageTreeItem();
    ~PackageTreeItem() override;

    void appendChild( PackageTreeItem* child );
    PackageTreeItem* child( int row );
    int childCount() const;
    QVariant data( int column ) const override;
    int row() const;

    PackageTreeItem* parentItem();
    const PackageTreeItem* parentItem() const;

    QString name() const { return m_name; }
    QString packageName() const { return m_packageName; }

    QString description() const { return m_description; }
    QString preScript() const { return m_preScript; }
    QString postScript() const { return m_postScript; }

    /** @brief Is this item a group-item?
     *
     * Groups have a (possibly empty) list of packages, and a
     * (possibly empty) list of sub-groups, and can be marked
     * critical, hidden, etc. Packages, on the other hand, only
     * have a meaningful packageName() and selection status.
     *
     * Root is a group.
     */
    bool isGroup() const { return m_isGroup; }

    /// @brief Is this item a single package?
    bool isPackage() const { return !isGroup(); }

    /** @brief Is this item hidden?
     *
     * Hidden items (generally only groups) are maintained separately,
     * not shown to the user, but do enter into the package-installation process.
     */
    bool isHidden() const { return m_isHidden; }

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
    bool isCritical() const { return m_isCritical; }

    /** @brief Is this group expanded on start?
     *
     * This does not affect installation, only the UI. A group
     * that expands on start is shown expanded (not collapsed)
     * in the treeview when the page is loaded.
     */
    bool expandOnStart() const { return m_startExpanded; }

    /** @brief Is this an immutable item?
     *
     * Groups can be immutable: then you can't toggle the selected
     * state of any of its items.
     */
    bool isImmutable() const { return m_showReadOnly; }

    /** @brief is this item selected?
     *
     * Groups may be partially selected; packages are only on or off.
     */
    Qt::CheckState isSelected() const { return m_selected; }

    /** @brief Turns this item into a variant for PackageOperations use
     *
     * For "plain" items, this is just the package name; items with
     * scripts return a map. See the package module for how it's interpreted.
     */
    QVariant toOperation() const;

    void setSelected( Qt::CheckState isSelected );
    void setChildrenSelected( Qt::CheckState isSelected );

    /** @brief Update selectedness based on the children's states
     *
     * This only makes sense for groups, which might have packages
     * or subgroups; it checks only direct children.
     */
    void updateSelected();

    // QStandardItem methods
    int type() const override;

    /** @brief Are two items equal
     *
     * This **disregards** parent-item and the child-items, and compares
     * only the fields for the items-proper (name, .. expanded). Note
     * also that *isSelected()* is a run-time state, and is **not**
     * compared either.
     */
    bool operator==( const PackageTreeItem& rhs ) const;
    bool operator!=( const PackageTreeItem& rhs ) const { return !( *this == rhs ); }

private:
    PackageTreeItem* m_parentItem;
    List m_childItems;

    // An entry can be a package, or a group.
    QString m_name;
    QString m_packageName;
    Qt::CheckState m_selected = Qt::Unchecked;

    // These are only useful for groups
    QString m_description;
    QString m_preScript;
    QString m_postScript;
    bool m_isGroup = false;
    bool m_isCritical = false;
    bool m_isHidden = false;
    bool m_showReadOnly = false;
    bool m_startExpanded = false;
};

#endif  // PACKAGETREEITEM_H
