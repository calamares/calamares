/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#include "FinishedViewStep.h"

#include "FinishedPage.h"

#include <QVariantMap>

FinishedViewStep::FinishedViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new FinishedPage() )
{
    emit nextStatusChanged( true );
}


FinishedViewStep::~FinishedViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
FinishedViewStep::prettyName() const
{
    return tr( "Finish" );
}


QWidget*
FinishedViewStep::widget()
{
    return m_widget;
}


void
FinishedViewStep::next()
{
    emit done();
}


void
FinishedViewStep::back()
{}


bool
FinishedViewStep::isNextEnabled() const
{
    return false;
}


bool
FinishedViewStep::isBackEnabled() const
{
    return false;
}


bool
FinishedViewStep::isAtBeginning() const
{
    return true;
}


bool
FinishedViewStep::isAtEnd() const
{
    return true;
}


void
FinishedViewStep::onActivate()
{
    m_widget->setUpRestart();
}


QList< Calamares::job_ptr >
FinishedViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}


void
FinishedViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "restartNowEnabled" ) &&
         configurationMap.value( "restartNowEnabled" ).type() == QVariant::Bool )
    {
        bool restartNowEnabled = configurationMap.value( "restartNowEnabled" ).toBool();

        m_widget->setRestartNowEnabled( restartNowEnabled );
        if ( restartNowEnabled )
        {
            if ( configurationMap.contains( "restartNowChecked" ) &&
                 configurationMap.value( "restartNowChecked" ).type() == QVariant::Bool )
            {
                m_widget->setRestartNowChecked( configurationMap.value( "restartNowChecked" ).toBool() );
            }

            if ( configurationMap.contains( "restartNowCommand" ) &&
                 configurationMap.value( "restartNowCommand" ).type() == QVariant::String )
            {
                m_widget->setRestartNowCommand( configurationMap.value( "restartNowCommand" ).toString() );
            }
            else
            {
                m_widget->setRestartNowCommand( "systemctl -i reboot");
            }
        }
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( FinishedViewStepFactory, registerPlugin<FinishedViewStep>(); )
