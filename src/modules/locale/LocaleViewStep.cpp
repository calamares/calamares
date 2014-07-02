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

#include "LocaleViewStep.h"

#include "LocalePage.h"

#include "timezonewidget/localeglobal.h"

LocaleViewStep::LocaleViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new LocalePage() )
{
    LocaleGlobal::init(); //this takes a long time
    m_widget->init();
    emit nextStatusChanged( true );
}


LocaleViewStep::~LocaleViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
LocaleViewStep::prettyName() const
{
    return tr( "Location" );
}


QWidget*
LocaleViewStep::widget()
{
    return m_widget;
}


void
LocaleViewStep::next()
{
    //TODO: actually save those settings somewhere
    emit done();
}


void
LocaleViewStep::back()
{}


bool
LocaleViewStep::isNextEnabled() const
{
    return true;
}


bool
LocaleViewStep::isAtBeginning() const
{
    return true;
}


bool
LocaleViewStep::isAtEnd() const
{
    return true;
}

