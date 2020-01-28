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

#include "geoip/Handler.h"
#include "locale/LabelModel.h"
#include "locale/Lookup.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "Branding.h"
#include "modulesystem/ModuleManager.h"

#include <QFutureWatcher>
#include <QPixmap>
#include <QVariant>

CALAMARES_PLUGIN_FACTORY_DEFINITION( LocaleQmlViewStepFactory, registerPlugin< LocaleQmlViewStep >(); )


LocaleQmlViewStep::LocaleQmlViewStep( QObject* parent )
: Calamares::ViewStep( parent )
, m_config( new Config( m_startingTimezone.first, m_startingTimezone.second, m_localeGenPath, this ) )
, m_nextEnabled( false )
, m_geoip( nullptr )
{
    emit nextStatusChanged( m_nextEnabled );
}

Config*
LocaleQmlViewStep::config() const
{
    return m_config;
}

QString
LocaleQmlViewStep::prettyName() const
{
    return tr( "Location" );
}


QWidget*
LocaleQmlViewStep::widget()
{
    return nullptr;
}

bool
LocaleQmlViewStep::isNextEnabled() const
{
    // TODO: should return true
    return false;
}


bool
LocaleQmlViewStep::isBackEnabled() const
{
    // TODO: should return true (it's weird that you are not allowed to have welcome *after* anything
    return false;
}


bool
LocaleQmlViewStep::isAtBeginning() const
{
    // TODO: adjust to "pages" in the QML
    return true;
}


bool
LocaleQmlViewStep::isAtEnd() const
{
    // TODO: adjust to "pages" in the QML
    return true;
}

Calamares::JobList
LocaleQmlViewStep::jobs() const
{
    return Calamares::JobList();
}

void LocaleQmlViewStep::setConfigurationMap(const QVariantMap& configurationMap)
{
    using Calamares::Branding;

}


