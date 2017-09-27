/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/YamlUtils.h"

#include <QBoxLayout>
#include <QLabel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtConcurrent/QtConcurrentRun>

#include <yaml-cpp/yaml.h>


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
    QNetworkAccessManager *manager = new QNetworkAccessManager( this );
    connect( manager, &QNetworkAccessManager::finished,
            [=]( QNetworkReply* reply )
    {
        if ( reply->error() == QNetworkReply::NoError )
        {
            QByteArray data = reply->readAll();

            try
            {
                YAML::Node doc = YAML::Load( reply->readAll() );

                QVariant var = CalamaresUtils::yamlToVariant( doc );
                if ( !var.isNull() &&
                    var.isValid() &&
                    var.type() == QVariant::Map )
                {
                    QVariantMap map = var.toMap();
                    if ( map.contains( "time_zone" ) &&
                        !map.value( "time_zone" ).toString().isEmpty() )
                    {
                        QString timezoneString = map.value( "time_zone" ).toString();
                        QStringList tzParts = timezoneString.split( '/', QString::SkipEmptyParts );
                        if ( tzParts.size() >= 2 )
                        {
                            cDebug() << "GeoIP reporting" << timezoneString;
                            QString region = tzParts.takeFirst();
                            QString zone = tzParts.join( '/' );
                            m_startingTimezone = qMakePair( region, zone );
                        }
                    }
                }
            }
            catch ( YAML::Exception& e )
            {
                CalamaresUtils::explainYamlException( e, data, "GeoIP data");
            }
        }

        reply->deleteLater();
        manager->deleteLater();
        setUpPage();
    } );

    QNetworkRequest request;
    QString requestUrl = QString( "%1/json" )
                         .arg( QUrl::fromUserInput( m_geoipUrl ).toString() );
    request.setUrl( QUrl( requestUrl ) );
    request.setAttribute( QNetworkRequest::FollowRedirectsAttribute, true );
    manager->get( request );
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


void
LocaleViewStep::next()
{
    emit done();
}


void
LocaleViewStep::back()
{}


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
    if ( configurationMap.contains( "region" ) &&
         configurationMap.value( "region" ).type() == QVariant::String &&
         !configurationMap.value( "region" ).toString().isEmpty() &&
         configurationMap.contains( "zone" ) &&
         configurationMap.value( "zone" ).type() == QVariant::String &&
         !configurationMap.value( "zone" ).toString().isEmpty() )
    {
        m_startingTimezone = qMakePair( configurationMap.value( "region" ).toString(),
                                        configurationMap.value( "zone" ).toString() );
    }
    else
    {
        m_startingTimezone = qMakePair( QStringLiteral( "America" ),
                                        QStringLiteral( "New_York" ) );
    }

    if ( configurationMap.contains( "localeGenPath" ) &&
         configurationMap.value( "localeGenPath" ).type() == QVariant::String &&
         !configurationMap.value( "localeGenPath" ).toString().isEmpty() )
    {
        m_localeGenPath = configurationMap.value( "localeGenPath" ).toString();
    }
    else
    {
        m_localeGenPath = QStringLiteral( "/etc/locale.gen" );
    }

    // Optional
    if ( configurationMap.contains( "geoipUrl" ) &&
         configurationMap.value( "geoipUrl" ).type() == QVariant::String &&
         !configurationMap.value( "geoipUrl" ).toString().isEmpty() )
    {
        m_geoipUrl = configurationMap.value( "geoipUrl" ).toString();
    }
}
