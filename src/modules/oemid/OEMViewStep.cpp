/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "OEMViewStep.h"

#include "utils/Variant.h"

#include <QLabel>

OEMViewStep::OEMViewStep(QObject* parent)
    : Calamares::ViewStep( parent )
    , m_widget( nullptr )
{
}

OEMViewStep::~OEMViewStep()
{
}

bool OEMViewStep::isBackEnabled() const
{
    return true;
}

bool OEMViewStep::isNextEnabled() const
{
    return true;
}

bool OEMViewStep::isAtBeginning() const
{
    return true;
}

bool OEMViewStep::isAtEnd() const
{
    return true;
}

QString OEMViewStep::prettyName() const
{
    return tr( "OEM Configuration" );
}

QWidget * OEMViewStep::widget()
{
    return nullptr; // m_widget;
}

Calamares::JobList OEMViewStep::jobs() const
{
    return Calamares::JobList();
}

void OEMViewStep::setConfigurationMap(const QVariantMap& configurationMap)
{
    m_batch = CalamaresUtils::getString( configurationMap, "batch-identifier" );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( OEMViewStepFactory, registerPlugin<OEMViewStep>(); )
