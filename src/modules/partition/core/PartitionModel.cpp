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

#include "core/PartitionModel.h"

#include "core/ColorUtils.h"
#include "core/PartitionInfo.h"
#include "core/KPMHelpers.h"
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

//- ResetHelper --------------------------------------------
PartitionModel::ResetHelper::ResetHelper( PartitionModel* model )
    : m_model( model )
{
    m_model->beginResetModel();
}

PartitionModel::ResetHelper::~ResetHelper()
{
    m_model->endResetModel();
}

//- PartitionModel -----------------------------------------
PartitionModel::PartitionModel( QObject* parent )
    : QAbstractItemModel( parent )
    , m_device( nullptr )
{
}

void
PartitionModel::init( Device* device , const OsproberEntryList& osproberEntries )
{
    beginResetModel();
    m_device = device;
    m_osproberEntries = osproberEntries;
    endResetModel();
}

int
PartitionModel::columnCount( const QModelIndex& parent ) const
{
    return ColumnCount;
}

int
PartitionModel::rowCount( const QModelIndex& parent ) const
{
    Partition* parentPartition = partitionForIndex( parent );
    if ( parentPartition )
        return parentPartition->children().count();
    PartitionTable* table = m_device->partitionTable();
    return table ? table->children().count() : 0;
}

QModelIndex
PartitionModel::index( int row, int column, const QModelIndex& parent ) const
{
    PartitionNode* parentPartition = parent.isValid()
                                     ? static_cast< PartitionNode* >( partitionForIndex( parent ) )
                                     : static_cast< PartitionNode* >( m_device->partitionTable() );
    if ( !parentPartition )
        return QModelIndex();
    auto lst = parentPartition->children();
    if ( row < 0 || row >= lst.count() )
        return QModelIndex();
    if ( column < 0 || column >= ColumnCount )
        return QModelIndex();
    Partition* partition = parentPartition->children().at( row );
    return createIndex( row, column, partition );
}

QModelIndex
PartitionModel::parent( const QModelIndex& child ) const
{
    if ( !child.isValid() )
        return QModelIndex();
    Partition* partition = partitionForIndex( child );
    if ( !partition )
        return QModelIndex();
    PartitionNode* parentNode = partition->parent();
    if ( parentNode == m_device->partitionTable() )
        return QModelIndex();

    int row = 0;
    for ( auto p : m_device->partitionTable()->children() )
    {
        if ( parentNode == p )
            return createIndex( row, 0, parentNode );
        ++row;
    }
    cLog() << "No parent found!";
    return QModelIndex();
}

QVariant
PartitionModel::data( const QModelIndex& index, int role ) const
{
    Partition* partition = partitionForIndex( index );
    if ( !partition )
        return QVariant();

    switch ( role )
    {
    case Qt::DisplayRole:
    {
        int col = index.column();
        if ( col == NameColumn )
        {
            if ( KPMHelpers::isPartitionFreeSpace( partition ) )
                return tr( "Free Space" );
            else
            {
                return KPMHelpers::isPartitionNew( partition )
                       ? tr( "New partition" )
                       : partition->partitionPath();
            }
        }
        if ( col == FileSystemColumn )
            return KPMHelpers::prettyNameForFileSystemType( partition->fileSystem().type() );
        if ( col == MountPointColumn )
            return PartitionInfo::mountPoint( partition );
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
            return ColorUtils::colorForPartition( partition );
        else
            return QVariant();
    case Qt::ToolTipRole:
    {
        int col = index.column();
        QString name;
        if ( col == NameColumn )
        {
            if ( KPMHelpers::isPartitionFreeSpace( partition ) )
                name = tr( "Free Space" );
            else
            {
                name = KPMHelpers::isPartitionNew( partition )
                        ? tr( "New partition" )
                        : partition->partitionPath();
            }
        }
        QString prettyFileSystem = KPMHelpers::prettyNameForFileSystemType( partition->fileSystem().type() );
        qint64 size = ( partition->lastSector() - partition->firstSector() + 1 ) * m_device->logicalSize();
        QString prettySize = KFormat().formatByteSize( size );
        return QVariant(name + " " + prettyFileSystem + " " + prettySize);
    }
    case SizeRole:
        return ( partition->lastSector() - partition->firstSector() + 1 ) * m_device->logicalSize();
    case IsFreeSpaceRole:
        return KPMHelpers::isPartitionFreeSpace( partition );

    case IsPartitionNewRole:
        return KPMHelpers::isPartitionNew( partition );

    case FileSystemLabelRole:
        if ( partition->fileSystem().supportGetLabel() != FileSystem::cmdSupportNone &&
             !partition->fileSystem().label().isEmpty() )
            return partition->fileSystem().label();
        return QVariant();

    case FileSystemTypeRole:
        return partition->fileSystem().type();

    case PartitionPathRole:
        return partition->partitionPath();

    case PartitionPtrRole:
        return qVariantFromValue( (void*)partition );

    // Osprober roles:
    case OsproberNameRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone &&
                 !partition->fileSystem().uuid().isEmpty() &&
                 osproberEntry.uuid == partition->fileSystem().uuid() )
                return osproberEntry.prettyName;
        return QVariant();
    case OsproberPathRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone &&
                 !partition->fileSystem().uuid().isEmpty() &&
                 osproberEntry.uuid == partition->fileSystem().uuid() )
                return osproberEntry.path;
        return QVariant();
    case OsproberCanBeResizedRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone &&
                 !partition->fileSystem().uuid().isEmpty() &&
                 osproberEntry.uuid == partition->fileSystem().uuid() )
                return osproberEntry.canBeResized;
        return QVariant();
    case OsproberRawLineRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone &&
                 !partition->fileSystem().uuid().isEmpty() &&
                 osproberEntry.uuid == partition->fileSystem().uuid() )
                return osproberEntry.line;
        return QVariant();
    case OsproberHomePartitionPathRole:
        foreach ( const OsproberEntry& osproberEntry, m_osproberEntries )
            if ( partition->fileSystem().supportGetUUID() != FileSystem::cmdSupportNone &&
                 !partition->fileSystem().uuid().isEmpty() &&
                 osproberEntry.uuid == partition->fileSystem().uuid() )
                return osproberEntry.homePath;
        return QVariant();
    // end Osprober roles.

    default:
        return QVariant();
    }
}

QVariant
PartitionModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
        return QVariant();

    switch ( section )
    {
    case NameColumn:
        return tr( "Name" );
    case FileSystemColumn:
        return tr( "File System" );
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
    if ( !index.isValid() )
        return nullptr;
    return reinterpret_cast< Partition* >( index.internalPointer() );
}


void
PartitionModel::update()
{
    emit dataChanged( index( 0, 0 ), index( rowCount() - 1, columnCount() - 1 ) );
}
