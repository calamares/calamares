/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef PROGRESSTREEMODEL_H
#define PROGRESSTREEMODEL_H

#include <QAbstractItemModel>

class ProgressTreeRoot;
class ProgressTreeItem;


/**
 * @brief The ProgressTreeModel class implements a model for the ProgressTreeView.
 */
class ProgressTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Role
    {
        ProgressTreeItemRole        = Qt::UserRole + 10,
        ProgressTreeItemCurrentRole = Qt::UserRole + 11
    };

    explicit ProgressTreeModel( QObject* parent = nullptr );
    virtual ~ProgressTreeModel() override;

    // Reimplemented from QAbstractItemModel
    Qt::ItemFlags flags( const QModelIndex& index ) const override;
    QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
    QModelIndex parent( const QModelIndex& index ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    int columnCount( const QModelIndex& parent = QModelIndex() ) const override;

private:
    void setupModelData();
    QModelIndex indexFromItem( ProgressTreeItem* item );

    ProgressTreeRoot* m_rootItem;
};

#endif // PROGRESSTREEMODEL_H
