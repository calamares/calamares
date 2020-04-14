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

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "geoip/Handler.h"
#include "network/Manager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

#include "Branding.h"
#include "modulesystem/ModuleManager.h"
#include <QQmlEngine>
#include <QFutureWatcher>
#include <QPixmap>
#include <QVariant>

CALAMARES_PLUGIN_FACTORY_DEFINITION( LocaleQmlViewStepFactory, registerPlugin< LocaleQmlViewStep >(); )

LocaleQmlViewStep::LocaleQmlViewStep( QObject* parent )
: Calamares::QmlViewStep( parent )
, m_config( new Config( this ) )
, m_nextEnabled( false )
, m_geoip( nullptr )
{
    emit nextStatusChanged( m_nextEnabled );
}

QObject*
LocaleQmlViewStep::getConfig()
{
    return m_config;
}

void
LocaleQmlViewStep::fetchGeoIpTimezone()
{
    if ( m_geoip && m_geoip->isValid() )
    {
        m_startingTimezone = m_geoip->get();
        if ( !m_startingTimezone.isValid() )
        {
            cWarning() << "GeoIP lookup at" << m_geoip->url() << "failed.";
        }
    }

    m_config->setLocaleInfo(m_startingTimezone.first, m_startingTimezone.second, m_localeGenPath);
}

Calamares::RequirementsList LocaleQmlViewStep::checkRequirements()
{
    if ( m_geoip && m_geoip->isValid() )
    {
        auto& network = CalamaresUtils::Network::Manager::instance();
        if ( network.hasInternet() )
        {
            fetchGeoIpTimezone();
        }
        else
        {
            if ( network.synchronousPing( m_geoip->url() ) )
            {
                fetchGeoIpTimezone();
            }
        }
    }

    return Calamares::RequirementsList();
}

QString
LocaleQmlViewStep::prettyName() const
{
    return tr( "Location" );
}

bool
LocaleQmlViewStep::isNextEnabled() const
{
    // TODO: should return true
    return true;
}

bool
LocaleQmlViewStep::isBackEnabled() const
{
    // TODO: should return true (it's weird that you are not allowed to have welcome *after* anything
    return true;
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
    return m_jobs;
}

void LocaleQmlViewStep::onActivate()
{
    // TODO no sure if it is needed at all or for the abstract class to start something
}

void LocaleQmlViewStep::onLeave()
{
    if ( true )
    {
        m_jobs = m_config->createJobs();
//         m_prettyStatus = m_actualWidget->prettyStatus();

        auto map = m_config->localesMap();
        QVariantMap vm;
        for ( auto it = map.constBegin(); it != map.constEnd(); ++it )
        {
            vm.insert( it.key(), it.value() );
        }

        Calamares::JobQueue::instance()->globalStorage()->insert( "localeConf", vm );
    }
    else
    {
        m_jobs.clear();
        Calamares::JobQueue::instance()->globalStorage()->remove( "localeConf" );
    }
}

void LocaleQmlViewStep::setConfigurationMap(const QVariantMap& configurationMap)
{
    QString region = CalamaresUtils::getString( configurationMap, "region" );
    QString zone = CalamaresUtils::getString( configurationMap, "zone" );
    if ( !region.isEmpty() && !zone.isEmpty() )
    {
        m_startingTimezone = CalamaresUtils::GeoIP::RegionZonePair( region, zone );
    }
    else
    {
        m_startingTimezone
        = CalamaresUtils::GeoIP::RegionZonePair( QStringLiteral( "America" ), QStringLiteral( "New_York" ) );
    }

    m_localeGenPath = CalamaresUtils::getString( configurationMap, "localeGenPath" );
    if ( m_localeGenPath.isEmpty() )
    {
        m_localeGenPath = QStringLiteral( "/etc/locale.gen" );
    }

    bool ok = false;
    QVariantMap geoip = CalamaresUtils::getSubMap( configurationMap, "geoip", ok );
    if ( ok )
    {
        QString url = CalamaresUtils::getString( geoip, "url" );
        QString style = CalamaresUtils::getString( geoip, "style" );
        QString selector = CalamaresUtils::getString( geoip, "selector" );

        m_geoip = std::make_unique< CalamaresUtils::GeoIP::Handler >( style, url, selector );
        if ( !m_geoip->isValid() )
        {
            cWarning() << "GeoIP Style" << style << "is not recognized.";
        }
    }

    checkRequirements();
    Calamares::QmlViewStep::setConfigurationMap( configurationMap ); // call parent implementation last
}
