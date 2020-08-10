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


CALAMARES_PLUGIN_FACTORY_DEFINITION( LocaleViewStepFactory, registerPlugin< LocaleViewStep >(); )

LocaleViewStep::LocaleViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QWidget() )
    , m_actualWidget( nullptr )
    , m_nextEnabled( false )
    , m_config( std::make_unique< Config >() )
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
    m_config->setCurrentLocation();
    if ( !m_actualWidget )
    {
        m_actualWidget = new LocalePage( m_config.get() );
    }
    m_widget->layout()->addWidget( m_actualWidget );

    ensureSize( m_actualWidget->sizeHint() );

    m_nextEnabled = true;
    emit nextStatusChanged( m_nextEnabled );
}


QString
LocaleViewStep::prettyName() const
{
    return tr( "Location" );
}


QString
LocaleViewStep::prettyStatus() const
{
    return m_config->prettyStatus();
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
    return m_config->createJobs();
}


void
LocaleViewStep::onActivate()
{
    m_config->setCurrentLocation();  // Finalize the location
    if ( !m_actualWidget )
    {
        setUpPage();
    }
    m_actualWidget->onActivate();
}


void
LocaleViewStep::onLeave()
{
    m_config->finalizeGlobalStorage();
}


void
LocaleViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
}
