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
#include "timezonewidget/localeglobal.h"
#include "widgets/WaitingWidget.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "geoip/Handler.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

#include <QBoxLayout>
#include <QLabel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtConcurrent/QtConcurrentRun>


CALAMARES_PLUGIN_FACTORY_DEFINITION( LocaleViewStepFactory, registerPlugin<LocaleViewStep>(); )

LocaleViewStep::LocaleViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QWidget() )
    , m_actualWidget( new LocalePage() )
    , m_nextEnabled( false )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    m_widget->setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    m_waitingWidget = new WaitingWidget( tr( "Loading location data..." ) );
    mainLayout->addWidget( m_waitingWidget );

    connect( &m_initWatcher, &QFutureWatcher< void >::finished,
             this, [=]
    {
        bool hasInternet = Calamares::JobQueue::instance()->globalStorage()
                           ->value( "hasInternet" ).toBool();
        if ( m_geoipUrl.isEmpty() || !hasInternet )
            setUpPage();
        else
            fetchGeoIpTimezone();
    });

    QFuture< void > initFuture = QtConcurrent::run( [=]
    {
        LocaleGlobal::init();
        if ( m_geoipUrl.isEmpty() )
            return;

        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

        // Max 10sec wait for RequirementsChecker to finish, assuming the welcome
        // module is used.
        // If welcome is not used, either "hasInternet" should be set by other means,
        // or the GeoIP feature should be disabled.
        for ( int i = 0; i < 10; ++i )
            if ( !gs->contains( "hasInternet" ) )
                QThread::sleep( 1 );
    } );

    m_initWatcher.setFuture( initFuture );

    emit nextStatusChanged( m_nextEnabled );
}


LocaleViewStep::~LocaleViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


void
LocaleViewStep::setUpPage()
{
    m_actualWidget->init( m_startingTimezone.first,
                          m_startingTimezone.second,
                          m_localeGenPath );
    m_widget->layout()->removeWidget( m_waitingWidget );
    m_waitingWidget->deleteLater();
    m_widget->layout()->addWidget( m_actualWidget );
    m_nextEnabled = true;
    emit nextStatusChanged( m_nextEnabled );
}


void
LocaleViewStep::fetchGeoIpTimezone()
{
    CalamaresUtils::GeoIP::Handler h( m_geoipStyle, m_geoipUrl, m_geoipSelector );
    if ( h.isValid() )
    {
        m_startingTimezone = h.get();
        if ( !m_startingTimezone.isValid() )
            cWarning() << "GeoIP lookup at" << m_geoipUrl << "failed.";
    }
    else
        cWarning() << "GeoIP Style" << m_geoipStyle << "is not recognized.";
    setUpPage();
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


QList< Calamares::job_ptr >
LocaleViewStep::jobs() const
{
    return m_jobs;
}


void
LocaleViewStep::onActivate()
{
    m_actualWidget->onActivate();
}


void
LocaleViewStep::onLeave()
{
    m_jobs.clear();
    m_jobs.append( m_actualWidget->createJobs() );

    m_prettyStatus = m_actualWidget->prettyStatus();

    auto map = m_actualWidget->localesMap();
    QVariantMap vm;
    for ( auto it = map.constBegin(); it != map.constEnd(); ++it )
        vm.insert( it.key(), it.value() );

    Calamares::JobQueue::instance()->globalStorage()
            ->insert( "localeConf", vm );
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
        m_startingTimezone = CalamaresUtils::GeoIP::RegionZonePair( QStringLiteral( "America" ), QStringLiteral( "New_York" ) );
    }

    m_localeGenPath = CalamaresUtils::getString( configurationMap, "localeGenPath" );
    if ( m_localeGenPath.isEmpty() )
        m_localeGenPath = QStringLiteral( "/etc/locale.gen" );

    bool ok = false;
    QVariantMap geoip = CalamaresUtils::getSubMap( configurationMap, "geoip", ok );
    if ( ok )
    {
        m_geoipUrl = CalamaresUtils::getString( geoip, "url" );
        m_geoipStyle = CalamaresUtils::getString( geoip, "style" );
        m_geoipSelector = CalamaresUtils::getString( geoip, "selector" );
    }
    else
    {
        // Optional
        m_geoipUrl = CalamaresUtils::getString( configurationMap, "geoipUrl" );
        m_geoipStyle = CalamaresUtils::getString( configurationMap, "geoipStyle" );
        m_geoipSelector = CalamaresUtils::getString( configurationMap, "geoipSelector" );

        if ( !m_geoipUrl.isEmpty() && ( m_geoipStyle.isEmpty() || m_geoipStyle == "legacy" ) )
        {
            m_geoipStyle = "json";
            m_geoipUrl.append( "/json/" );
        }

        if ( !m_geoipUrl.isEmpty() )
            cWarning() << "Legacy-style GeoIP configuration is deprecated. Use geoip: map.";
    }
}
