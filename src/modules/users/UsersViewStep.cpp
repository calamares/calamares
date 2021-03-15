/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "UsersViewStep.h"

#include "Config.h"
#include "UsersPage.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( UsersViewStepFactory, registerPlugin< UsersViewStep >(); )

UsersViewStep::UsersViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( nullptr )
    , m_config( new Config( this ) )
{
    connect( m_config, &Config::readyChanged, this, &UsersViewStep::nextStatusChanged );

    emit nextStatusChanged( m_config->isReady() );
}


UsersViewStep::~UsersViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
UsersViewStep::prettyName() const
{
    return tr( "Users" );
}


QWidget*
UsersViewStep::widget()
{
    if ( !m_widget )
    {
        m_widget = new UsersPage( m_config );
    }
    return m_widget;
}


bool
UsersViewStep::isNextEnabled() const
{
    return m_config->isReady();
}


bool
UsersViewStep::isBackEnabled() const
{
    return true;
}


bool
UsersViewStep::isAtBeginning() const
{
    return true;
}


bool
UsersViewStep::isAtEnd() const
{
    return true;
}


Calamares::JobList
UsersViewStep::jobs() const
{
    return m_config->createJobs();
}


void
UsersViewStep::onActivate()
{
    if ( m_widget )
    {
        m_widget->onActivate();
    }
}


void
UsersViewStep::onLeave()
{
    m_config->finalizeGlobalStorage();
}


void
UsersViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
}
