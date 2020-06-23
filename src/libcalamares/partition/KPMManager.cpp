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

#include "KPMManager.h"

#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#if defined( WITH_KPMCORE4API )
#include <kpmcore/util/externalcommand.h>
#endif


#include <QObject>


namespace CalamaresUtils
{
namespace Partition
{
class InternalManager
{
public:
    InternalManager();
    ~InternalManager();
};

static bool s_kpm_loaded = false;

/*
 * We have one living InternalManager object at a time.
 * It is managed by shared_ptr<>s help by KPMManager
 * objects, but since we can create KPMManager objects
 * independent of each other, all of which share ownership
 * of the same InternalManager, hang on to one extra reference
 * to the InternalManager so we can hand it out in getInternal().
 */
static std::weak_ptr< InternalManager > s_backend;

InternalManager::InternalManager()
{
    cDebug() << "KPMCore backend starting ..";

    Q_ASSERT( s_backend.expired() );

    if ( !s_kpm_loaded )
    {
        QByteArray backendName = qgetenv( "KPMCORE_BACKEND" );
        if ( !CoreBackendManager::self()->load( backendName.isEmpty() ? CoreBackendManager::defaultBackendName()
                                                                      : backendName ) )
        {
            cWarning() << "Failed to load backend plugin" << backendName;
        }
        else
        {
            auto* backend_p = CoreBackendManager::self()->backend();
            cDebug() << Logger::SubEntry << "Backend" << Logger::Pointer(backend_p) << backend_p->id() << backend_p->version();
            s_kpm_loaded = true;
        }
    }
}

InternalManager::~InternalManager()
{
    cDebug() << "Cleaning up KPMCore backend ..";

#if defined( WITH_KPMCORE4API )
    auto backend_p = CoreBackendManager::self()->backend();
    if ( backend_p )
    {
        ExternalCommand::stopHelper();
    }
#endif
}

std::shared_ptr< InternalManager >
getInternal()
{
    if ( s_backend.expired() )
    {
        auto p = std::make_shared< InternalManager >();
        s_backend = p;
        return p;
    }
    return s_backend.lock();
}

KPMManager::KPMManager()
    : m_d( getInternal() )
{
    cDebug() << "KPMManager" << s_backend.use_count() << "created.";
}

KPMManager::~KPMManager()
{
    cDebug() << "KPMManager" << s_backend.use_count() << "being destroyed.";
}

KPMManager::operator bool() const
{
    return s_kpm_loaded;
}

CoreBackend*
KPMManager::backend() const
{
    return s_kpm_loaded ? CoreBackendManager::self()->backend() : nullptr;
}


}  // namespace Partition
}  // namespace CalamaresUtils
