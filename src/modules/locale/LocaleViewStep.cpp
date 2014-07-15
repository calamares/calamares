/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
#include "QtWaitingSpinner.h"
#include "timezonewidget/localeglobal.h"

#include "utils/CalamaresUtilsGui.h"

#include <QBoxLayout>
#include <QLabel>
#include <QtConcurrent/QtConcurrentRun>

LocaleViewStep::LocaleViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QWidget() )
    , m_actualWidget( new LocalePage() )
    , m_nextEnabled( false )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    m_widget->setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    QWidget* waitingWidget = new QWidget;
    {
        QBoxLayout* waitingLayout = new QVBoxLayout;
        waitingWidget->setLayout( waitingLayout );
        waitingLayout->addStretch();
        QBoxLayout* pbLayout = new QHBoxLayout;
        waitingLayout->addLayout( pbLayout );
        pbLayout->addStretch();

        QtWaitingSpinner* spnr = new QtWaitingSpinner();
        pbLayout->addWidget( spnr );

        pbLayout->addStretch();

        QLabel* waitingLabel = new QLabel( "Loading location data..." );

        int spnrSize = waitingLabel->fontMetrics().height() * 4;
        spnr->setFixedSize( spnrSize, spnrSize );
        spnr->setRadius( spnrSize / 2 );
        spnr->setLength( spnrSize / 2 );
        spnr->setWidth( spnrSize / 8 );
        spnr->start();

        waitingLabel->setAlignment( Qt::AlignCenter);
        waitingLayout->addSpacing( spnrSize / 2 );
        waitingLayout->addWidget( waitingLabel );
        waitingLayout->addStretch();

        mainLayout->addWidget( waitingWidget );

        CalamaresUtils::unmarginLayout( waitingLayout );
    }

    connect( &m_initWatcher, &QFutureWatcher< void >::finished,
             [=]
    {
        m_actualWidget->init( m_startingTimezone.first, m_startingTimezone.second );
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
    //TODO: actually save those settings somewhere
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
    return QList< Calamares::job_ptr >();
}


void
LocaleViewStep::onLeave()
{
    m_prettyStatus = m_actualWidget->prettyStatus();
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
}
