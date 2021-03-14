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

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

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

Calamares::JobList
UsersQmlViewStep::jobs() const
{
    return m_config->createJobs();
}

void
UsersQmlViewStep::onLeave()
{
    m_config->finalizeGlobalStorage();
}

void
UsersQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
    Calamares::QmlViewStep::setConfigurationMap( configurationMap );  // call parent implementation last
}
