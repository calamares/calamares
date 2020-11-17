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

#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QTableView>

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

    QTableView* view = new QTableView( this );
    view->verticalHeader()->hide();
    view->horizontalHeader()->hide();
    view->setModel( m_config->themeModel() );
    ui->verticalLayout->addWidget( view );

    connect( view->selectionModel(),
             &QItemSelectionModel::selectionChanged,
             [this]( const QItemSelection& selected, const QItemSelection& ) {
                 auto i = selected.indexes();
                 if ( !i.isEmpty() )
                 {
                     auto* model = m_config->themeModel();
                     auto id = model->data( i.first(), ThemesModel::KeyRole ).toString();
                     cDebug() << "View selected" << selected << id;
                     if ( !id.isEmpty() )
                     {
                         emit plasmaThemeSelected( id );
                     }
                 }
             } );
}
