/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    , m_config( new Config( this ) )
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

    Calamares::QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
    setContextProperty( "Users", m_config );
}
