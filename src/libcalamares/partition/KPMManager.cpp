/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "KPMManager.h"

#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/util/externalcommand.h>

#include <QObject>


namespace CalamaresUtils
{
namespace Partition
{
class InternalManager
{
public:
    InternalManager();
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
            cDebug() << Logger::SubEntry << "Backend" << Logger::Pointer( backend_p ) << backend_p->id()
                     << backend_p->version();
            s_kpm_loaded = true;
        }
    }
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
}

KPMManager::~KPMManager() {}

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
