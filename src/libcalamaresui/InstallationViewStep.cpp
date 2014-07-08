/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <InstallationViewStep.h>

#include <QLabel>

namespace Calamares
{

InstallationViewStep::InstallationViewStep( QObject* parent )
    : ViewStep( parent )
    , m_widget( new QLabel( "[Installation Progress]" ) )
{
}

QString
InstallationViewStep::prettyName() const
{
    return tr( "Install" );
}

QWidget*
InstallationViewStep::widget()
{
    return m_widget;
}


void
InstallationViewStep::next()
{
}

void
InstallationViewStep::back()
{
}

bool
InstallationViewStep::isNextEnabled() const
{
    return false;
}

bool
InstallationViewStep::isAtBeginning() const
{
    return false;
}

bool
InstallationViewStep::isAtEnd() const
{
    return false;
}

} // namespace
