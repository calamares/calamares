/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "ViewStep.h"

namespace Calamares
{

ViewStep::ViewStep( QObject* parent )
    : QObject( parent )
{}


ViewStep::~ViewStep()
{}


QString
ViewStep::prettyStatus() const
{
    return QString();
}

QWidget*
ViewStep::createSummaryWidget() const
{
    return nullptr;
}

void
ViewStep::onActivate()
{}


void
ViewStep::onLeave()
{}


void
ViewStep::setModuleInstanceKey( const QString& instanceKey )
{
    m_instanceKey = instanceKey;
}


void
ViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    Q_UNUSED( configurationMap );
}

}
