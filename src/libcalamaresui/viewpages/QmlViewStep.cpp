/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#include "QmlViewStep.h"

namespace Calamares
{

QmlViewStep::QmlViewStep( const QString& name, QObject* parent )
    : ViewStep( parent )
    , m_name( name )
{
}

QmlViewStep::~QmlViewStep() {}

QString
QmlViewStep::prettyName() const
{
    // TODO: query the QML itself
    return tr( "QML Step <i>%1</i>" ).arg( m_name );
}


}  // namespace Calamares

bool
Calamares::QmlViewStep::isAtBeginning() const
{
    return true;
}

bool
Calamares::QmlViewStep::isAtEnd() const
{
    return true;
}
bool
Calamares::QmlViewStep::isBackEnabled() const
{
    return true;
}

bool
Calamares::QmlViewStep::isNextEnabled() const
{
    return true;
}

Calamares::JobList
Calamares::QmlViewStep::jobs() const
{
    return JobList();
}

void
Calamares::QmlViewStep::onActivate()
{
    // TODO: call into QML
}

void
Calamares::QmlViewStep::onLeave()
{
    // TODO: call into QML
}

QWidget*
Calamares::QmlViewStep::widget()
{
    return nullptr;
}
