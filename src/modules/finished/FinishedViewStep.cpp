/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "FinishedViewStep.h"

#include "Config.h"
#include "FinishedPage.h"

#include "JobQueue.h"

#include <QApplication>

FinishedViewStep::FinishedViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_config( new Config( this ) )
    , m_widget( new FinishedPage( m_config ) )
{
    auto jq = Calamares::JobQueue::instance();
    connect( jq, &Calamares::JobQueue::failed, m_config, &Config::onInstallationFailed );
    connect( jq, &Calamares::JobQueue::failed, m_widget, &FinishedPage::onInstallationFailed );

    emit nextStatusChanged( true );
}


FinishedViewStep::~FinishedViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
FinishedViewStep::prettyName() const
{
    return tr( "Finish" );
}


QWidget*
FinishedViewStep::widget()
{
    return m_widget;
}


bool
FinishedViewStep::isNextEnabled() const
{
    return false;
}


bool
FinishedViewStep::isBackEnabled() const
{
    return false;
}


bool
FinishedViewStep::isAtBeginning() const
{
    return true;
}


bool
FinishedViewStep::isAtEnd() const
{
    return true;
}


void
FinishedViewStep::onActivate()
{
    m_config->doNotify();
    connect( qApp, &QApplication::aboutToQuit, m_config, qOverload<>( &Config::doRestart ) );
}


Calamares::JobList
FinishedViewStep::jobs() const
{
    return Calamares::JobList();
}

void
FinishedViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( FinishedViewStepFactory, registerPlugin< FinishedViewStep >(); )
