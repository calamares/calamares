/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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
#ifndef BOOTLOADERMODEL_H
#define BOOTLOADERMODEL_H

#include <QStandardItemModel>
#include <QList>

class Device;

/**
 * This model contains one entry for each device MBR plus one entry for the
 * /boot or / partition
 */
class BootLoaderModel : public QStandardItemModel
{
    Q_OBJECT
public:
    enum
    {
        BootLoaderPathRole = Qt::UserRole + 1,
        IsPartitionRole
    };

    BootLoaderModel( QObject* parent = nullptr );
    ~BootLoaderModel() override;

    /**
     * Init the model with the list of devices. Does *not* take ownership of the
     * devices.
     */
    void init( const QList< Device* >& devices );

    void update();

    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;

private:
    QList< Device* > m_devices;

    void createMbrItems();
};

#endif /* BOOTLOADERMODEL_H */
