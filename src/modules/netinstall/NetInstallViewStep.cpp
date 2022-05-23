/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "NetInstallViewStep.h"

#include "NetInstallPage.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( NetInstallViewStepFactory, registerPlugin< NetInstallViewStep >(); )

NetInstallViewStep::NetInstallViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new NetInstallPage( &m_config ) )
    , m_nextEnabled( false )
{
    connect( &m_config, &Config::statusReady, this, &NetInstallViewStep::nextIsReady );
}


NetInstallViewStep::~NetInstallViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
NetInstallViewStep::prettyName() const
{
    return m_config.sidebarLabel();

#if defined( TABLE_OF_TRANSLATIONS )
    __builtin_unreachable();
    // This is a table of "standard" labels for this module. If you use them
    // in the label: sidebar: section of the config file, the existing
    // translations can be used.
    //
    // These translations still live here, even though the lookup
    // code is in the Config class.
    tr( "Package selection" );
    tr( "Office software" );
    tr( "Office package" );
    tr( "Browser software" );
    tr( "Browser package" );
    tr( "Web browser" );
    tr( "Kernel", "label for netinstall module, Linux kernel" );
    tr( "Services", "label for netinstall module, system services" );
    tr( "Login", "label for netinstall module, choose login manager" );
    tr( "Desktop", "label for netinstall module, choose desktop environment" );
    tr( "Applications" );
    tr( "Communication", "label for netinstall module" );
    tr( "Development", "label for netinstall module" );
    tr( "Office", "label for netinstall module" );
    tr( "Multimedia", "label for netinstall module" );
    tr( "Internet", "label for netinstall module" );
    tr( "Theming", "label for netinstall module" );
    tr( "Gaming", "label for netinstall module" );
    tr( "Utilities", "label for netinstall module" );
#endif
}


QWidget*
NetInstallViewStep::widget()
{
    return m_widget;
}


bool
NetInstallViewStep::isNextEnabled() const
{
    return !m_config.required() || m_nextEnabled;
}


bool
NetInstallViewStep::isBackEnabled() const
{
    return true;
}


bool
NetInstallViewStep::isAtBeginning() const
{
    return true;
}


bool
NetInstallViewStep::isAtEnd() const
{
    return true;
}


Calamares::JobList
NetInstallViewStep::jobs() const
{
    return Calamares::JobList();
}


void
NetInstallViewStep::onActivate()
{
    m_widget->onActivate();
}

void
NetInstallViewStep::onLeave()
{
    m_config.finalizeGlobalStorage( moduleInstanceKey() );
}

void
NetInstallViewStep::nextIsReady()
{
    m_nextEnabled = true;
    emit nextStatusChanged( true );
}

void
NetInstallViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config.setConfigurationMap( configurationMap );
}
