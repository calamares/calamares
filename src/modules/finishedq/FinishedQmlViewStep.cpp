/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "FinishedQmlViewStep.h"

#include "Config.h"

#include "JobQueue.h"
#include <QApplication>

CALAMARES_PLUGIN_FACTORY_DEFINITION( FinishedQmlViewStepFactory, registerPlugin< FinishedQmlViewStep >(); )

FinishedQmlViewStep::FinishedQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
{
    auto jq = Calamares::JobQueue::instance();
    connect( jq, &Calamares::JobQueue::failed, m_config, &Config::onInstallationFailed );

    emit nextStatusChanged( true );
}

QString
FinishedQmlViewStep::prettyName() const
{
    return tr( "Finish" );
}

bool
FinishedQmlViewStep::isNextEnabled() const
{
    return false;
}


bool
FinishedQmlViewStep::isBackEnabled() const
{
    return false;
}


bool
FinishedQmlViewStep::isAtBeginning() const
{
    return true;
}


bool
FinishedQmlViewStep::isAtEnd() const
{
    return true;
}


void
FinishedQmlViewStep::onActivate()
{
    m_config->doNotify();
    connect( qApp, &QApplication::aboutToQuit, m_config, qOverload<>( &Config::doRestart ) );
    QmlViewStep::onActivate();
}


Calamares::JobList
FinishedQmlViewStep::jobs() const
{
    return Calamares::JobList();
}

QObject*
FinishedQmlViewStep::getConfig()
{
    return m_config;
}

void
FinishedQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
    Calamares::QmlViewStep::setConfigurationMap( configurationMap );
}
