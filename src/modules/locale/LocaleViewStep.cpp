/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include <QBoxLayout>
#include <QLabel>
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

    WaitingWidget* waitingWidget =
        new WaitingWidget( tr( "Loading location data..." ) );

    mainLayout->addWidget( waitingWidget );

    connect( &m_initWatcher, &QFutureWatcher< void >::finished,
             [=]
    {
        m_actualWidget->init( m_startingTimezone.first,
                              m_startingTimezone.second,
                              m_localeGenPath );
        m_widget->layout()->removeWidget( waitingWidget );
        waitingWidget->deleteLater();
        m_widget->layout()->addWidget( m_actualWidget );
        m_nextEnabled = true;
        emit nextStatusChanged( m_nextEnabled );
    });

    QFuture< void > initFuture = QtConcurrent::run( LocaleGlobal::init );
    m_initWatcher.setFuture( initFuture );

    emit nextStatusChanged( m_nextEnabled );
}


LocaleViewStep::~LocaleViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
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

    Calamares::JobQueue::instance()->globalStorage()->insert( "lcLocale",
                                                              m_actualWidget->lcLocale() );
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
        m_startingTimezone = qMakePair( QStringLiteral( "Europe" ),
                                        QStringLiteral( "Berlin" ) );
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
}
