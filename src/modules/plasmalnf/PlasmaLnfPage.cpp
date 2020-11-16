/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "PlasmaLnfPage.h"

#include "Config.h"
#include "ui_page_plasmalnf.h"

#include "Settings.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QAbstractButton>

#include <KPackage/Package>
#include <KPackage/PackageLoader>

PlasmaLnfPage::PlasmaLnfPage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::PlasmaLnfPage )
    , m_config( config )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE( {
        ui->retranslateUi( this );
        if ( Calamares::Settings::instance()->isSetupMode() )
            ui->generalExplanation->setText( tr( "Please choose a look-and-feel for the KDE Plasma Desktop. "
                                                 "You can also skip this step and configure the look-and-feel "
                                                 "once the system is set up. Clicking on a look-and-feel "
                                                 "selection will give you a live preview of that look-and-feel." ) );
        else
            ui->generalExplanation->setText( tr( "Please choose a look-and-feel for the KDE Plasma Desktop. "
                                                 "You can also skip this step and configure the look-and-feel "
                                                 "once the system is installed. Clicking on a look-and-feel "
                                                 "selection will give you a live preview of that look-and-feel." ) );
    } )
    connect( this, &PlasmaLnfPage::plasmaThemeSelected, config, &Config::setTheme );
}
