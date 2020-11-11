/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "PlasmaLnfViewStep.h"

#include "Config.h"
#include "PlasmaLnfPage.h"
#include "ThemeInfo.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QProcess>
#include <QVariantMap>

#ifdef WITH_KCONFIG
#include <KConfigGroup>
#include <KSharedConfig>
#endif

CALAMARES_PLUGIN_FACTORY_DEFINITION( PlasmaLnfViewStepFactory, registerPlugin< PlasmaLnfViewStep >(); )

static QString
currentPlasmaTheme()
{
#ifdef WITH_KCONFIG
    KConfigGroup cg( KSharedConfig::openConfig( QStringLiteral( "kdeglobals" ) ), "KDE" );
    return cg.readEntry( "LookAndFeelPackage", QString() );
#else
    cWarning() << "No KConfig support, cannot determine Plasma theme.";
    return QString();
#endif
}

PlasmaLnfViewStep::PlasmaLnfViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_config( new Config( this ) )
    , m_widget( new PlasmaLnfPage )
{
    connect( m_widget, &PlasmaLnfPage::plasmaThemeSelected, m_config, &Config::setTheme );
    emit nextStatusChanged( false );
}


PlasmaLnfViewStep::~PlasmaLnfViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
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


void
PlasmaLnfViewStep::onLeave()
{
}


Calamares::JobList
PlasmaLnfViewStep::jobs() const
{
    return m_config->createJobs();
}


void
PlasmaLnfViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_config->setConfigurationMap( configurationMap );

    m_widget->setLnfPath( m_config->lnfToolPath() );

    QString preselect = CalamaresUtils::getString( configurationMap, "preselect" );
    if ( preselect == QStringLiteral( "*" ) )
    {
        preselect = currentPlasmaTheme();
    }
    if ( !preselect.isEmpty() )
    {
        m_widget->setPreselect( preselect );
    }

    bool showAll = CalamaresUtils::getBool( configurationMap, "showAll", false );

    if ( configurationMap.contains( "themes" ) && configurationMap.value( "themes" ).type() == QVariant::List )
    {
        ThemeInfoList listedThemes;
        auto themeList = configurationMap.value( "themes" ).toList();
        // Create the ThemInfo objects for the listed themes; information
        // about the themes from Plasma (e.g. human-readable name and description)
        // are filled in by update_names() in PlasmaLnfPage.
        for ( const auto& i : themeList )
            if ( i.type() == QVariant::Map )
            {
                auto iv = i.toMap();
                listedThemes.append( ThemeInfo( iv.value( "theme" ).toString(), iv.value( "image" ).toString() ) );
            }
            else if ( i.type() == QVariant::String )
            {
                listedThemes.append( ThemeInfo( i.toString() ) );
            }

        if ( listedThemes.length() == 1 )
        {
            cWarning() << "only one theme enabled in plasmalnf";
        }
        m_widget->setEnabledThemes( listedThemes, showAll );
    }
    else
    {
        m_widget->setEnabledThemesAll();  // All of them
    }
}
