/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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
