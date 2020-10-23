/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "KeyboardViewStep.h"

#include "Config.h"
#include "KeyboardPage.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( KeyboardViewStepFactory, registerPlugin< KeyboardViewStep >(); )

KeyboardViewStep::KeyboardViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_config( new Config(this) )
    , m_widget( new KeyboardPage() )
    , m_nextEnabled( false )
{
    m_widget->init();
    m_nextEnabled = true;
    emit nextStatusChanged( m_nextEnabled );
}


KeyboardViewStep::~KeyboardViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
KeyboardViewStep::prettyName() const
{
    return tr( "Keyboard" );
}


QString
KeyboardViewStep::prettyStatus() const
{
    return m_prettyStatus;
}


QWidget*
KeyboardViewStep::widget()
{
    return m_widget;
}


bool
KeyboardViewStep::isNextEnabled() const
{
    return m_nextEnabled;
}


bool
KeyboardViewStep::isBackEnabled() const
{
    return true;
}


bool
KeyboardViewStep::isAtBeginning() const
{
    return true;
}


bool
KeyboardViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
KeyboardViewStep::jobs() const
{
    return m_config->createJobs();
}


void
KeyboardViewStep::onActivate()
{
    m_widget->onActivate();
}


void
KeyboardViewStep::onLeave()
{
    m_widget->finalize();
    m_prettyStatus = m_widget->prettyStatus();
}


void
KeyboardViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap(configurationMap);
}
