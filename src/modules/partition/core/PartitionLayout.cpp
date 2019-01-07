/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
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
parseSizeString( QString sizeString, PartitionLayout::SizeUnit *unit )
{
    double value;
    bool ok;

    QRegExp rx( "[KkMmGg%]" );
    int pos = rx.indexIn( sizeString );
    QString valueString = sizeString.mid( 0, pos );
    QString unitString = sizeString.mid( pos );

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

void
PartitionLayout::addEntry( QString mountPoint, QString size, QString min )
{
    PartitionLayout::PartitionEntry entry;

    entry.partMountPoint = mountPoint;
    entry.partFileSystem = FileSystem::Ext4;
    entry.partSize = parseSizeString( size , &entry.partSizeUnit );
    entry.partMinSize = parseSizeString( min , &entry.partMinSizeUnit );

    partLayout.append( entry );
}

void
PartitionLayout::addEntry( QString label, QString mountPoint, QString fs, QString size, QString min )
{
    PartitionLayout::PartitionEntry entry;

    entry.partLabel = label;
    entry.partMountPoint = mountPoint;
    entry.partFileSystem = FileSystem::typeForName( fs );
    entry.partSize = parseSizeString( size , &entry.partSizeUnit );
    entry.partMinSize = parseSizeString( min , &entry.partMinSizeUnit );

    partLayout.append( entry );
}
