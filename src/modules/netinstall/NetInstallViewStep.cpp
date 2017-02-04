/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
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

#include "NetInstallViewStep.h"

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"

#include "NetInstallPage.h"

CALAMARES_PLUGIN_FACTORY_DEFINITION( NetInstallViewStepFactory, registerPlugin<NetInstallViewStep>(); )

NetInstallViewStep::NetInstallViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new NetInstallPage() )
    , m_nextEnabled( true )
{
    emit nextStatusChanged( true );
    connect( m_widget, &NetInstallPage::checkReady,
             this, &NetInstallViewStep::nextStatusChanged );
}


NetInstallViewStep::~NetInstallViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
        m_widget->deleteLater();
}


QString
NetInstallViewStep::prettyName() const
{
    return tr( "Package selection" );
}


QString
NetInstallViewStep::prettyStatus() const
{
    return m_prettyStatus;
}


QWidget*
NetInstallViewStep::widget()
{
    return m_widget;
}


void
NetInstallViewStep::next()
{
    emit done();
}


void
NetInstallViewStep::back()
{}


bool
NetInstallViewStep::isNextEnabled() const
{
    return m_nextEnabled;
}


bool
NetInstallViewStep::isBackEnabled() const
{
    return true;
}


bool
NetInstallViewStep::isAtBeginning() const
{
    return true;
}


bool
NetInstallViewStep::isAtEnd() const
{
    return true;
}


QList< Calamares::job_ptr >
NetInstallViewStep::jobs() const
{
    return m_jobs;
}


void
NetInstallViewStep::onActivate()
{
    m_widget->onActivate();
}


void
NetInstallViewStep::onLeave()
{
    cDebug() << "Leaving netinstall, adding packages to be installed"
             << "to global storage";

    QMap<QString, QVariant> packagesWithOperation;
    QList<PackageTreeItem::ItemData> packages = m_widget->selectedPackages();
    QVariantList installPackages;
    QVariantList tryInstallPackages;
    cDebug() << "Processing";

    for ( auto package : packages )
    {
        QMap<QString, QVariant> details;
        details.insert( "pre-script", package.preScript );
        details.insert( "package", package.packageName );
        details.insert( "post-script", package.postScript );
        if ( package.isCritical )
            installPackages.append( details );
        else
            tryInstallPackages.append( details );
    }

    if ( !installPackages.empty() )
        packagesWithOperation.insert( "install", QVariant( installPackages ) );
    if ( !tryInstallPackages.empty() )
        packagesWithOperation.insert( "try_install", QVariant( tryInstallPackages ) );

    if ( !packagesWithOperation.isEmpty() )
    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        gs->insert( "packageOperations", QVariant( packagesWithOperation ) );
    }
}


void
NetInstallViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    if ( configurationMap.contains( "groupsUrl" ) &&
            configurationMap.value( "groupsUrl" ).type() == QVariant::String )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert(
            "groupsUrl", configurationMap.value( "groupsUrl" ).toString() );
        m_widget->loadGroupList();
    }
}
