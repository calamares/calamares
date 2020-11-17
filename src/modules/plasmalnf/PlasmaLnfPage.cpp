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

#include <KExtraColumnsProxyModel>

#include <QHeaderView>
#include <QStyledItemDelegate>
#include <QTableView>

class ThemeColumns : public KExtraColumnsProxyModel
{
public:
    ThemeColumns( QObject* parent );

    QVariant extraColumnData( const QModelIndex& parent, int row, int extraColumn, int role ) const override;
};

ThemeColumns::ThemeColumns( QObject* parent )
    : KExtraColumnsProxyModel( parent )
{
    appendColumn();
    appendColumn();
}

QVariant
ThemeColumns::extraColumnData( const QModelIndex& parent, int row, int extraColumn, int role ) const
{
    if ( role != Qt::DisplayRole )
    {
        return QVariant();
    }
    switch ( extraColumn )
    {
    case 0:
        return sourceModel()->data( sourceModel()->index( row, 0 ), ThemesModel::DescriptionRole );
    case 1:
        return sourceModel()->data( sourceModel()->index( row, 0 ), ThemesModel::ImageRole );
    default:
        return QVariant();
    }
    __builtin_unreachable();
}


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
    ThemeColumns* model = new ThemeColumns( this );
    model->setSourceModel( m_config->themeModel() );
    view->setModel( model );
    view->verticalHeader()->hide();
    view->horizontalHeader()->hide();
    ui->verticalLayout->addWidget( view );

    connect( view->selectionModel(),
             &QItemSelectionModel::selectionChanged,
             [this]( const QItemSelection& selected, const QItemSelection& ) {
                 auto i = selected.indexes();
                 if ( !i.isEmpty() )
                 {
                     auto row = i.first().row();
                     auto* model = m_config->themeModel();
                     auto id = model->data( model->index( row, 0 ), ThemesModel::KeyRole ).toString();
                     cDebug() << "View selected" << selected << id;
                     if ( !id.isEmpty() )
                     {
                         emit plasmaThemeSelected( id );
                     }
                 }
             } );
}
