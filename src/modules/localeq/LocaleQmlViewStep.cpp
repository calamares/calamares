/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018,2020 Adriaan de Groot <groot@kde.org>
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

#include "LocaleQmlViewStep.h"

#include "utils/Logger.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( LocaleQmlViewStepFactory, registerPlugin< LocaleQmlViewStep >(); )

LocaleQmlViewStep::LocaleQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( std::make_unique< Config >( this ) )
{
}

QObject*
LocaleQmlViewStep::getConfig()
{
    return m_config.get();
}

QString
LocaleQmlViewStep::prettyName() const
{
    return tr( "Location" );
}

QString
LocaleQmlViewStep::prettyStatus() const
{
    return m_config->prettyStatus();
}

bool
LocaleQmlViewStep::isNextEnabled() const
{
    return true;
}

bool
LocaleQmlViewStep::isBackEnabled() const
{
    return true;
}


bool
LocaleQmlViewStep::isAtBeginning() const
{
    return true;
}


bool
LocaleQmlViewStep::isAtEnd() const
{
    return true;
}

Calamares::JobList
LocaleQmlViewStep::jobs() const
{
    return m_config->createJobs();
}

void
LocaleQmlViewStep::onActivate()
{
    m_config->setCurrentLocation();  // Finalize the location
    QmlViewStep::onActivate();
}

void
LocaleQmlViewStep::onLeave()
{
    m_config->finalizeGlobalStorage();
}

void
LocaleQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
    QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
}
