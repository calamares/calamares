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
#include "PlasmaLnfInfo.h"

#include "ui_page_plasmalnf.h"

#include "Branding.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <QButtonGroup>
#include <QDesktopServices>
#include <QLabel>

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

    Calamares::themes_by_service();
    ui->lnfCombo->addItems( Calamares::themes_by_lnftool() );
}

