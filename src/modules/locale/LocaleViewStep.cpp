/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "LocaleViewStep.h"

#include "LocalePage.h"

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
