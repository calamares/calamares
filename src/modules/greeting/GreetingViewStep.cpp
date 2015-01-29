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

#include "GreetingViewStep.h"

#include "GreetingPage.h"

GreetingViewStep::GreetingViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new GreetingPage() )
{
    emit nextStatusChanged( true );
}


GreetingViewStep::~GreetingViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
GreetingViewStep::prettyName() const
{
    return tr( "Welcome" );
}


QWidget*
GreetingViewStep::widget()
{
    return m_widget;
}


void
GreetingViewStep::next()
{
    emit done();
}


void
GreetingViewStep::back()
{}


bool
GreetingViewStep::isNextEnabled() const
{
    return true;
}


bool
GreetingViewStep::isBackEnabled() const
{
    return false;
}


bool
GreetingViewStep::isAtBeginning() const
{
    return true;
}


bool
GreetingViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
GreetingViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}

