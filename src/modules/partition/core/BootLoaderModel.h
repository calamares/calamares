/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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
#ifndef BOOTLOADERMODEL_H
#define BOOTLOADERMODEL_H

#include <QList>
#include <QMutex>
#include <QStandardItemModel>

class Device;
class QComboBox;

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

    using DeviceList = QList< Device* >;

private:
    DeviceList m_devices;
    mutable QMutex m_lock;

    void createMbrItems();
    void updateInternal();
};

namespace Calamares
{
/** @brief Returns the row number of boot-loader @p path (e.g. /dev/sda)
 *
 * Assuming the @p model is a BootLoaderModel, will return a row number
 * in the model. Returns -1 otherwise.
 */
int findBootloader( const QAbstractItemModel* model, const QString& path );

/** @brief Tries to set @p path as selected item in @p combo
 *
 * Matches a boot-loader install path (e.g. /dev/sda) with a model
 * row and sets that as the current row.
 */
void restoreSelectedBootLoader( QComboBox& combo, const QString& path );
}  // namespace Calamares
#endif /* BOOTLOADERMODEL_H */
