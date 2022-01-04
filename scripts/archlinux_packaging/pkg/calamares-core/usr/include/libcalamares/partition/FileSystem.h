/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/*
 * NOTE: this functionality is only available when Calamares is compiled
 *       with KPMcore support.
 */

#ifndef PARTITION_FILESYSTEM_H
#define PARTITION_FILESYSTEM_H

#include "DllMacro.h"

#include <kpmcore/fs/filesystem.h>

namespace CalamaresUtils
{
namespace Partition
{
QString DLLEXPORT prettyNameForFileSystemType( FileSystem::Type t );

/** @brief Returns a machine-readable identifier for the filesystem type
 *
 * This identifier is  used in filesystem manipulation --
 * e.g. when mounting the filesystem, or in /etc/fstab. It
 * is almost always just what KPMCore says it is, with
 * the following exceptions:
 *  - reiserfs is called "reiser" by KPMCore, "reiserfs" by Calamares
 */
QString DLLEXPORT untranslatedFS( FileSystem::Type t );

/** @brief Returns the machine-readable identifier for the given @p fs
 *
 * See notes for untranslatedFS(), above.
 */
static inline QString
untranslatedFS( FileSystem& fs )
{
    return untranslatedFS( fs.type() );
}

/** @brief Returns a machine-readable identifier for the given @p fs
 *
 * Returns an empty string is the @p fs is not valid (e.g. nullptr).
 */
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
