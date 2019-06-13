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

#include "KPMManager.h"

#include "utils/Logger.h"

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
static bool s_loaded = false;
static std::shared_ptr< InternalManager > s_backend;

InternalManager::InternalManager()
{
    Q_ASSERT( !s_loaded );
    s_loaded = true;
    s_backend.reset( this );

    cDebug() << "KPMCore backend starting ..";
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
            s_kpm_loaded = true;
        }
    }
}

InternalManager::~InternalManager()
{
    cDebug() << "Cleaning up KPMCore backend ..";

    s_loaded = false;

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

    if ( !s_loaded )
    {
        return std::make_shared< InternalManager >();
    }
    return s_backend;
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


}  // namespace Partition
}  // namespace CalamaresUtils
