/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

/** @brief Gets filesystem names from KPMCore
 *
 * A name (e.g. "ext4") can be for internal, untranslated, use, or for
 * user-visible use. In the latter case it should be translated. The
 * KPMCore API gives user-visible names by default.
 */
#ifndef PARTITION_FSNAME_H
#define PARTITION_FSNAME_H

#include <fs/filesystem.h>

#include <QString>

namespace CalamaresUtils
{
namespace Partition
{

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

}  // namespace Partition
}  // namespace CalamaresUtils

#endif  // PARTITION_FSNAME_H
