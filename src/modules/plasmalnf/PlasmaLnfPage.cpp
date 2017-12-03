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

#include "Branding.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <KPackage/Package>
#include <KPackage/PackageLoader>

#include <QButtonGroup>
#include <QDesktopServices>
#include <QLabel>
#include <QProcess>

static QStringList plasma_themes()
{
    QStringList packages;

    QList<KPluginMetaData> pkgs = KPackage::PackageLoader::self()->listPackages("Plasma/LookAndFeel");

    for (const KPluginMetaData &data : pkgs) {
        packages << data.pluginId();
    }

    return packages;
}


PlasmaLnfPage::PlasmaLnfPage(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::PlasmaLnfPage )
{
    using StringEntry = Calamares::Branding::StringEntry;

    ui->setupUi( this );
    CALAMARES_RETRANSLATE(
        ui->retranslateUi( this );
        ui->generalExplanation->setText( tr( "Please choose a look-and-feel for the KDE Plasma Desktop, below." ) );
    )

    ui->lnfCombo->addItems( plasma_themes() );

    QObject::connect<void(QComboBox::*)(const QString&)>(ui->lnfCombo, &QComboBox::activated, this, &PlasmaLnfPage::activated);
}

void
PlasmaLnfPage::activated(const QString& name)
{
    cDebug() << "Changed to" << name;

    QProcess lnftool;
    lnftool.start( m_lnfPath, {"--resetLayout", "--apply", name} );

    if ( lnftool.waitForStarted(1000) && lnftool.waitForFinished( 1000 ) && (lnftool.exitCode() == 0) && (lnftool.exitStatus() == QProcess::NormalExit ) )
        ; // OK
    else
        cDebug() << "WARNING: could not apply look-and-feel" << name;


    emit plasmaThemeSelected( name );
}

void
PlasmaLnfPage::setLnfPath(const QString& path)
{
    m_lnfPath = path;
}
