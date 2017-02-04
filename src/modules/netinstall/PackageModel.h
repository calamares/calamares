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

#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include "PackageTreeItem.h"

#include <QAbstractItemModel>
#include <QObject>
#include <QString>

#include <yaml-cpp/yaml.h>

// Required forward declarations
class PackageTreeItem;

class PackageModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit PackageModel( const YAML::Node& data, const QVariantList& columnHeadings,
                           QObject* parent = 0 );
    ~PackageModel();

    QVariant data( const QModelIndex& index, int role ) const Q_DECL_OVERRIDE;
    bool setData( const QModelIndex& index, const QVariant& value,
                  int role = Qt::EditRole ) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags( const QModelIndex& index ) const Q_DECL_OVERRIDE;
    QVariant headerData( int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole ) const Q_DECL_OVERRIDE;
    QModelIndex index( int row, int column,
                       const QModelIndex& parent = QModelIndex() ) const Q_DECL_OVERRIDE;
    QModelIndex parent( const QModelIndex& index ) const Q_DECL_OVERRIDE;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const Q_DECL_OVERRIDE;
    int columnCount( const QModelIndex& parent = QModelIndex() ) const Q_DECL_OVERRIDE;
    QList<QVariant> getPackages( bool isCritical ) const;
    QList<PackageTreeItem*> getItemPackages( PackageTreeItem* item, bool isCritical ) const;

private:
    void setupModelData( const YAML::Node& data, PackageTreeItem* parent );

    PackageTreeItem* m_rootItem;
    QList<PackageTreeItem*> m_hiddenItems;
    QVariantList m_columnHeadings;
};

#endif // PACKAGEMODEL_H
