/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

#include "UsersViewStep.h"

#include "Config.h"
#include "CreateUserJob.h"
#include "SetHostNameJob.h"
#include "SetPasswordJob.h"
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
    emit nextStatusChanged( true );
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
        connect( m_widget, &UsersPage::checkReady, this, &UsersViewStep::nextStatusChanged );
    }
    return m_widget;
}


bool
UsersViewStep::isNextEnabled() const
{
    return m_widget ? m_widget->isReady() : true;
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


QList< Calamares::job_ptr >
UsersViewStep::jobs() const
{
    return m_jobs;
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
    m_jobs.clear();
    if ( !m_widget || !m_widget->isReady() )
    {
        return;
    }

    Calamares::Job* j;
    // TODO: Config object should create jobs, like this one, that depend only on config values
    j = new CreateUserJob( m_config->loginName(),
                           m_config->fullName().isEmpty() ? m_config->loginName() : m_config->fullName(),
                           m_config->doAutoLogin(),
                           m_config->defaultGroups() );
    m_jobs.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( m_config->loginName(), m_config->userPassword() );
    m_jobs.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( "root", m_config->rootPassword() );
    m_jobs.append( Calamares::job_ptr( j ) );

    // TODO: Config object should create jobs
    j = new SetHostNameJob( m_config->hostName(), m_config->hostNameActions() );
    m_jobs.append( Calamares::job_ptr( j ) );

    m_widget->fillGlobalStorage();
}


void
UsersViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
}
