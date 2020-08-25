/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "KeyboardViewStep.h"

#include "KeyboardPage.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/Variant.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( KeyboardViewStepFactory, registerPlugin< KeyboardViewStep >(); )

KeyboardViewStep::KeyboardViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new KeyboardPage() )
    , m_nextEnabled( false )
    , m_writeEtcDefaultKeyboard( true )
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
    return m_jobs;
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
    m_jobs = m_widget->createJobs( m_xOrgConfFileName, m_convertedKeymapPath, m_writeEtcDefaultKeyboard );
    m_prettyStatus = m_widget->prettyStatus();
}


void
KeyboardViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    using namespace CalamaresUtils;

    if ( configurationMap.contains( "xOrgConfFileName" )
         && configurationMap.value( "xOrgConfFileName" ).type() == QVariant::String
         && !getString( configurationMap, "xOrgConfFileName" ).isEmpty() )
    {
        m_xOrgConfFileName = getString( configurationMap, "xOrgConfFileName" );
    }
    else
    {
        m_xOrgConfFileName = "00-keyboard.conf";
    }

    if ( configurationMap.contains( "convertedKeymapPath" )
         && configurationMap.value( "convertedKeymapPath" ).type() == QVariant::String
         && !getString( configurationMap, "convertedKeymapPath" ).isEmpty() )
    {
        m_convertedKeymapPath = getString( configurationMap, "convertedKeymapPath" );
    }
    else
    {
        m_convertedKeymapPath = QString();
    }

    if ( configurationMap.contains( "writeEtcDefaultKeyboard" )
         && configurationMap.value( "writeEtcDefaultKeyboard" ).type() == QVariant::Bool )
    {
        m_writeEtcDefaultKeyboard = getBool( configurationMap, "writeEtcDefaultKeyboard", true );
    }
    else
    {
        m_writeEtcDefaultKeyboard = true;
    }
}
