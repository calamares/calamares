/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
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

#ifndef PARTITION_SYNC_H
#define PARTITION_SYNC_H

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
void sync();

/** @brief RAII class for calling sync() */
struct Syncer
{
    ~Syncer() { sync(); }
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif
