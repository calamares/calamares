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

#include "UsersPage.h"

// #include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( UsersViewStepFactory, registerPlugin<UsersViewStep>(); )

UsersViewStep::UsersViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new UsersPage() )
{
    emit nextStatusChanged( true );
    connect( m_widget, &UsersPage::checkReady,
             this, &UsersViewStep::nextStatusChanged );
}


UsersViewStep::~UsersViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
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
}


void
UsersViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "defaultGroups" ) &&
         configurationMap.value( "defaultGroups" ).type() == QVariant::List )
    {
        m_defaultGroups = configurationMap.value( "defaultGroups" ).toStringList();
    }
    else
    {
        cWarning() << "Using fallback groups. Please check defaultGroups in users.conf";
        m_defaultGroups = QStringList{ "lp", "video", "network", "storage", "wheel", "audio" };
    }

    if ( configurationMap.contains( "autologinGroup" ) &&
         configurationMap.value( "autologinGroup" ).type() == QVariant::String )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert( "autologinGroup",
                        configurationMap.value( "autologinGroup" ).toString() );
    }

    if ( configurationMap.contains( "sudoersGroup" ) &&
         configurationMap.value( "sudoersGroup" ).type() == QVariant::String )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert( "sudoersGroup",
                        configurationMap.value( "sudoersGroup" ).toString() );
    }

    if ( configurationMap.contains( "setRootPassword" ) &&
         configurationMap.value( "setRootPassword" ).type() == QVariant::Bool )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert( "setRootPassword",
                        configurationMap.value( "setRootPassword" ).toBool() );
        m_widget->setWriteRootPassword( configurationMap.value( "setRootPassword" ).toBool() );
    }

    if ( configurationMap.contains( "doAutologin" ) &&
         configurationMap.value( "doAutologin" ).type() == QVariant::Bool )
    {
        m_widget->setAutologinDefault( configurationMap.value( "doAutologin" ).toBool() );
    }

    if ( configurationMap.contains( "doReusePassword" ) &&
         configurationMap.value( "doReusePassword" ).type() == QVariant::Bool )
    {
        m_widget->setReusePasswordDefault( configurationMap.value( "doReusePassword" ).toBool() );
    }

    if ( configurationMap.contains( "passwordRequirements" ) &&
        configurationMap.value( "passwordRequirements" ).type() == QVariant::Map )
    {
        auto pr_checks( configurationMap.value( "passwordRequirements" ).toMap() );

        for (decltype(pr_checks)::const_iterator i = pr_checks.constBegin();
            i != pr_checks.constEnd(); ++i)
        {
            m_widget->addPasswordCheck( i.key(), i.value() );
        }
    }

    QString shell( QLatin1String( "/bin/bash" ) );  // as if it's not set at all
    if ( configurationMap.contains( "userShell" ) )
        shell = CalamaresUtils::getString( configurationMap, "userShell" );
        // Now it might be explicitly set to empty, which is ok

    Calamares::JobQueue::instance()->globalStorage()->insert( "userShell", shell );
}

