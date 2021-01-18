/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef PARTITION_SYNC_H
#define PARTITION_SYNC_H

#include "DllMacro.h"

namespace CalamaresUtils
{
namespace Partition
{

/** @brief Run "udevadm settle" or other disk-sync mechanism.
 *
 * Call this after mounting, unmount, toggling swap, or other functions
 * that might cause the disk to be "busy" for other disk-modifying
 * actions (in particular, KPMcore actions with the sfdisk backend
 * are sensitive, and systemd tends to keep disks busy after a change
 * for a while).
 */
DLLEXPORT void sync();

/** @brief RAII class for calling sync() */
struct DLLEXPORT Syncer
{
    ~Syncer() { sync(); }
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
