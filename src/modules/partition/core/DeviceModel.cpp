/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
#include "core/DeviceModel.h"

#include "core/PartitionModel.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/device.h>

// KF5
#include <KFormat>

#include <QIcon>

// STL
#include <algorithm>

DeviceModel::DeviceModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

DeviceModel::~DeviceModel()
{
}

void
DeviceModel::init( const QList< Device* >& devices )
{
    beginResetModel();
    m_devices = devices;
    std::sort( m_devices.begin(), m_devices.end(), []( const Device* dev1, const Device* dev2 )
    {
        return dev1->deviceNode() < dev2->deviceNode();
    } );
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
        return QVariant();

    Device* device = m_devices.at( row );

    switch ( role )
    {
    case Qt::DisplayRole:
    case Qt::ToolTipRole:
        if ( device->name().isEmpty() )
            return device->deviceNode();
        else
            return tr( "%1 - %2 (%3)" )
                   .arg( device->name() )
                   .arg( KFormat().formatByteSize( device->capacity() ) )
                   .arg( device->deviceNode() );
    case Qt::DecorationRole:
        return CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionDisk,
                                              CalamaresUtils::Original,
                                              QSize( CalamaresUtils::defaultIconSize().width() * 3,
                                                     CalamaresUtils::defaultIconSize().height() * 3 ) );
    default:
        return QVariant();
    }
}


Device*
DeviceModel::deviceForIndex( const QModelIndex& index ) const
{
    int row = index.row();
    if ( row < 0 || row >= m_devices.count() )
        return nullptr;
    return m_devices.at( row );
}


void
DeviceModel::swapDevice( Device* oldDevice, Device* newDevice )
{
    Q_ASSERT( oldDevice );
    Q_ASSERT( newDevice );

    int indexOfOldDevice = m_devices.indexOf( oldDevice );
    if ( indexOfOldDevice < 0 )
        return;

    m_devices[ indexOfOldDevice ] = newDevice;

    emit dataChanged( index( indexOfOldDevice ), index( indexOfOldDevice ) );
}
