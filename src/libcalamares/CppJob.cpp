/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CppJob.h"

namespace Calamares
{

CppJob::CppJob( QObject* parent )
    : Job( parent )
{
}


CppJob::~CppJob() {}


void
CppJob::setModuleInstanceKey( const Calamares::ModuleSystem::InstanceKey& instanceKey )
{
    m_instanceKey = instanceKey;
}


void
CppJob::setConfigurationMap( const QVariantMap& configurationMap )
{
    Q_UNUSED( configurationMap )
}

}  // namespace Calamares
