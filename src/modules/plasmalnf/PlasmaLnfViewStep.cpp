/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
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

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtils.h"
#include "utils/CalamaresUtilsSystem.h"

#include "PlasmaLnfInfo.h"
#include "PlasmaLnfJob.h"
#include "PlasmaLnfPage.h"
#include "PlasmaLnfViewStep.h"

#include <QDesktopServices>
#include <QVariantMap>

CALAMARES_PLUGIN_FACTORY_DEFINITION( PlasmaLnfViewStepFactory, registerPlugin<PlasmaLnfViewStep>(); )

PlasmaLnfViewStep::PlasmaLnfViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new PlasmaLnfPage )
{
    connect( m_widget, &PlasmaLnfPage::plasmaThemeSelected, this, &PlasmaLnfViewStep::themeSelected );
    emit nextStatusChanged( false );
}


PlasmaLnfViewStep::~PlasmaLnfViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
PlasmaLnfViewStep::prettyName() const
{
    return tr( "Look-and-Feel" );
}


QWidget*
PlasmaLnfViewStep::widget()
{
    return m_widget;
}


void
PlasmaLnfViewStep::next()
{
    emit done();
}


void
PlasmaLnfViewStep::back()
{}


bool
PlasmaLnfViewStep::isNextEnabled() const
{
    return true;
}


bool
PlasmaLnfViewStep::isBackEnabled() const
{
    return true;
}


bool
PlasmaLnfViewStep::isAtBeginning() const
{
    return true;
}


bool
PlasmaLnfViewStep::isAtEnd() const
{
    return true;
}


void PlasmaLnfViewStep::onLeave()
{
}


Calamares::JobList
PlasmaLnfViewStep::jobs() const
{
    Calamares::JobList l;

    cDebug() << "Creating Plasma LNF jobs ..";
    if ( !m_themeId.isEmpty() && !m_lnfPath.isEmpty() )
    {
        l.append( Calamares::job_ptr( new PlasmaLnfJob( m_lnfPath, m_themeId ) ) );
    }
    return l;
}


void
PlasmaLnfViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_lnfPath = CalamaresUtils::getString( configurationMap, "lnftool" );
    Calamares::set_lnftool( m_lnfPath );

    if (m_lnfPath.isEmpty())
        cDebug() << "WARNING: no lnftool given for plasmalnf module.";
}

void
PlasmaLnfViewStep::themeSelected( const QString& id )
{
    m_themeId = id;
}
