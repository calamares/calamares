/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <PartitionCoreModule.h>

#include <DeviceModel.h>

// CalaPM
#include <CalaPM.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>

PartitionCoreModule::PartitionCoreModule( QObject* parent )
    : QObject( parent )
    , m_deviceModel( new DeviceModel( this ) )
{
    // FIXME: Should be done at startup
    if ( !CalaPM::init() )
    {
        qFatal( "Failed to init CalaPM" );
    }
    CoreBackend* backend = CoreBackendManager::self()->backend();
    m_devices = backend->scanDevices();

    m_deviceModel->init( m_devices );
}

QList< Device* >
PartitionCoreModule::devices() const
{
    return m_devices;
}

DeviceModel*
PartitionCoreModule::deviceModel() const
{
    return m_deviceModel;
}
