/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef VARIANTMODEL_H
#define VARIANTMODEL_H

#include <QAbstractItemModel>
#include <QVariantMap>
#include <QVector>

/** @brief A model that operates directly on a QVariant
 *
 * A VariantModel operates directly on an underlying
 * QVariant, treating QVariantMap and QVariantList as
 * nodes with multiple children. In general, putting
 * a QVariantMap into a QVariant and passing that into
 * the model will get you a tree-like model of the
 * VariantMap's data structure.
 *
 * Take care of object lifetimes and that the underlying
 * QVariant does not change during use. If the QVariant
 * **does** change, call reload() to re-build the internal
 * representation of the tree.
 */
class VariantModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    /** @brief Auxiliary data
     *
     * The nodes of the tree are enumerated into a vector
     * (of length equal to the number of nodes in the tree + 1)
     * which are used to do index and parent calculations.
     */
    using IndexVector = QVector< quintptr >;

    /** @brief Constructor
     *
     * The QVariant's lifetime is **not** affected by the model,
     * so take care that the QVariant lives at least as long as
     * the model). Also, don't change the QVariant underneath the model.
     */
    VariantModel( const QVariant* p );

    ~VariantModel() override;

    /** @brief Re-build the internal tree
     *
     * Call this when the underlying variant is changed, which
     * might impact how the tree is laid out.
     */
    void reload();

    int columnCount( const QModelIndex& index ) const override;
    int rowCount( const QModelIndex& index ) const override;

    QModelIndex index( int row, int column, const QModelIndex& parent ) const override;
    QModelIndex parent( const QModelIndex& index ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const override;

private:
    const QVariant* const m_p;

    /** @brief Tree representation of the variant.
     *
     * At index 0 in the vector , we store -1 to indicate the root.
     *
     * Then we enumerate all the elements in the tree (by traversing
     * the variant and using QVariantMap and QVariantList as having
     * children, and everything else being a leaf node) and at the index
     * for a child, store the index of its parent. This means that direct
     * children of the root store a 0 in their indexes, children of the first
     * child of the root store a 1, and we can "pointer chase" from an index
     * through parents back to index 0.
     *
     * Because of this structure, the value stored at index i must be
     * less than i (except for index 0, which is special). This makes it
     * slightly easier to search for a given value *p*, because we can start
     * at index *p* (or even *p+1*).
     *
     * Given an index *i* into the vector corresponding to a child, we know the
     * parent, but can also count which row this child should have, by counting
     * *other* indexes before *i* with the same parent (and by the ordering
     * of values, we can start counting at index *parent-index*).
     *
     */
    IndexVector m_rows;

    /// @brief Implementation of walking an index through the variant-tree
    const QVariant underlying( const QModelIndex& index ) const;

    /// @brief Helpers for range-checking
    inline bool inRange( quintptr p ) const { return p < static_cast< quintptr >( m_rows.count() ); }
    inline bool inRange( const QModelIndex& index ) const { return inRange( index.internalId() ); }
};

#endif
