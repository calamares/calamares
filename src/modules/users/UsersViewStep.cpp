/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "JobQueue.h"
#include "GlobalStorage.h"

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


void
UsersViewStep::next()
{
    emit done();
}


void
UsersViewStep::back()
{}


bool
UsersViewStep::isNextEnabled() const
{
    return m_widget->isReady();
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

    m_jobs.append( m_widget->createJobs( m_userGroup, m_defaultGroups ) );
}


void
UsersViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "userGroup" ) &&
         configurationMap.value( "userGroup" ).type() == QVariant::String )
    {
        m_userGroup = configurationMap.value( "userGroup" ).toString();
    }
    if ( m_userGroup.isEmpty() )
        m_userGroup = QStringLiteral( "users" );

    if ( configurationMap.contains( "defaultGroups" ) &&
         configurationMap.value( "defaultGroups" ).type() == QVariant::List )
    {
        m_defaultGroups = configurationMap.value( "defaultGroups" ).toStringList();
    }
    else
    {
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
}

