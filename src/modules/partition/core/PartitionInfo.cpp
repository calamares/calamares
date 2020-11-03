/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "core/PartitionInfo.h"

// KPMcore
#include <kpmcore/core/lvmdevice.h>
#include <kpmcore/core/partition.h>

// Qt
#include <QVariant>

namespace PartitionInfo
{

static const char MOUNT_POINT_PROPERTY[] = "_calamares_mountPoint";
static const char FORMAT_PROPERTY[] = "_calamares_format";
static const char FLAGS_PROPERTY[] = "_calamares_flags";

QString
mountPoint( Partition* partition )
{
    return partition->property( MOUNT_POINT_PROPERTY ).toString();
}

void
setMountPoint( Partition* partition, const QString& value )
{
    partition->setProperty( MOUNT_POINT_PROPERTY, value );
}

bool
format( Partition* partition )
{
    return partition->property( FORMAT_PROPERTY ).toBool();
}

void
setFormat( Partition* partition, bool value )
{
    partition->setProperty( FORMAT_PROPERTY, value );
}

PartitionTable::Flags
flags( const Partition* partition )
{
    auto v = partition->property( FLAGS_PROPERTY );
    if ( !v.isValid() )
    {
        return partition->activeFlags();
    }
    // The underlying type of PartitionTable::Flags can be int or uint
    // (see qflags.h) and so setting those flags can create a QVariant
    // of those types; we don't just want to check QVariant::canConvert()
    // here because that will also accept QByteArray and some other things.
    if ( v.type() == QVariant::Int || v.type() == QVariant::UInt )
    {
        return static_cast< PartitionTable::Flags >( v.toInt() );
    }
    return partition->activeFlags();
}

void
setFlags( Partition* partition, PartitionTable::Flags f )
{
    partition->setProperty( FLAGS_PROPERTY, PartitionTable::Flags::Int( f ) );
}

void
reset( Partition* partition )
{
    partition->setProperty( MOUNT_POINT_PROPERTY, QVariant() );
    partition->setProperty( FORMAT_PROPERTY, QVariant() );
    partition->setProperty( FLAGS_PROPERTY, QVariant() );
}

bool
isDirty( Partition* partition )
{
    if ( LvmDevice::s_DirtyPVs.contains( partition ) )
    {
        return true;
    }

    return !mountPoint( partition ).isEmpty() || format( partition ) || flags( partition ) != partition->activeFlags();
}

}  // namespace PartitionInfo
