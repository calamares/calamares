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

static PlasmaLnfList plasma_themes()
{
    PlasmaLnfList packages;

    QList<KPluginMetaData> pkgs = KPackage::PackageLoader::self()->listPackages( "Plasma/LookAndFeel" );

    for ( const KPluginMetaData& data : pkgs )
    {
        packages << PlasmaLnfDescriptor{ data.pluginId(), data.name() };
        cDebug() << "LNF Package" << data.pluginId();
        cDebug() << "  .." << data.name();
        cDebug() << "  .." << data.description();
        cDebug() << "  .." << 'V' << data.isValid() << 'H' << data.isHidden() << 'D' << data.isEnabledByDefault();
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
        m_availableLnf = plasma_themes();
        ui->lnfCombo->clear();
        for ( const auto& p : m_availableLnf )
            ui->lnfCombo->addItem( p.name );
    }
    )

    QObject::connect<void( QComboBox::* )( int )>( ui->lnfCombo, &QComboBox::activated, this, &PlasmaLnfPage::activated );
}

void
PlasmaLnfPage::activated( int index )
{
    if ( ( index < 0 ) || ( index > m_availableLnf.length() ) )
    {
        cDebug() << "Plasma LNF index" << index << "out of range.";
        return;
    }

    const PlasmaLnfDescriptor& lnf = m_availableLnf.at( index );
    cDebug() << "Changed to" << index << lnf.id << lnf.name;
    emit plasmaThemeSelected( lnf.id );
}

void
PlasmaLnfPage::setLnfPath( const QString& path )
{
    m_lnfPath = path;
}
