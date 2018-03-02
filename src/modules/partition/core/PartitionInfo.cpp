/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "core/PartitionInfo.h"

// KPMcore
#include <kpmcore/core/partition.h>

// Qt
#include <QVariant>

namespace PartitionInfo
{

static const char* MOUNT_POINT_PROPERTY = "_calamares_mountPoint";
static const char* FORMAT_PROPERTY = "_calamares_format";

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

void
reset( Partition* partition )
{
    partition->setProperty( MOUNT_POINT_PROPERTY, QVariant() );
    partition->setProperty( FORMAT_PROPERTY, QVariant() );
}

bool
isDirty( Partition* partition )
{
    return !mountPoint( partition ).isEmpty()
           || format( partition );
}

} // namespace
