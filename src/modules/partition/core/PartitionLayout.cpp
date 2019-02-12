/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Collabora Ltd
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

#include "core/PartitionLayout.h"

#include "core/KPMHelpers.h"
#include "core/PartitionActions.h"
#include "core/PartitionInfo.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

PartitionLayout::PartitionLayout()
{
}

PartitionLayout::PartitionLayout( PartitionLayout::PartitionEntry entry )
{
    partLayout.append( entry );
}

PartitionLayout::PartitionLayout( const PartitionLayout& layout )
    : partLayout( layout.partLayout )
{
}

PartitionLayout::~PartitionLayout()
{
}

void
PartitionLayout::addEntry( PartitionLayout::PartitionEntry entry )
{
    partLayout.append( entry );
}

static double
parseSizeString( const QString& sizeString, PartitionLayout::SizeUnit* unit )
{
    double value;
    bool ok;
    QString valueString;
    QString unitString;

    QRegExp rx( "[KkMmGg%]" );
    int pos = rx.indexIn( sizeString );
    if (pos > 0)
    {
        valueString = sizeString.mid( 0, pos );
        unitString = sizeString.mid( pos );
    }
    else
        valueString = sizeString;

    value = valueString.toDouble( &ok );
    if ( !ok )
    {
        /*
         * In case the conversion fails, a size of 100% allows a few cases to pass
         * anyway (e.g. when it is the last partition of the layout)
         */
        *unit = PartitionLayout::SizeUnit::Percent;
        return 100;
    }

    if ( unitString.length() > 0 )
    {
        if ( unitString.at(0) == '%' )
            *unit = PartitionLayout::SizeUnit::Percent;
        else if ( unitString.at(0).toUpper() == 'K' )
            *unit = PartitionLayout::SizeUnit::KiB;
        else if ( unitString.at(0).toUpper() == 'M' )
            *unit = PartitionLayout::SizeUnit::MiB;
        else if ( unitString.at(0).toUpper() == 'G' )
            *unit = PartitionLayout::SizeUnit::GiB;
        else
            *unit = PartitionLayout::SizeUnit::Byte;
    }
    else
    {
        *unit = PartitionLayout::SizeUnit::Byte;
    }

    return value;
}

PartitionLayout::PartitionEntry::PartitionEntry(const QString& size, const QString& min)
{
    partSize = parseSizeString( size , &partSizeUnit );
    if ( !min.isEmpty() )
        partMinSize = parseSizeString( min , &partMinSizeUnit );
}

void
PartitionLayout::addEntry( const QString& mountPoint, const QString& size, const QString& min )
{
    PartitionLayout::PartitionEntry entry( size, min );

    entry.partMountPoint = mountPoint;
    entry.partFileSystem = FileSystem::Ext4;

    partLayout.append( entry );
}

void
PartitionLayout::addEntry( const QString& label, const QString& mountPoint, const QString& fs, const QString& size, const QString& min )
{
    PartitionLayout::PartitionEntry entry( size, min );

    entry.partLabel = label;
    entry.partMountPoint = mountPoint;
    entry.partFileSystem = FileSystem::typeForName( fs );

    partLayout.append( entry );
}

static qint64
sizeToSectors( double size, PartitionLayout::SizeUnit unit, qint64 totalSize, qint64 logicalSize )
{
    qint64 sectors;
    double tmp;

    if ( unit == PartitionLayout::SizeUnit::Percent )
    {
        tmp = static_cast<double>( totalSize ) * size / 100;
        sectors = static_cast<qint64>( tmp );
    }
    else
    {
        tmp = size;
        if ( unit >= PartitionLayout::SizeUnit::KiB )
            tmp *= 1024;
        if ( unit >= PartitionLayout::SizeUnit::MiB )
            tmp *= 1024;
        if ( unit >= PartitionLayout::SizeUnit::GiB )
            tmp *= 1024;

        sectors = PartitionActions::bytesToSectors( static_cast<unsigned long long>( tmp ),
                                                    logicalSize
                                                  );
    }

    return sectors;
}

QList< Partition* >
PartitionLayout::execute( Device *dev, qint64 firstSector,
                          qint64 lastSector, QString luksPassphrase,
                          PartitionNode* parent,
                          const PartitionRole& role )
{
    QList< Partition* > partList;
    qint64 size, minSize, end;
    qint64 totalSize = lastSector - firstSector + 1;
    qint64 availableSize = totalSize;

    // TODO: Refine partition sizes to make sure there is room for every partition
    // Use a default (200-500M ?) minimum size for partition without minSize

    foreach( const PartitionLayout::PartitionEntry& part, partLayout )
    {
        Partition *currentPartition = nullptr;

        // Calculate partition size
        size = sizeToSectors( part.partSize, part.partSizeUnit, totalSize, dev->logicalSize() );
        minSize = sizeToSectors( part.partMinSize, part.partMinSizeUnit, totalSize, dev->logicalSize() );
        if ( size < minSize )
            size = minSize;
        if ( size > availableSize )
            size = availableSize;
        end = firstSector + size - 1;

        if ( luksPassphrase.isEmpty() )
        {
            currentPartition = KPMHelpers::createNewPartition(
                parent,
                *dev,
                role,
                static_cast<FileSystem::Type>(part.partFileSystem),
                firstSector,
                end,
                PartitionTable::FlagNone
            );
        }
        else
        {
            currentPartition = KPMHelpers::createNewEncryptedPartition(
                parent,
                *dev,
                role,
                static_cast<FileSystem::Type>(part.partFileSystem),
                firstSector,
                end,
                luksPassphrase,
                PartitionTable::FlagNone
            );
        }
        PartitionInfo::setFormat( currentPartition, true );
        PartitionInfo::setMountPoint( currentPartition, part.partMountPoint );
        if ( !part.partLabel.isEmpty() )
            currentPartition->fileSystem().setLabel( part.partLabel );
        // Some buggy (legacy) BIOSes test if the bootflag of at least one partition is set.
        // Otherwise they ignore the device in boot-order, so add it here.
        partList.append( currentPartition );
        firstSector = end + 1;
        availableSize -= size;
    }

    return partList;
}
