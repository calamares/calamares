/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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
#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include <QScopedPointer>
#include <QList>

class Device;
class PartitionModel;

/**
 * A Qt model which exposes a list of Devices.
 */
class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DeviceModel( QObject* parent = nullptr );
    ~DeviceModel() override;

    /**
     * Init the model with the list of devices. Does *not* take ownership of the
     * devices.
     */
    void init( const QList< Device* >& devices );

    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;

    Device* deviceForIndex( const QModelIndex& index ) const;

    void swapDevice( Device* oldDevice, Device* newDevice );

private:
    QList< Device* > m_devices;
};

#endif /* DEVICEMODEL_H */
