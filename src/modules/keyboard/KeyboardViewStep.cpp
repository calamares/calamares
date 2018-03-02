/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "KeyboardViewStep.h"

#include "JobQueue.h"
#include "GlobalStorage.h"

#include "KeyboardPage.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( KeyboardViewStepFactory, registerPlugin<KeyboardViewStep>(); )

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
        m_widget->deleteLater();
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


void
KeyboardViewStep::next()
{
    //TODO: actually save those settings somewhere
    emit done();
}


void
KeyboardViewStep::back()
{}


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
    m_jobs = m_widget->createJobs( m_xOrgConfFileName,
                                   m_convertedKeymapPath,
                                   m_writeEtcDefaultKeyboard );
    m_prettyStatus = m_widget->prettyStatus();
}


void
KeyboardViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "xOrgConfFileName" ) &&
            configurationMap.value( "xOrgConfFileName" ).type() == QVariant::String &&
            !configurationMap.value( "xOrgConfFileName" ).toString().isEmpty() )
    {
        m_xOrgConfFileName = configurationMap.value( "xOrgConfFileName" )
                             .toString();
    }
    else
        m_xOrgConfFileName = "00-keyboard.conf";

    if ( configurationMap.contains( "convertedKeymapPath" ) &&
            configurationMap.value( "convertedKeymapPath" ).type() == QVariant::String &&
            !configurationMap.value( "convertedKeymapPath" ).toString().isEmpty() )
    {
        m_convertedKeymapPath = configurationMap.value( "convertedKeymapPath" )
                                .toString();
    }
    else
        m_convertedKeymapPath = QString();

    if ( configurationMap.contains( "writeEtcDefaultKeyboard" ) &&
            configurationMap.value( "writeEtcDefaultKeyboard" ).type() == QVariant::Bool )
        m_writeEtcDefaultKeyboard = configurationMap.value( "writeEtcDefaultKeyboard" ).toBool();
    else
        m_writeEtcDefaultKeyboard = true;
}
