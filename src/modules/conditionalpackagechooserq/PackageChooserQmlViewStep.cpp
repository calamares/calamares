/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2021 shivanandvp <shivanandvp@rebornos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PackageChooserQmlViewStep.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"
#include "Config.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( PackageChooserQmlViewStepFactory, registerPlugin< PackageChooserQmlViewStep >(); )

PackageChooserQmlViewStep::PackageChooserQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
    , m_stepName( nullptr )
{
    emit nextStatusChanged( false );
    connect( m_config, &Config::nextStatusChanged, this, &PackageChooserQmlViewStep::nextStatusChanged );
}

void PackageChooserQmlViewStep::onActivate() {
    m_config->refreshQMLData();
}

QString
PackageChooserQmlViewStep::prettyName() const
{
    return m_stepName ? m_stepName->get() : tr( "Packages" );
}

QString
PackageChooserQmlViewStep::prettyStatus() const
{
    //QString option = m_pkgc;
    //return tr( "Install option: %1" ).arg( option );
    return m_config->prettyStatus();
}

bool
PackageChooserQmlViewStep::isNextEnabled() const
{
    return m_config -> refreshNextButtonStatus();
}

bool
PackageChooserQmlViewStep::isBackEnabled() const
{
    return true;
}

bool
PackageChooserQmlViewStep::isAtBeginning() const
{
    return true;
}

bool
PackageChooserQmlViewStep::isAtEnd() const
{
    return true;
}

Calamares::JobList
PackageChooserQmlViewStep::jobs() const
{
    Calamares::JobList l;
    return l;
}

void
PackageChooserQmlViewStep::onLeave()
{
    m_config->updateGlobalStorage();
}

void
PackageChooserQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setDefaultId( moduleInstanceKey() );
    m_config->setConfigurationMap( configurationMap );

    bool labels_ok = false;
    auto labels = CalamaresUtils::getSubMap( configurationMap, "labels", labels_ok );
    if ( labels_ok )
    {
        if ( labels.contains( "step" ) )
        {
            m_stepName = new CalamaresUtils::Locale::TranslatedString( labels, "step" );
        }
    }

    Calamares::QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
}

