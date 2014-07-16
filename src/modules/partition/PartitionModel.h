/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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
#ifndef PARTITIONMODEL_H
#define PARTITIONMODEL_H

// Qt
#include <QAbstractListModel>

class Device;
class Partition;
class PartitionNode;

class PartitionModel : public QAbstractListModel
{
public:
    enum Column
    {
        NameColumn,
        FileSystemColumn,
        MountPointColumn,
        SizeColumn,
        LastColumn = SizeColumn + 1
    };

    PartitionModel( QObject* parent = 0 );
    /**
     * device must remain alive for the life of PartitionModel
     */
    void init( Device* device );

    int columnCount( const QModelIndex& parent = QModelIndex() ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;

    Partition* partitionForIndex( const QModelIndex& index ) const;

    Device* device() const
    {
        return m_device;
    }

    /**
     * Reload model from m_device new content
     */
    void reload();

private:
    Device* m_device;
    QList< Partition* > m_partitionList;

    void fillPartitionList( PartitionNode* parent );
};

#endif /* PARTITIONMODEL_H */
