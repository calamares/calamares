/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "WelcomeQmlViewStep.h"

#include "checker/GeneralRequirements.h"

#include "locale/LabelModel.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "Branding.h"
#include "modulesystem/ModuleManager.h"
#include "utils/Yaml.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( WelcomeQmlViewStepFactory, registerPlugin< WelcomeQmlViewStep >(); )

WelcomeQmlViewStep::WelcomeQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
    , m_requirementsChecker( new GeneralRequirements( this ) )
{
    connect( Calamares::ModuleManager::instance(),
             &Calamares::ModuleManager::requirementsComplete,
             this,
             &WelcomeQmlViewStep::nextStatusChanged );
}


QString
WelcomeQmlViewStep::prettyName() const
{
    return tr( "Welcome" );
}

bool
WelcomeQmlViewStep::isNextEnabled() const
{
    return m_config->requirementsModel()->satisfiedMandatory();
}

bool
WelcomeQmlViewStep::isBackEnabled() const
{
    // TODO: should return true (it's weird that you are not allowed to have welcome *after* anything
    return false;
}


bool
WelcomeQmlViewStep::isAtBeginning() const
{
    // TODO: adjust to "pages" in the QML
    return true;
}


bool
WelcomeQmlViewStep::isAtEnd() const
{
    // TODO: adjust to "pages" in the QML
    return true;
}


Calamares::JobList
WelcomeQmlViewStep::jobs() const
{
    return Calamares::JobList();
}

void
WelcomeQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );

    if ( configurationMap.contains( "requirements" )
         && configurationMap.value( "requirements" ).type() == QVariant::Map )
    {
        m_requirementsChecker->setConfigurationMap( configurationMap.value( "requirements" ).toMap() );
    }
    else
    {
        cWarning() << "no valid requirements map found in welcomeq "
                      "module configuration.";
    }

    Calamares::QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
    setContextProperty( "Welcome", m_config );
}

Calamares::RequirementsList
WelcomeQmlViewStep::checkRequirements()
{
    return m_requirementsChecker->checkRequirements();
}

QObject*
WelcomeQmlViewStep::getConfig()
{
    return m_config;
}
