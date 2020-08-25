/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
