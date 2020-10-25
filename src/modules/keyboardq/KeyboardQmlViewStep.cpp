/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "KeyboardQmlViewStep.h"

#include "Config.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( KeyboardQmlViewStepFactory, registerPlugin< KeyboardQmlViewStep >(); )

KeyboardQmlViewStep::KeyboardQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
    , m_nextEnabled( false )
{
    m_config->init();
    m_nextEnabled = true;
    emit nextStatusChanged( m_nextEnabled );
}

QString
KeyboardQmlViewStep::prettyName() const
{
    return tr( "Keyboard" );
}

QString
KeyboardQmlViewStep::prettyStatus() const
{
    return m_prettyStatus;
}

bool
KeyboardQmlViewStep::isNextEnabled() const
{
    return m_nextEnabled;
}

bool
KeyboardQmlViewStep::isBackEnabled() const
{
    return true;
}

bool
KeyboardQmlViewStep::isAtBeginning() const
{
    return true;
}

bool
KeyboardQmlViewStep::isAtEnd() const
{
    return true;
}

Calamares::JobList
KeyboardQmlViewStep::jobs() const
{
    return m_config->createJobs();
}

void
KeyboardQmlViewStep::onActivate()
{
    m_config->onActivate();
}

void
KeyboardQmlViewStep::onLeave()
{
    m_config->finalize();
    m_prettyStatus = m_config->prettyStatus();
}

QObject*
KeyboardQmlViewStep::getConfig()
{
    return m_config;
}

void
KeyboardQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{

    Calamares::QmlViewStep::setConfigurationMap( configurationMap );
}
