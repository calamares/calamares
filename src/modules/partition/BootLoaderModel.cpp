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
#include <BootLoaderModel.h>

#include <PartitionInfo.h>
#include <PMUtils.h>

// CalaPM
#include <core/device.h>

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
    for( auto device : m_devices )
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
    QString partitionText;
    Partition* partition = PMUtils::findPartitionByMountPoint( m_devices, "/boot" );
    if ( partition )
        partitionText = tr( "Boot Partition" );
    else
    {
        partition = PMUtils::findPartitionByMountPoint( m_devices, "/" );
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
        return;
    }

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
}

