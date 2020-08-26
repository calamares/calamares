/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "LicenseViewStep.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "LicensePage.h"
#include "utils/Logger.h"

#include <QVariantMap>

CALAMARES_PLUGIN_FACTORY_DEFINITION( LicenseViewStepFactory, registerPlugin< LicenseViewStep >(); )

LicenseViewStep::LicenseViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new LicensePage )
{
    emit nextStatusChanged( false );
    connect( m_widget, &LicensePage::nextStatusChanged, this, &LicenseViewStep::nextStatusChanged );
}


LicenseViewStep::~LicenseViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}


QString
LicenseViewStep::prettyName() const
{
    return tr( "License" );
}


QWidget*
LicenseViewStep::widget()
{
    return m_widget;
}


bool
LicenseViewStep::isNextEnabled() const
{
    return m_widget->isNextEnabled();
}


bool
LicenseViewStep::isBackEnabled() const
{
    return true;
}


bool
LicenseViewStep::isAtBeginning() const
{
    return true;
}


bool
LicenseViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
LicenseViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}

void
LicenseViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    QList< LicenseEntry > entriesList;
    if ( configurationMap.contains( "entries" ) && configurationMap.value( "entries" ).type() == QVariant::List )
    {
        const auto entries = configurationMap.value( "entries" ).toList();
        for ( const QVariant& entryV : entries )
        {
            if ( entryV.type() != QVariant::Map )
            {
                continue;
            }

            LicenseEntry entry( entryV.toMap() );
            if ( entry.isValid() )
            {
                entriesList.append( entry );
            }
        }
    }

    m_widget->setEntries( entriesList );
}
