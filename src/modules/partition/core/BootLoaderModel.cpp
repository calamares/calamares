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

#include "core/BootLoaderModel.h"

#include "core/PartitionInfo.h"
#include "core/KPMHelpers.h"

// KPMcore
#include <kpmcore/core/device.h>

static QStandardItem*
createBootLoaderItem( const QString& description, const QString& path, bool isPartition )
{
    QStandardItem* item = new QStandardItem( description );
    item->setData( path, BootLoaderModel::BootLoaderPathRole );
    item->setData( isPartition, BootLoaderModel::IsPartitionRole );
    return item;
}

BootLoaderModel::BootLoaderModel( QObject* parent )
    : QStandardItemModel( parent )
{
}

BootLoaderModel::~BootLoaderModel()
{
}

void
BootLoaderModel::init( const QList< Device* >& devices )
{
    m_devices = devices;
    clear();
    createMbrItems();
}

void
BootLoaderModel::createMbrItems()
{
    for ( auto device : m_devices )
    {
        QString text = tr( "Master Boot Record of %1" )
                       .arg( device->name() );
        appendRow(
            createBootLoaderItem( text, device->deviceNode(), false )
        );
    }
}

void
BootLoaderModel::update()
{
    clear();
    createMbrItems();

    QString partitionText;
    Partition* partition = KPMHelpers::findPartitionByMountPoint( m_devices, "/boot" );
    if ( partition )
        partitionText = tr( "Boot Partition" );
    else
    {
        partition = KPMHelpers::findPartitionByMountPoint( m_devices, "/" );
        if ( partition )
            partitionText = tr( "System Partition" );
    }

    Q_ASSERT( rowCount() > 0 );
    QStandardItem* last = item( rowCount() - 1 );
    Q_ASSERT( last );
    bool lastIsPartition = last->data( IsPartitionRole ).toBool();

    if ( !partition )
    {
        if ( lastIsPartition )
            takeRow( rowCount() - 1 );
    }
    else
    {
        QString mountPoint = PartitionInfo::mountPoint( partition );
        if ( lastIsPartition )
        {
            last->setText( partitionText );
            last->setData( mountPoint, BootLoaderPathRole );
        }
        else
        {
            appendRow(
                createBootLoaderItem( partitionText, PartitionInfo::mountPoint( partition ), true )
            );
        }

        // Create "don't install bootloader" item
        appendRow(
            createBootLoaderItem( tr( "Do not install a boot loader" ), QString(), false )
        );
    }
}


QVariant
BootLoaderModel::data( const QModelIndex& index, int role ) const
{
    if ( role == Qt::DisplayRole )
    {
        if ( QStandardItemModel::data( index, BootLoaderModel::BootLoaderPathRole ).toString().isEmpty() )
            return QStandardItemModel::data( index, Qt::DisplayRole ).toString();

        return tr( "%1 (%2)" )
                .arg( QStandardItemModel::data( index, Qt::DisplayRole ).toString() )
                .arg( QStandardItemModel::data( index, BootLoaderModel::BootLoaderPathRole ).toString() );
    }
    return QStandardItemModel::data( index, role );
}
