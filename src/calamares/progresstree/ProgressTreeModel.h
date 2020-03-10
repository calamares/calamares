/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include <QAbstractListModel>

/**
 * @brief The ProgressTreeModel class implements a model for the ProgressTreeView.
 */
class ProgressTreeModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role
    {
        ProgressTreeItemCurrentRole = Qt::UserRole + 11,  ///< Is this the *current* step?
        ProgressTreeItemCompletedRole = Qt::UserRole + 12  ///< Are we past this one?
    };

    explicit ProgressTreeModel( QObject* parent = nullptr );
    virtual ~ProgressTreeModel() override;

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;

    QHash< int, QByteArray > roleNames() const override;
};

#endif  // PROGRESSTREEMODEL_H
