/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ViewStep.h"

#include <QApplication>
#include <QStyle>

namespace Calamares
{

ViewStep::ViewStep( QObject* parent )
    : QObject( parent )
{
}


ViewStep::~ViewStep() {}


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
{
}


void
ViewStep::onLeave()
{
}

void
ViewStep::next()
{
}

void
ViewStep::back()
{
}


void
ViewStep::setModuleInstanceKey( const Calamares::ModuleSystem::InstanceKey& instanceKey )
{
    m_instanceKey = instanceKey;
}


void
ViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    Q_UNUSED( configurationMap )
}


RequirementsList
ViewStep::checkRequirements()
{
    return RequirementsList();
}

QSize
ViewStep::widgetMargins( Qt::Orientations panelSides )
{
    Q_UNUSED( panelSides )

    // Application's default style
    const auto* s = QApplication::style();
    return QSize( s->pixelMetric( QStyle::PM_LayoutLeftMargin ), s->pixelMetric( QStyle::PM_LayoutTopMargin ) );
}

}  // namespace Calamares
