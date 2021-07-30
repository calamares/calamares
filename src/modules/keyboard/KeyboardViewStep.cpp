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
    , m_config( new Config( this ) )
    , m_widget( new KeyboardPage( m_config ) )
{
    m_config->detectCurrentKeyboardLayout();
    emit nextStatusChanged( true );
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
    return m_config->prettyStatus();
}


QWidget*
KeyboardViewStep::widget()
{
    return m_widget;
}


bool
KeyboardViewStep::isNextEnabled() const
{
    return true;
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
    m_config->guessLocaleKeyboardLayout();
}


void
KeyboardViewStep::onLeave()
{
    m_config->finalize();
}


void
KeyboardViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );
}
