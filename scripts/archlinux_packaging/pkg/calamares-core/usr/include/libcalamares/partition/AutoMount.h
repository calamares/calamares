/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef PARTITION_AUTOMOUNT_H
#define PARTITION_AUTOMOUNT_H

#include "DllMacro.h"

#include <memory>

namespace CalamaresUtils
{
namespace Partition
{

struct AutoMountInfo;

/** @brief Disable automount
 *
 * Various subsystems can do "agressive automount", which can get in the
 * way of partitioning actions. In particular, Solid can be configured
 * to automount every device it sees, and partitioning happens in multiple
 * steps (create table, create partition, set partition flags) which are
 * blocked if the partition gets mounted partway through the operation.
 *
 * @param disable set this to false to reverse the sense of the function
 *      call and force *enabling* automount, instead.
 *
 * Returns an opaque structure which can be passed to automountRestore()
 * to return the system to the previously-configured automount settings.
 */
DLLEXPORT std::shared_ptr< AutoMountInfo > automountDisable( bool disable = true );

/** @brief Restore automount settings
 *
 * Pass the value returned from automountDisable() to restore the
 * previous settings.
 */
DLLEXPORT void automountRestore( const std::shared_ptr< AutoMountInfo >& t );

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
