/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "WelcomeViewStep.h"

#include "WelcomePage.h"
#include "checker/RequirementsChecker.h"
#include "utils/Logger.h"


#include <QVariant>

CALAMARES_PLUGIN_FACTORY_DEFINITION( WelcomeViewStepFactory, registerPlugin<WelcomeViewStep>(); )

WelcomeViewStep::WelcomeViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_requirementsChecker( new RequirementsChecker( this ) )
{
    emit nextStatusChanged( true );
    m_widget = new WelcomePage( m_requirementsChecker );
    connect( m_requirementsChecker, &RequirementsChecker::verdictChanged,
             this, &WelcomeViewStep::nextStatusChanged );
}


WelcomeViewStep::~WelcomeViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
WelcomeViewStep::prettyName() const
{
    return tr( "Welcome" );
}


QWidget*
WelcomeViewStep::widget()
{
    return m_widget;
}


void
WelcomeViewStep::next()
{
    emit done();
}


void
WelcomeViewStep::back()
{}


bool
WelcomeViewStep::isNextEnabled() const
{
    return m_requirementsChecker->verdict();
}


bool
WelcomeViewStep::isBackEnabled() const
{
    return false;
}


bool
WelcomeViewStep::isAtBeginning() const
{
    return true;
}


bool
WelcomeViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
WelcomeViewStep::jobs() const
{
    return QList< Calamares::job_ptr >();
}


void
WelcomeViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool showSupportUrl =
        configurationMap.contains( "showSupportUrl" ) &&
        configurationMap.value( "showSupportUrl" ).type() == QVariant::Bool &&
        configurationMap.value( "showSupportUrl" ).toBool();
    bool showKnownIssuesUrl =
        configurationMap.contains( "showKnownIssuesUrl" ) &&
        configurationMap.value( "showKnownIssuesUrl" ).type() == QVariant::Bool &&
        configurationMap.value( "showKnownIssuesUrl" ).toBool();
    bool showReleaseNotesUrl =
        configurationMap.contains( "showReleaseNotesUrl" ) &&
        configurationMap.value( "showReleaseNotesUrl" ).type() == QVariant::Bool &&
        configurationMap.value( "showReleaseNotesUrl" ).toBool();

    m_widget->setUpLinks( showSupportUrl,
                          showKnownIssuesUrl,
                          showReleaseNotesUrl );

    if ( configurationMap.contains( "requirements" ) &&
         configurationMap.value( "requirements" ).type() == QVariant::Map )
        m_requirementsChecker->setConfigurationMap( configurationMap.value( "requirements" ).toMap() );
    else
        cWarning() << "no valid requirements map found in welcome "
                    "module configuration.";
}

