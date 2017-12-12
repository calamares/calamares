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

#include "PlasmaLnfPage.h"

#include "ui_page_plasmalnf.h"

#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <KPackage/Package>
#include <KPackage/PackageLoader>

static ThemeInfoList plasma_themes()
{
    ThemeInfoList packages;

    QList<KPluginMetaData> pkgs = KPackage::PackageLoader::self()->listPackages( "Plasma/LookAndFeel" );

    for ( const KPluginMetaData& data : pkgs )
    {
        if ( data.isValid() && !data.isHidden() && !data.name().isEmpty() )
        {
            packages << ThemeInfo{ data.pluginId(), data.name() };
        }
    }

    return packages;
}


PlasmaLnfPage::PlasmaLnfPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::PlasmaLnfPage )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE(
    {
        ui->retranslateUi( this );
        ui->generalExplanation->setText( tr( "Please choose a look-and-feel for the KDE Plasma Desktop, below." ) );
        updateThemeNames();
        fillUi();
    }
    )

    QObject::connect<void( QComboBox::* )( int )>( ui->lnfCombo, &QComboBox::activated, this, &PlasmaLnfPage::activated );
}

void
PlasmaLnfPage::activated( int index )
{
    if ( ( index < 0 ) || ( index > m_enabledThemes.length() ) )
    {
        cDebug() << "Plasma LNF index" << index << "out of range.";
        return;
    }

    const ThemeInfo& lnf = m_enabledThemes.at( index );
    cDebug() << "Changed to" << index << lnf.id << lnf.name;
    emit plasmaThemeSelected( lnf.id );
}

void
PlasmaLnfPage::setLnfPath( const QString& path )
{
    m_lnfPath = path;
}

void
PlasmaLnfPage::setEnabledThemes(const ThemeInfoList& themes)
{
    if ( themes.isEmpty() )
        m_enabledThemes = plasma_themes();
    else
        m_enabledThemes = themes;

    updateThemeNames();
    winnowThemes();
    fillUi();
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
    ui->lnfCombo->clear();
    for ( auto& theme : m_enabledThemes )
    {
        ui->lnfCombo->addItem( theme.name );
    }
}
