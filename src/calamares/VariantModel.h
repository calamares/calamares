/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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
    IndexVector m_rows;

    /// @brief Implementation of walking an index through the variant-tree
    const QVariant underlying( const QModelIndex& index ) const;
};

#endif
