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

#include "SummaryViewStep.h"

#include "SummaryPage.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( SummaryViewStepFactory, registerPlugin<SummaryViewStep>(); )

SummaryViewStep::SummaryViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new SummaryPage( this ) )
{
    emit nextStatusChanged( true );
}


SummaryViewStep::~SummaryViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
SummaryViewStep::prettyName() const
{
    return tr( "Summary" );
}


QWidget*
SummaryViewStep::widget()
{
    return m_widget;
}


void
SummaryViewStep::next()
{
    emit done();
}


void
SummaryViewStep::back()
{}


bool
SummaryViewStep::isNextEnabled() const
{
    return true;
}


bool
SummaryViewStep::isBackEnabled() const
{
    return true;
}


bool
SummaryViewStep::isAtBeginning() const
{
    return true;
}


bool
SummaryViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
SummaryViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}


void
SummaryViewStep::onActivate()
{
    m_widget->onActivate();
}


void
SummaryViewStep::onLeave()
{
    m_widget->createContentWidget();
}

