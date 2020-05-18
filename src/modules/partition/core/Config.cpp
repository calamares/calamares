/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Variant.h"

Config::Config( QObject* parent )
    : QObject( parent )
{
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    // Settings that overlap with the Welcome module
    m_requiredStorageGiB = CalamaresUtils::getDouble( configurationMap, "requiredStorage", -1.0 );
}

void
Config::updateGlobalStorage() const
{
    // If there's no setting (e.g. from the welcome page) for required storage
    // then use ours, if it was set.
    auto* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( m_requiredStorageGiB >= 0.0 && gs && !gs->contains( "requiredStorageGiB" ) )
    {
        gs->insert( "requiredStorageGiB", m_requiredStorageGiB );
    }
}
