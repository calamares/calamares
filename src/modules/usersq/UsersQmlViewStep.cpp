/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
 *   Copyright 2020, Camilo Higuita <milo.h@aol.com>
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

#include "UsersQmlViewStep.h"

#include "SetHostNameJob.h"
#include "SetPasswordJob.h"

#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( UsersQmlViewStepFactory, registerPlugin< UsersQmlViewStep >(); )

UsersQmlViewStep::UsersQmlViewStep( QObject* parent )
: Calamares::QmlViewStep( parent )
, m_config( new Config(this) )
{
    connect( m_config, &Config::readyChanged, this, &UsersQmlViewStep::nextStatusChanged );

    emit nextStatusChanged( true );
}

QString
UsersQmlViewStep::prettyName() const
{
    return tr( "Users" );
}

bool
UsersQmlViewStep::isNextEnabled() const
{
    return m_config->isReady();
    //return true;
}


bool
UsersQmlViewStep::isBackEnabled() const
{
    return true;
}


bool
UsersQmlViewStep::isAtBeginning() const
{
    return true;
}


bool
UsersQmlViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
UsersQmlViewStep::jobs() const
{
    return m_jobs;
}


void
UsersQmlViewStep::onActivate()
{
    //m_config->onActivate();
    //QmlViewStep::onActivate();
}


void
UsersQmlViewStep::onLeave()
{
    m_jobs = m_config->createJobs();
    m_config->finalizeGlobalStorage();
}


void
UsersQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );

    Calamares::QmlViewStep::setConfigurationMap( configurationMap ); // call parent implementation last
    setContextProperty( "Users", m_config );
}
