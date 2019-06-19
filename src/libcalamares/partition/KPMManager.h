/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

/*
 * NOTE: this functionality is only available when Calamares is compiled
 *       with KPMcore support.
 */

#ifndef PARTITION_KPMMANAGER_H
#define PARTITION_KPMMANAGER_H

#include <memory>

class CoreBackend;

namespace CalamaresUtils
{
namespace Partition
{
/// @brief Handle to KPMCore
class InternalManager;

/** @brief KPMCore loader and cleanup
 *
 * A Calamares plugin that uses KPMCore should hold an object of
 * this class; its only responsibility is to load KPMCore
 * and to cleanly unload it on destruction (with KPMCore 4,
 * also to shutdown the privileged helper application).
 *
 * It loads the default plugin ("parted" with KPMCore 3, "sfdisk"
 * with KPMCore 4), but this can be overridden by setting the
 * environment variable KPMCORE_BACKEND. Setting it to
 * "dummy" will load the dummy plugin instead.
 */
class KPMManager
{
public:
    KPMManager();
    ~KPMManager();

    /// @brief Is KPMCore loaded correctly?
    operator bool() const;

    /// @brief Gets the KPMCore backend (e.g. CoreBackendManager::self()->backend() )
    CoreBackend* backend() const;

private:
    std::shared_ptr< InternalManager > m_d;
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif  // PARTITION_KPMMANAGER_H
