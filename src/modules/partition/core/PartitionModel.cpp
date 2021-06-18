/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/PartitionModel.h"

#include "core/ColorUtils.h"
#include "core/KPMHelpers.h"
#include "core/PartitionInfo.h"

#include "partition/FileSystem.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"

// CalaPM
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/core/partitiontable.h>
#include <kpmcore/fs/filesystem.h>

// KF5
#include <KFormat>

// Qt
#include <QColor>

using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::isPartitionNew;

//- ResetHelper --------------------------------------------
PartitionModel::ResetHelper::ResetHelper( PartitionModel* model )
    : m_model( model )
{
    m_model->m_lock.lock();
    m_model->beginResetModel();
}

PartitionModel::ResetHelper::~ResetHelper()
{
    // We need to unlock the mutex before emitting the reset signal,
    // because the reset will cause clients to start looking at the
    // (new) data.
    m_model->m_lock.unlock();
    m_model->endResetModel();
}

//- PartitionModel -----------------------------------------
PartitionModel::PartitionModel( QObject* parent )
    : QAbstractItemModel( parent )
    , m_device( nullptr )
{
}

void
PartitionModel::init( Device* device, const OsproberEntryList& osproberEntries )
{
    QMutexLocker lock( &m_lock );
    beginResetModel();
    m_device = device;
    m_osproberEntries = osproberEntries;
    endResetModel();
}

int
PartitionModel::columnCount( const QModelIndex& ) const
{
    return ColumnCount;
}

int
PartitionModel::rowCount( const QModelIndex& parent ) const
{
    Partition* parentPartition = partitionForIndex( parent );
    if ( parentPartition )
    {
        return parentPartition->children().count();
    }
    PartitionTable* table = m_device->partitionTable();
    return table ? table->children().count() : 0;
}

QModelIndex
PartitionModel::index( int row, int column, const QModelIndex& parent ) const
{
    PartitionNode* parentPartition = parent.isValid() ? static_cast< PartitionNode* >( partitionForIndex( parent ) )
                                                      : static_cast< PartitionNode* >( m_device->partitionTable() );
    if ( !parentPartition )
    {
        return QModelIndex();
    }
    auto lst = parentPartition->children();
    if ( row < 0 || row >= lst.count() )
    {
        return QModelIndex();
    }
    if ( column < 0 || column >= ColumnCount )
    {
        return QModelIndex();
    }
    Partition* partition = parentPartition->children().at( row );
    return createIndex( row, column, partition );
}

QModelIndex
PartitionModel::parent( const QModelIndex& child ) const
{
    if ( !child.isValid() )
    {
        return QModelIndex();
    }
    Partition* partition = partitionForIndex( child );
    if ( !partition )
    {
        return QModelIndex();
    }
    PartitionNode* parentNode = partition->parent();
    if ( parentNode == m_device->partitionTable() )
    {
        return QModelIndex();
    }

    int row = 0;
    for ( auto p : m_device->partitionTable()->children() )
    {
        if ( parentNode == p )
        {
            return createIndex( row, 0, parentNode );
        }
        ++row;
    }
    cWarning() << "No parent found!";
    return QModelIndex();
}

QVariant
PartitionModel::data( const QModelIndex& index, int role ) const
{
    Partition* partition = partitionForIndex( index );
    if ( !partition )
    {
        return QVariant();
    }

    switch ( role )
    {
    case Qt::DisplayRole:
    {
        int col = index.column();
        if ( col == NameColumn )
        {
            if ( isPartitionFreeSpace( partition ) )
            {
                return tr( "Free Space" );
            }
            else
            {
                return isPartitionNew( partition ) ? tr( "New partition" ) : partition->partitionPath();
            }
        }
        if ( col == FileSystemColumn )
        {
            return CalamaresUtils::Partition::prettyNameForFileSystemType( partition->fileSystem().type() );
        }
        if ( col == FileSystemLabelColumn )
        {
            return partition->fileSystem().label();
        }
        if ( col == MountPointColumn )
        {
            return PartitionInfo::mountPoint( partition );
        }
        if ( col == SizeColumn )
        {
            qint64 size = ( partition->lastSector() - partition->firstSector() + 1 ) * m_device->logicalSize();
            return KFormat().formatByteSize( size );
        }
        cDebug() << "Unknown column" << col;
        return QVariant();
    }
    case Qt::DecorationRole:
        if ( index.column() == NameColumn )
        {
            return ColorUtils::colorForPartition( partition );
        }
        else
        {
            return QVariant();
        }
    case Qt::ToolTipRole:
    {
        int col = index.column();
        QString name;
        if ( col == NameColumn )
        {
            if ( isPartitionFreeSpace( partition ) )
            {
                name = tr( "Free Space" );
            }
            else
            {
                name = isPartitionNew( partition ) ? tr( "New partition" ) : partition->partitionPath();
            }
        }
        QString prettyFileSystem
            = CalamaresUtils::Partition::prettyNameForFileSystemType( partition->fileSystem().type() );
        qint64 size = ( partition->lastSector() - partition->firstSector() + 1 ) * m_device->logicalSize();
        QString prettySize = KFormat().formatByteSize( size );
        return QVariant( name + " " + prettyFileSystem + " " + prettySize );
    }
    case SizeRole:
        return ( partition->lastSector() - partition->firstSector() + 1 ) * m_device->logicalSize();
    case IsFreeSpaceRole:
        return isPartitionFreeSpace( partition );

    case IsPartitionNewRole:
        return isPartitionNew( partition );

    case FileSystemLabelRole:
        if ( partition->fileSystem().supportGetLabel() != FileSystem::cmdSupportNone
             && !partition->fileSystem().label().isEmpty() )
        {
            return partition->fileSystem().label();
        }
        return QVariant();

    case FileSystemTypeRole:
        return partition->fileSystem().type();

    case PartitionPathRole:
        return partition->partitionPath();

    case PartitionPtrRole:
        return QVariant::fromValue( (void*)partition );

    // Osprober roles:
    case OsproberNameRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
                 && !partition->fileSystem().uuid().isEmpty() && osproberEntry.uuid == partition->fileSystem().uuid() )
            {
                return osproberEntry.prettyName;
            }
        return QVariant();
    case OsproberPathRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
                 && !partition->fileSystem().uuid().isEmpty() && osproberEntry.uuid == partition->fileSystem().uuid() )
            {
                return osproberEntry.path;
            }
        return QVariant();
    case OsproberCanBeResizedRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
                 && !partition->fileSystem().uuid().isEmpty() && osproberEntry.uuid == partition->fileSystem().uuid() )
            {
                return osproberEntry.canBeResized;
            }
        return QVariant();
    case OsproberRawLineRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
                 && !partition->fileSystem().uuid().isEmpty() && osproberEntry.uuid == partition->fileSystem().uuid() )
            {
                return osproberEntry.line;
            }
        return QVariant();
    case OsproberHomePartitionPathRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone
                 && !partition->fileSystem().uuid().isEmpty() && osproberEntry.uuid == partition->fileSystem().uuid() )
            {
                return osproberEntry.homePath;
            }
        return QVariant();
        // end Osprober roles.

    default:
        return QVariant();
    }
}

QVariant
PartitionModel::headerData( int section, Qt::Orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    switch ( section )
    {
    case NameColumn:
        return tr( "Name" );
    case FileSystemColumn:
        return tr( "File System" );
    case FileSystemLabelColumn:
        return tr( "File System Label" );
    case MountPointColumn:
        return tr( "Mount Point" );
    case SizeColumn:
        return tr( "Size" );
    default:
        cDebug() << "Unknown column" << section;
        return QVariant();
    }
}

Partition*
PartitionModel::partitionForIndex( const QModelIndex& index ) const
{
    QMutexLocker lock( &m_lock );
    if ( !index.isValid() )
    {
        return nullptr;
    }
    return reinterpret_cast< Partition* >( index.internalPointer() );
}


void
PartitionModel::update()
{
    Q_EMIT dataChanged( index( 0, 0 ), index( rowCount() - 1, columnCount() - 1 ) );
}
