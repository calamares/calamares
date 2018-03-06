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

#include "PlasmaLnfPage.h"

#include "ui_page_plasmalnf.h"

#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <KPackage/Package>
#include <KPackage/PackageLoader>

ThemeInfo::ThemeInfo( const KPluginMetaData& data )
    : id( data.pluginId() )
    , name( data.name() )
    , description( data.description() )
    , widget( nullptr )
{
}

static ThemeInfoList plasma_themes()
{
    ThemeInfoList packages;

    QList<KPluginMetaData> pkgs = KPackage::PackageLoader::self()->listPackages( "Plasma/LookAndFeel" );

    for ( const KPluginMetaData& data : pkgs )
    {
        if ( data.isValid() && !data.isHidden() && !data.name().isEmpty() )
        {
            packages << ThemeInfo{ data };
        }
    }

    return packages;
}


PlasmaLnfPage::PlasmaLnfPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::PlasmaLnfPage )
    , m_buttonGroup( nullptr )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE(
    {
        ui->retranslateUi( this );
        ui->generalExplanation->setText( tr( "Please choose a look-and-feel for the KDE Plasma Desktop. You can also skip this step and configure the look-and-feel once the system is installed." ) );
        updateThemeNames();
        fillUi();
    }
    )
}

void
PlasmaLnfPage::setLnfPath( const QString& path )
{
    m_lnfPath = path;
}

void
PlasmaLnfPage::setEnabledThemes(const ThemeInfoList& themes)
{
    m_enabledThemes = themes;

    updateThemeNames();
    winnowThemes();
    fillUi();
}

void
PlasmaLnfPage::setEnabledThemesAll()
{
    setEnabledThemes( plasma_themes() );
}


void PlasmaLnfPage::updateThemeNames()
{
    auto plasmaThemes = plasma_themes();
    for ( auto& enabled_theme : m_enabledThemes )
    {
        ThemeInfo* t = plasmaThemes.findById( enabled_theme.id );
        if ( t != nullptr )
        {
            enabled_theme.name = t->name;
            enabled_theme.description = t->description;
        }
    }
}

void PlasmaLnfPage::winnowThemes()
{
    auto plasmaThemes = plasma_themes();
    bool winnowed = true;
    int winnow_index = 0;
    while ( winnowed )
    {
        winnowed = false;
        winnow_index = 0;

        for ( auto& enabled_theme : m_enabledThemes )
        {
            ThemeInfo* t = plasmaThemes.findById( enabled_theme.id );
            if ( t == nullptr )
            {
                cDebug() << "Removing" << enabled_theme.id;
                winnowed = true;
                break;
            }
            ++winnow_index;
        }

        if ( winnowed )
        {
            m_enabledThemes.removeAt( winnow_index );
        }
    }
}

void PlasmaLnfPage::fillUi()
{
    if ( m_enabledThemes.isEmpty() )
    {
        return;
    }

    if ( !m_buttonGroup )
    {
        m_buttonGroup = new QButtonGroup( this );
        m_buttonGroup->setExclusive( true );
    }

    int c = 1; // After the general explanation
    for ( auto& theme : m_enabledThemes )
    {
        if ( !theme.widget )
        {
            ThemeWidget* w = new ThemeWidget( theme );
            m_buttonGroup->addButton( w->button() );
            ui->verticalLayout->insertWidget( c, w );
            connect( w, &ThemeWidget::themeSelected, this, &PlasmaLnfPage::plasmaThemeSelected);
            theme.widget = w;
        }
        else
        {
            theme.widget->updateThemeName( theme );
        }
        ++c;
    }
}
