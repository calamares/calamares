/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "PlasmaLnfJob.h"
#include "ThemeInfo.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#ifdef WITH_KCONFIG
#include <KConfigGroup>
#include <KSharedConfig>
#endif

#include <QSortFilterProxyModel>

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

Config::Config( QObject* parent )
    : QObject( parent )
    , m_themeModel( new ThemesModel( this ) )
{
    auto* filter = new QSortFilterProxyModel( m_themeModel );
    filter->setFilterRole( ThemesModel::ShownRole );
    filter->setFilterFixedString( QStringLiteral( "true" ) );
    filter->setSourceModel( m_themeModel );
    filter->setSortRole( ThemesModel::LabelRole );
    filter->sort( 0 );

    m_filteredModel = filter;
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_lnfPath = CalamaresUtils::getString( configurationMap, "lnftool" );

    if ( m_lnfPath.isEmpty() )
    {
        cWarning() << "no lnftool given for plasmalnf module.";
    }

    m_liveUser = CalamaresUtils::getString( configurationMap, "liveuser" );

    QString preselect = CalamaresUtils::getString( configurationMap, "preselect" );
    if ( preselect == QStringLiteral( "*" ) )
    {
        preselect = currentPlasmaTheme();
    }
    m_preselectThemeId = preselect;

    if ( configurationMap.contains( "themes" ) && configurationMap.value( "themes" ).type() == QVariant::List )
    {
        QMap< QString, QString > listedThemes;
        auto themeList = configurationMap.value( "themes" ).toList();
        // Create the ThemInfo objects for the listed themes; information
        // about the themes from Plasma (e.g. human-readable name and description)
        // are filled in by update_names() in PlasmaLnfPage.
        for ( const auto& i : themeList )
            if ( i.type() == QVariant::Map )
            {
                auto iv = i.toMap();
                listedThemes.insert( iv.value( "theme" ).toString(), iv.value( "image" ).toString() );
            }
            else if ( i.type() == QVariant::String )
            {
                listedThemes.insert( i.toString(), QString() );
            }

        if ( listedThemes.count() == 1 )
        {
            cWarning() << "only one theme enabled in plasmalnf";
        }
        m_themeModel->setThemeImage( listedThemes );

        bool showAll = CalamaresUtils::getBool( configurationMap, "showAll", false );
        if ( !listedThemes.isEmpty() && !showAll )
        {
            m_themeModel->showOnlyThemes( listedThemes );
        }
    }

    m_themeModel->select( m_preselectThemeId );
}

Calamares::JobList
Config::createJobs() const
{
    Calamares::JobList l;

    cDebug() << "Creating Plasma LNF jobs ..";
    if ( !theme().isEmpty() )
    {
        if ( !lnfToolPath().isEmpty() )
        {
            l.append( Calamares::job_ptr( new PlasmaLnfJob( lnfToolPath(), theme() ) ) );
        }
        else
        {
            cWarning() << "no lnftool given for plasmalnf module.";
        }
    }
    return l;
}


void
Config::setTheme( const QString& id )
{
    if ( m_themeId == id )
    {
        return;
    }

    m_themeId = id;
    if ( lnfToolPath().isEmpty() )
    {
        cWarning() << "no lnftool given for plasmalnf module.";
    }
    else
    {
        QStringList command;
        if ( !m_liveUser.isEmpty() )
        {
            command << "sudo"
                    << "-E"
                    << "-H"
                    << "-u" << m_liveUser;
        }
        command << lnfToolPath() << "--resetLayout"
                << "--apply" << id;
        auto r = CalamaresUtils::System::instance()->runCommand( command, std::chrono::seconds( 10 ) );

        if ( r.getExitCode() )
        {
            cWarning() << "Failed (" << r.getExitCode() << ')';
        }
        else
        {
            cDebug() << "Plasma look-and-feel applied" << id;
        }
    }
    m_themeModel->select( id );
    emit themeChanged( id );
}
