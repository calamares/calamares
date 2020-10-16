/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot.org>
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

#include "LocaleViewStep.h"

#include "LocalePage.h"
#include "widgets/WaitingWidget.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "geoip/Handler.h"
#include "network/Manager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

#include <QBoxLayout>
#include <QLabel>
#include <QtConcurrent/QtConcurrentRun>


CALAMARES_PLUGIN_FACTORY_DEFINITION( LocaleViewStepFactory, registerPlugin< LocaleViewStep >(); )

LocaleViewStep::LocaleViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QWidget() )
    , m_actualWidget( nullptr )
    , m_nextEnabled( false )
    , m_geoip( nullptr )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    m_widget->setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    emit nextStatusChanged( m_nextEnabled );
}


LocaleViewStep::~LocaleViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


void
LocaleViewStep::setUpPage()
{
    if ( !m_actualWidget )
    {
        m_actualWidget = new LocalePage();
    }
    m_actualWidget->init( m_startingTimezone.first, m_startingTimezone.second, m_localeGenPath );
    m_widget->layout()->addWidget( m_actualWidget );

    ensureSize( m_actualWidget->sizeHint() );

    m_nextEnabled = true;
    emit nextStatusChanged( m_nextEnabled );
}


void
LocaleViewStep::fetchGeoIpTimezone()
{
    if ( m_geoip && m_geoip->isValid() )
    {
        m_startingTimezone = m_geoip->get();
        if ( !m_startingTimezone.isValid() )
        {
            cWarning() << "GeoIP lookup at" << m_geoip->url() << "failed.";
        }
    }
}


QString
LocaleViewStep::prettyName() const
{
    return tr( "Location" );
}


QString
LocaleViewStep::prettyStatus() const
{
    return m_prettyStatus;
}


QWidget*
LocaleViewStep::widget()
{
    return m_widget;
}


bool
LocaleViewStep::isNextEnabled() const
{
    return m_nextEnabled;
}


bool
LocaleViewStep::isBackEnabled() const
{
    return true;
}


bool
LocaleViewStep::isAtBeginning() const
{
    return true;
}


bool
LocaleViewStep::isAtEnd() const
{
    return true;
}


Calamares::JobList
LocaleViewStep::jobs() const
{
    return m_jobs;
}


void
LocaleViewStep::onActivate()
{
    if ( !m_actualWidget )
    {
        setUpPage();
    }
    m_actualWidget->onActivate();
}


void
LocaleViewStep::onLeave()
{
    if ( m_actualWidget )
    {
        m_jobs = m_actualWidget->createJobs();
        m_prettyStatus = m_actualWidget->prettyStatus();

        auto map = m_actualWidget->localesMap();
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


void
LocaleViewStep::setConfigurationMap( const QVariantMap& configurationMap )
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
}

Calamares::RequirementsList
LocaleViewStep::checkRequirements()
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
