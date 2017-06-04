/*******************************************************************************
 * Copyright (c) 2016-2017, Kyle Robbertze (AIMS, South Africa)
 *
 * This project is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * It is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this project. If not, see <http://www.gnu.org/licenses/>.
 *
 *    Description:  Module for installing select packages in the installed
 *                  system
 *
 *        Created:  06/12/2016 07:31:14
 *       Compiler:  g++
 *
 *         Author:  Kyle Robbertze (kr), kyle@aims.ac.za
 *******************************************************************************/

#include "ExtraPackagesViewStep.h"

#include "ExtraPackagesPage.h"
#include "JobQueue.h"
#include "utils/Logger.h"

#include <QVariant>

CALAMARES_PLUGIN_FACTORY_DEFINITION( ExtraPackagesViewStepFactory,
                                     registerPlugin<ExtraPackagesViewStep>(); )

ExtraPackagesViewStep::ExtraPackagesViewStep( QObject* parent ) :
    Calamares::ViewStep( parent )
{
    emit nextStatusChanged( true );
    m_widget = new ExtraPackagesPage();
}

ExtraPackagesViewStep::~ExtraPackagesViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}

QString
ExtraPackagesViewStep::prettyName() const
{
    return tr( "Extra Packages" );
}

QString
ExtraPackagesViewStep::prettyStatus() const
{
    return m_widget->prettyStatus();
}

QWidget*
ExtraPackagesViewStep::widget()
{
    return m_widget;
}

void
ExtraPackagesViewStep::next()
{
}

void
ExtraPackagesViewStep::back()
{
}

bool
ExtraPackagesViewStep::isNextEnabled() const
{
    return true;
}

bool
ExtraPackagesViewStep::isBackEnabled() const
{
    return true;
}

bool
ExtraPackagesViewStep::isAtBeginning() const
{
    return true;
}

bool
ExtraPackagesViewStep::isAtEnd() const
{
    return true;
}

void
ExtraPackagesViewStep::onActivate()
{
    m_widget->checkInternet();
}

void
ExtraPackagesViewStep::onLeave()
{
    m_jobs.clear();
    m_jobs.append( m_widget->createJobs( m_sources ) );
    m_widget->addPackagesToStorage();
}

QList<Calamares::job_ptr>
ExtraPackagesViewStep::jobs() const
{
    return m_jobs;
}

void
ExtraPackagesViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    bool showHelpCentre =
        configurationMap.contains( "showHelpCentre" ) &&
        configurationMap.value( "showHelpCentre" ).type() == QVariant::Bool &&
        configurationMap.value( "showHelpCentre" ).toBool();
    QString url;
    if ( configurationMap.contains( "helpUrl" ) &&
            configurationMap.value( "helpUrl" ).type() == QVariant::String )
        url = configurationMap.value( "helpUrl" ).toString();
    m_widget->setUpLink( showHelpCentre, url );
    if ( configurationMap.contains( "packages" ) &&
            configurationMap.value( "packages" ).toList().size() )
        m_widget->setUpPackages( configurationMap.value( "packages" ).toList() );
    else
        cDebug() << "WARNING: No valid packages found in aptextrapackages "
                 "module configuration.";
    if ( configurationMap.contains( "sources" ) &&
            configurationMap.value( "sources" ).toList().size() )
        m_sources = configurationMap.value( "sources" ).toList();
    else
        cDebug() << "WARNING: No valid sources list found in aptextrapackages "
                 "module configuration.";
}
