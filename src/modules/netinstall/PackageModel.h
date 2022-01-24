
/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze <kyle@aims.ac.za>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include "PackageTreeItem.h"

#include <QAbstractItemModel>
#include <QObject>
#include <QString>

namespace YAML
{
class Node;
}

class PackageModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    // Names for columns (unused in the code)
    static constexpr const int NameColumn = 0;
    static constexpr const int DescriptionColumn = 1;

    /* The only interesting roles are DisplayRole (with text depending
     * on the column, and MetaExpandRole which tells if an index
     * should be initially expanded.
     */
    static constexpr const int MetaExpandRole = Qt::UserRole + 1;

    explicit PackageModel( QObject* parent = nullptr );
    ~PackageModel() override;

    void setupModelData( const QVariantList& l );

    QVariant data( const QModelIndex& index, int role ) const override;
    bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;
    Qt::ItemFlags flags( const QModelIndex& index ) const override;

    QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
    QModelIndex parent( const QModelIndex& index ) const override;

    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    int columnCount( const QModelIndex& parent = QModelIndex() ) const override;

    /** @brief Sets the checked flag on matching groups in the tree
     *
     * Recursively traverses the tree pointed to by m_rootItem and
     * checks if a group name matches any of the items in @p selectNames.
     * If a match is found, set check the box for that group and it's children.
     *
     * Individual packages will not be matched.
     *
     */
    void setSelections(const QStringList &selectNames );

    PackageTreeItem::List getPackages() const;
    PackageTreeItem::List getItemPackages( PackageTreeItem* item ) const;

    void appendModelData(const QVariantList& groupList);

private:
    friend class ItemTests;

    void setupModelData( const QVariantList& l, PackageTreeItem* parent );

    PackageTreeItem* m_rootItem = nullptr;
    PackageTreeItem::List m_hiddenItems;
};

#endif  // PACKAGEMODEL_H
