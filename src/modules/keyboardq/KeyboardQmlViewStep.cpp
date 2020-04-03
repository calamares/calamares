/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "KeyboardQmlViewStep.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Variant.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( KeyboardQmlViewStepFactory, registerPlugin< KeyboardQmlViewStep >(); )

KeyboardQmlViewStep::KeyboardQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
    , m_nextEnabled( false )
    , m_writeEtcDefaultKeyboard( true )
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
    return m_jobs;
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
    m_jobs = m_config->createJobs( m_xOrgConfFileName, m_convertedKeymapPath, m_writeEtcDefaultKeyboard );
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

    Calamares::QmlViewStep::setConfigurationMap( configurationMap );
}
