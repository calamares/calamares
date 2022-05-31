/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anubhav Choudhary <ac.10edu@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/BootLoaderModel.h"

#include "core/KPMHelpers.h"
#include "core/PartitionInfo.h"

#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QComboBox>

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

BootLoaderModel::~BootLoaderModel() {}

void
BootLoaderModel::init( const QList< Device* >& devices )
{
    beginResetModel();
    blockSignals( true );

    m_devices = devices;
    updateInternal();

    blockSignals( false );
    endResetModel();
}

void
BootLoaderModel::createMbrItems()
{
    for ( auto device : m_devices )
    {
        QString text = tr( "Master Boot Record of %1" ).arg( device->name() );
        appendRow( createBootLoaderItem( text, device->deviceNode(), false ) );
    }
}

void
BootLoaderModel::update()
{
    beginResetModel();
    blockSignals( true );
    updateInternal();
    blockSignals( false );
    endResetModel();
}


void
BootLoaderModel::updateInternal()
{
    QMutexLocker lock( &m_lock );
    clear();
    createMbrItems();

    // An empty model is possible if you don't have permissions: don't crash though.
    if ( rowCount() < 1 )
    {
        return;
    }

    QString partitionText;
    Partition* partition = KPMHelpers::findPartitionByMountPoint( m_devices, "/boot" );
    if ( partition )
    {
        partitionText = tr( "Boot Partition" );
    }
    else
    {
        partition = KPMHelpers::findPartitionByMountPoint( m_devices, "/" );
        if ( partition )
        {
            partitionText = tr( "System Partition" );
        }
    }

    Q_ASSERT( rowCount() > 0 );
    QStandardItem* last = item( rowCount() - 1 );
    Q_ASSERT( last );
    bool lastIsPartition = last->data( IsPartitionRole ).toBool();

    if ( !partition )
    {
        if ( lastIsPartition )
        {
            takeRow( rowCount() - 1 );
        }
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
            appendRow( createBootLoaderItem( partitionText, PartitionInfo::mountPoint( partition ), true ) );
        }
    }
    // Create "don't install bootloader" item. This is always available,
    // also if there was no /boot or / partition found.
    appendRow( createBootLoaderItem( tr( "Do not install a boot loader" ), QString(), false ) );
}


QVariant
BootLoaderModel::data( const QModelIndex& index, int role ) const
{
    QMutexLocker lock( &m_lock );
    if ( role == Qt::DisplayRole )
    {
        QString displayRole = QStandardItemModel::data( index, Qt::DisplayRole ).toString();
        QString pathRole = QStandardItemModel::data( index, BootLoaderModel::BootLoaderPathRole ).toString();
        if ( pathRole.isEmpty() )
        {
            return displayRole;
        }

        return tr( "%1 (%2)" ).arg( displayRole, pathRole );
    }
    return QStandardItemModel::data( index, role );
}

std::pair< int, Device* >
BootLoaderModel::findBootLoader( const QString& path ) const
{
    int r = 0;
    for ( Device* d : m_devices )
    {
        if ( d && d->deviceNode() == path )
        {
            return std::make_pair( r, d );
        }
        r++;
    }

    Partition* partition = KPMHelpers::findPartitionByMountPoint( m_devices, path );
    if ( partition )
    {
        const QString partition_device_path = partition->deviceNode();
        r = 0;
        for ( Device* d : m_devices )
        {
            if ( d && d->deviceNode() == partition_device_path )
            {
                return std::make_pair( r, d );
            }
            r++;
        }
    }
    return std::make_pair( -1, nullptr );
}


namespace Calamares
{
void
restoreSelectedBootLoader( QComboBox& combo, const QString& path )
{
    const auto* model = combo.model();
    if ( model->rowCount() < 1 )
    {
        cDebug() << "No items in BootLoaderModel";
        return;
    }

    if ( path.isEmpty() )
    {
        cDebug() << "No path to restore, choosing default";
        combo.setCurrentIndex( 0 );
        return;
    }

    const BootLoaderModel* bmodel = qobject_cast< const BootLoaderModel* >( model );
    int r = bmodel ? bmodel->findBootLoader( path ).first : -1;
    if ( r >= 0 )
    {
        combo.setCurrentIndex( r );
    }
    else
    {
        combo.setCurrentIndex( 0 );
    }
}

}  // namespace Calamares
