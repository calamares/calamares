/* === This file is part of Calamares - <https://github.com/calamares> ===
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
#include "PlasmaLnfViewStep.h"

#include "PlasmaLnfJob.h"
#include "PlasmaLnfPage.h"
#include "ThemeInfo.h"

#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"

#include <QProcess>
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
    if ( !m_themeId.isEmpty() )
    {
        if ( !m_lnfPath.isEmpty() )
            l.append( Calamares::job_ptr( new PlasmaLnfJob( m_lnfPath, m_themeId ) ) );
        else
            cWarning() << "no lnftool given for plasmalnf module.";
    }
    return l;
}


void
PlasmaLnfViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_lnfPath = CalamaresUtils::getString( configurationMap, "lnftool" );
    m_widget->setLnfPath( m_lnfPath );

    if ( m_lnfPath.isEmpty() )
        cWarning() << "no lnftool given for plasmalnf module.";

    m_liveUser = CalamaresUtils::getString( configurationMap, "liveuser" );

    if ( configurationMap.contains( "themes" ) &&
        configurationMap.value( "themes" ).type() == QVariant::List )
    {
        ThemeInfoList allThemes;
        auto themeList = configurationMap.value( "themes" ).toList();
        // Create the ThemInfo objects for the listed themes; information
        // about the themes from Plasma (e.g. human-readable name and description)
        // are filled in by update_names() in PlasmaLnfPage.
        for ( const auto& i : themeList )
            if ( i.type() == QVariant::Map )
            {
                auto iv = i.toMap();
                allThemes.append( ThemeInfo( iv.value( "theme" ).toString(), iv.value( "image" ).toString() ) );
            }
            else if ( i.type() == QVariant::String )
                allThemes.append( ThemeInfo( i.toString() ) );

        if ( allThemes.length() == 1 )
            cWarning() << "only one theme enabled in plasmalnf";
        m_widget->setEnabledThemes( allThemes );
    }
    else
        m_widget->setEnabledThemesAll();  // All of them
}

void
PlasmaLnfViewStep::themeSelected( const QString& id )
{
    m_themeId = id;
    if ( m_lnfPath.isEmpty() )
    {
        cWarning() << "no lnftool given for plasmalnf module.";
        return;
    }

    QProcess lnftool;
    if ( !m_liveUser.isEmpty() )
        lnftool.start( "sudo", {"-E", "-H", "-u", m_liveUser, m_lnfPath, "--resetLayout", "--apply", id} );
    else
        lnftool.start( m_lnfPath, {"--resetLayout", "--apply", id} );

    if ( !lnftool.waitForStarted( 1000 ) )
    {
        cWarning() << "could not start look-and-feel" << m_lnfPath;
        return;
    }
    if ( !lnftool.waitForFinished() )
    {
        cWarning() << m_lnfPath << "timed out.";
        return;
    }

    if ( ( lnftool.exitCode() == 0 ) && ( lnftool.exitStatus() == QProcess::NormalExit ) )
        cDebug() << "Plasma look-and-feel applied" << id;
    else
        cWarning() << "could not apply look-and-feel" << id;
}
