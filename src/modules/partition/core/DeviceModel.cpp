/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "core/DeviceModel.h"

#include "core/PartitionModel.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/device.h>

// KF5
#include <KFormat>

#include <QIcon>
#include <QStandardItemModel>

// STL
#include <algorithm>

static void
sortDevices( DeviceModel::DeviceList& l )
{
    std::sort( l.begin(), l.end(), []( const Device* dev1, const Device* dev2 ) {
        return dev1->deviceNode() < dev2->deviceNode();
    } );
}

DeviceModel::DeviceModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

DeviceModel::~DeviceModel() {}

void
DeviceModel::init( const DeviceList& devices )
{
    beginResetModel();
    m_devices = devices;
    sortDevices( m_devices );
    endResetModel();
}

int
DeviceModel::rowCount( const QModelIndex& parent ) const
{
    return parent.isValid() ? 0 : m_devices.count();
}

QVariant
DeviceModel::data( const QModelIndex& index, int role ) const
{
    int row = index.row();
    if ( row < 0 || row >= m_devices.count() )
    {
        return QVariant();
    }

    Device* device = m_devices.at( row );

    switch ( role )
    {
    case Qt::DisplayRole:
    case Qt::ToolTipRole:
        if ( device->name().isEmpty() )
        {
            return device->deviceNode();
        }
        else
        {
            if ( device->logicalSize() >= 0 && device->totalLogical() >= 0 )
            {
                //: device[name] - size[number] (device-node[name])
                return tr( "%1 - %2 (%3)" )
                    .arg( device->name() )
                    .arg( KFormat().formatByteSize( device->capacity() ) )
                    .arg( device->deviceNode() );
            }
            else
            {
                // Newly LVM VGs don't have capacity property yet (i.e.
                // always has 1B capacity), so don't show it for a while.
                //
                //: device[name] - (device-node[name])
                return tr( "%1 - (%2)" ).arg( device->name() ).arg( device->deviceNode() );
            }
        }
    case Qt::DecorationRole:
        return CalamaresUtils::defaultPixmap(
            CalamaresUtils::PartitionDisk,
            CalamaresUtils::Original,
            QSize( CalamaresUtils::defaultIconSize().width() * 2, CalamaresUtils::defaultIconSize().height() * 2 ) );
    default:
        return QVariant();
    }
}


Device*
DeviceModel::deviceForIndex( const QModelIndex& index ) const
{
    int row = index.row();
    if ( row < 0 || row >= m_devices.count() )
    {
        return nullptr;
    }
    return m_devices.at( row );
}


void
DeviceModel::swapDevice( Device* oldDevice, Device* newDevice )
{
    Q_ASSERT( oldDevice );
    Q_ASSERT( newDevice );

    int indexOfOldDevice = m_devices.indexOf( oldDevice );
    if ( indexOfOldDevice < 0 )
    {
        return;
    }

    m_devices[ indexOfOldDevice ] = newDevice;

    Q_EMIT dataChanged( index( indexOfOldDevice ), index( indexOfOldDevice ) );
}

void
DeviceModel::addDevice( Device* device )
{
    beginResetModel();
    m_devices << device;
    sortDevices( m_devices );
    endResetModel();
}

void
DeviceModel::removeDevice( Device* device )
{
    beginResetModel();
    m_devices.removeAll( device );
    sortDevices( m_devices );
    endResetModel();
}
