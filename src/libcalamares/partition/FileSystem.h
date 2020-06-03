/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

/*
 * NOTE: this functionality is only available when Calamares is compiled
 *       with KPMcore support.
 */

#ifndef PARTITION_FILESYSTEM_H
#define PARTITION_FILESYSTEM_H

#include <kpmcore/fs/filesystem.h>

namespace CalamaresUtils
{
namespace Partition
{
QString prettyNameForFileSystemType( FileSystem::Type t );

static inline QString
untranslatedFS( FileSystem& fs )
{
    return fs.name( { QStringLiteral( "C" ) } );
}

static inline QString
untranslatedFS( FileSystem* fs )
{
    return fs ? untranslatedFS( *fs ) : QString();
}

static inline QString
userVisibleFS( FileSystem& fs )
{
    return fs.name();
}

static inline QString
userVisibleFS( FileSystem* fs )
{
    return fs ? userVisibleFS( *fs ) : QString();
}


}  // namespace Partition
}  // namespace CalamaresUtils

#endif  // PARTITION_PARTITIONQUERY_H
