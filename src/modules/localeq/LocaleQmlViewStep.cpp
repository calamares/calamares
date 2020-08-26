/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 20182020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
