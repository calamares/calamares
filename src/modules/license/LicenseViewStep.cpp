/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
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

#include "LicensePage.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"

#include <QVariantMap>

LicenseViewStep::LicenseViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
{
    emit nextStatusChanged( true );
    m_widget = new LicensePage;
}


LicenseViewStep::~LicenseViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
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


void
LicenseViewStep::next()
{
    emit done();
}


void
LicenseViewStep::back()
{}


bool
LicenseViewStep::isNextEnabled() const
{
    return true;
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
    bool showLicense1Url =
        configurationMap.contains( "showLicense1Url" ) &&
        configurationMap.value( "showLicense1Url" ).type() == QVariant::Bool &&
        configurationMap.value( "showLicense1Url" ).toBool();
    bool showLicense2Url =
        configurationMap.contains( "showLicense2Url" ) &&
        configurationMap.value( "showLicense2Url" ).type() == QVariant::Bool &&
        configurationMap.value( "showLicense2Url" ).toBool();
    bool showLicense3Url =
        configurationMap.contains( "showLicense3Url" ) &&
        configurationMap.value( "showLicense3Url" ).type() == QVariant::Bool &&
        configurationMap.value( "showLicense3Url" ).toBool();
    bool showLicense4Url =
        configurationMap.contains( "showLicense4Url" ) &&
        configurationMap.value( "showLicense4Url" ).type() == QVariant::Bool &&
        configurationMap.value( "showLicense4Url" ).toBool();
        
    QString license1Url;
    if ( configurationMap.contains( "license1Url" ) &&
         configurationMap.value( "license1Url" ).type() == QVariant::String )
    {
        license1Url = configurationMap.value( "license1Url" ).toString();
        cDebug() << "Read: " << license1Url;
    }
    
    QString license2Url;
    if ( configurationMap.contains( "license2Url" ) &&
         configurationMap.value( "license2Url" ).type() == QVariant::String )
    {
        license2Url = configurationMap.value( "license2Url" ).toString();
    }
    
    QString license3Url;
    if ( configurationMap.contains( "license3Url" ) &&
         configurationMap.value( "license3Url" ).type() == QVariant::String )
    {
        license3Url = configurationMap.value( "license3Url" ).toString();
    }
    
    QString license4Url;
    if ( configurationMap.contains( "license4Url" ) &&
         configurationMap.value( "license4Url" ).type() == QVariant::String )
    {
        license4Url = configurationMap.value( "license4Url" ).toString();
    }
    
    QString license1Button;
    if ( configurationMap.contains( "license1Button" ) &&
         configurationMap.value( "license1Button" ).type() == QVariant::String )
    {
        license1Button = configurationMap.value( "license1Button" ).toString();
        cDebug() << "Read: " << license1Button;
    }

    m_widget->showLicense1Url( showLicense1Url );
    m_widget->showLicense2Url( showLicense2Url );
    m_widget->showLicense3Url( showLicense3Url );
    m_widget->showLicense4Url( showLicense4Url );
    m_widget->setLicense1Url(license1Url);
    m_widget->setLicense2Url(license2Url);
    m_widget->setLicense3Url(license3Url);
    m_widget->setLicense4Url(license4Url);
    m_widget->setLicense1Button(license1Button);
                          
}
