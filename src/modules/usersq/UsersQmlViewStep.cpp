/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

#include "UsersQmlViewStep.h"

#include "SetHostNameJob.h"
#include "SetPasswordJob.h"

#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( UsersQmlViewStepFactory, registerPlugin< UsersQmlViewStep >(); )

/*static const NamedEnumTable< SetHostNameJob::Action >&
hostnameActions()
{
    using Action = SetHostNameJob::Action;

    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< Action > names {
        { QStringLiteral( "none" ), Action::None },
        { QStringLiteral( "etcfile" ), Action::EtcHostname },
        { QStringLiteral( "hostnamed" ), Action::SystemdHostname }
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}*/

UsersQmlViewStep::UsersQmlViewStep( QObject* parent )
: Calamares::QmlViewStep( parent )
, m_config( new Config(this) )
{
    emit nextStatusChanged( true );
    //connect( m_config, &Config::checkReady, this, &UsersQmlViewStep::nextStatusChanged );
}

QString
UsersQmlViewStep::prettyName() const
{
    return tr( "Users" );
}

bool
UsersQmlViewStep::isNextEnabled() const
{
    //return m_config->isReady();
    return true;
}


bool
UsersQmlViewStep::isBackEnabled() const
{
    return true;
}


bool
UsersQmlViewStep::isAtBeginning() const
{
    return true;
}


bool
UsersQmlViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
UsersQmlViewStep::jobs() const
{
    return m_jobs;
}


void
UsersQmlViewStep::onActivate()
{
    //m_config->onActivate();
}


void
UsersQmlViewStep::onLeave()
{
    m_jobs.clear();

    //m_jobs.append( m_config->createJobs( m_defaultGroups ) );
}


void
UsersQmlViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    using CalamaresUtils::getBool;

    if ( configurationMap.contains( "defaultGroups" )
        && configurationMap.value( "defaultGroups" ).type() == QVariant::List )
    {
        m_defaultGroups = configurationMap.value( "defaultGroups" ).toStringList();
    }
    else
    {
        cWarning() << "Using fallback groups. Please check defaultGroups in users.conf";
        m_defaultGroups = QStringList { "lp", "video", "network", "storage", "wheel", "audio" };
    }

    if ( configurationMap.contains( "autologinGroup" )
        && configurationMap.value( "autologinGroup" ).type() == QVariant::String )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert(
            "autologinGroup", configurationMap.value( "autologinGroup" ).toString() );
    }

    if ( configurationMap.contains( "sudoersGroup" )
        && configurationMap.value( "sudoersGroup" ).type() == QVariant::String )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert( "sudoersGroup",
                                                                  configurationMap.value( "sudoersGroup" ).toString() );
    }

    bool setRootPassword = getBool( configurationMap, "setRootPassword", true );
    Calamares::JobQueue::instance()->globalStorage()->insert( "setRootPassword", setRootPassword );

    //m_config->writeRootPassword( setRootPassword );
    //m_config->setAutologinGroup( getBool( configurationMap, "doAutologin", false ) );
    //m_config->setReusePasswordDefault( getBool( configurationMap, "doReusePassword", false ) );

    if ( configurationMap.contains( "passwordRequirements" )
        && configurationMap.value( "passwordRequirements" ).type() == QVariant::Map )
    {
        auto pr_checks( configurationMap.value( "passwordRequirements" ).toMap() );

        for ( decltype( pr_checks )::const_iterator i = pr_checks.constBegin(); i != pr_checks.constEnd(); ++i )
        {
            //m_config->passwordChecks( i.key(), i.value() );
        }
    }

    //m_config->setPasswordCheckboxVisible( getBool( configurationMap, "allowWeakPasswords", false ) );
    //m_config->setValidatePasswordDefault( !getBool( configurationMap, "allowWeakPasswordsDefault", false ) );

    QString shell( QLatin1String( "/bin/bash" ) );  // as if it's not set at all
    if ( configurationMap.contains( "userShell" ) )
    {
        shell = CalamaresUtils::getString( configurationMap, "userShell" );
    }
    // Now it might be explicitly set to empty, which is ok

    Calamares::JobQueue::instance()->globalStorage()->insert( "userShell", shell );

    /*using Action = SetHostNameJob::Action;

    QString hostnameActionString = CalamaresUtils::getString( configurationMap, "setHostname" );
    if ( hostnameActionString.isEmpty() )
    {
        hostnameActionString = QStringLiteral( "EtcFile" );
    }
    bool ok = false;
    auto hostnameAction = hostnameActions().find( hostnameActionString, ok );
    if ( !ok )
    {
        hostnameAction = Action::EtcHostname;
    }

    Action hostsfileAction = getBool( configurationMap, "writeHostsFile", true ) ? Action::WriteEtcHosts : Action::None;
    m_actions = hostsfileAction | hostnameAction;*/

    Calamares::QmlViewStep::setConfigurationMap( configurationMap ); // call parent implementation last
    setContextProperty( "Users", m_config );
}
