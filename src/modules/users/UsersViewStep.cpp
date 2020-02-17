/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

#include "UsersViewStep.h"

#include "SetHostNameJob.h"
#include "SetPasswordJob.h"
#include "UsersPage.h"

#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( UsersViewStepFactory, registerPlugin< UsersViewStep >(); )

static const NamedEnumTable< SetHostNameJob::Action >&
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
}

UsersViewStep::UsersViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new UsersPage() )
    , m_actions( SetHostNameJob::Action::None )
{
    emit nextStatusChanged( true );
    connect( m_widget, &UsersPage::checkReady, this, &UsersViewStep::nextStatusChanged );
}


UsersViewStep::~UsersViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
UsersViewStep::prettyName() const
{
    return tr( "Users" );
}


QWidget*
UsersViewStep::widget()
{
    return m_widget;
}


bool
UsersViewStep::isNextEnabled() const
{
    return m_widget->isReady();
}


bool
UsersViewStep::isBackEnabled() const
{
    return true;
}


bool
UsersViewStep::isAtBeginning() const
{
    return true;
}


bool
UsersViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
UsersViewStep::jobs() const
{
    return m_jobs;
}


void
UsersViewStep::onActivate()
{
    m_widget->onActivate();
}


void
UsersViewStep::onLeave()
{
    m_jobs.clear();
    m_jobs.append( m_widget->createJobs( m_defaultGroups ) );

    Calamares::Job* j;

    auto userPW = m_widget->getUserPassword();
    j = new SetPasswordJob( userPW.first, userPW.second );
    m_jobs.append( Calamares::job_ptr( j ) );

    j = new SetPasswordJob( "root", m_widget->getRootPassword() );
    m_jobs.append( Calamares::job_ptr( j ) );

    j = new SetHostNameJob( m_widget->getHostname(), m_actions );
    m_jobs.append( Calamares::job_ptr( j ) );
}


void
UsersViewStep::setConfigurationMap( const QVariantMap& configurationMap )
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

    m_widget->setWriteRootPassword( setRootPassword );
    m_widget->setAutologinDefault( getBool( configurationMap, "doAutologin", false ) );
    m_widget->setReusePasswordDefault( getBool( configurationMap, "doReusePassword", false ) );

    if ( configurationMap.contains( "passwordRequirements" )
         && configurationMap.value( "passwordRequirements" ).type() == QVariant::Map )
    {
        auto pr_checks( configurationMap.value( "passwordRequirements" ).toMap() );

        for ( decltype( pr_checks )::const_iterator i = pr_checks.constBegin(); i != pr_checks.constEnd(); ++i )
        {
            m_widget->addPasswordCheck( i.key(), i.value() );
        }
    }

    m_widget->setPasswordCheckboxVisible( getBool( configurationMap, "allowWeakPasswords", false ) );
    m_widget->setValidatePasswordDefault( !getBool( configurationMap, "allowWeakPasswordsDefault", false ) );

    QString shell( QLatin1String( "/bin/bash" ) );  // as if it's not set at all
    if ( configurationMap.contains( "userShell" ) )
    {
        shell = CalamaresUtils::getString( configurationMap, "userShell" );
    }
    // Now it might be explicitly set to empty, which is ok

    Calamares::JobQueue::instance()->globalStorage()->insert( "userShell", shell );

    using Action = SetHostNameJob::Action;

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
    m_actions = hostsfileAction | hostnameAction;
}
