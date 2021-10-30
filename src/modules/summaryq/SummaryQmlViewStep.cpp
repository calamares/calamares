/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020, Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SummaryQmlViewStep.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( SummaryQmlViewStepFactory, registerPlugin< SummaryQmlViewStep >(); )

SummaryQmlViewStep::SummaryQmlViewStep( QObject* parent )
    : Calamares::QmlViewStep( parent )
    , m_config( new Config( this ) )
{
    emit nextStatusChanged( true );
}


SummaryQmlViewStep::~SummaryQmlViewStep() {}

QString
SummaryQmlViewStep::prettyName() const
{
    return m_config->title();
}


bool
SummaryQmlViewStep::isNextEnabled() const
{
    return true;
}


bool
SummaryQmlViewStep::isBackEnabled() const
{
    return true;
}


bool
SummaryQmlViewStep::isAtBeginning() const
{
    return true;
}


bool
SummaryQmlViewStep::isAtEnd() const
{
    return true;
}


Calamares::JobList
SummaryQmlViewStep::jobs() const
{
    return {};
}


void
SummaryQmlViewStep::onActivate()
{
    // Collect the steps before this one: those need to have their
    // summary (text or widget) displayed.
    m_config->collectSummaries( this, Config::Widgets::Disabled );
}
