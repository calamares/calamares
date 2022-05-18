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
#include <QListView>
#include <QStyledItemDelegate>

class ThemeDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    // The size of the item is constant
    QSize sizeHint( const QStyleOptionViewItem&, const QModelIndex& ) const override;
};

QSize
ThemeDelegate::sizeHint( const QStyleOptionViewItem&, const QModelIndex& ) const
{
    QSize image( ThemesModel::imageSize() );
    return { 3 * image.width(), image.height() };
}

void
ThemeDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    auto label = index.data( ThemesModel::LabelRole ).toString();
    auto description = index.data( ThemesModel::DescriptionRole ).toString();
    auto selected = index.data( ThemesModel::SelectedRole ).toBool() ? QStyle::State_On : QStyle::State_Off;
    auto image_v = index.data( ThemesModel::ImageRole );
    QPixmap image = image_v.canConvert< QPixmap >() ? qvariant_cast< QPixmap >( image_v ) : QPixmap();

    // The delegate paints three "columns", each of which takes 1/3
    // of the space: label, description and screenshot.
    QRect labelRect( option.rect );
    labelRect.setWidth( labelRect.width() / 3 );

    QStyleOptionButton rbOption;
    rbOption.state |= QStyle::State_Enabled | selected;
    rbOption.rect = labelRect;
    rbOption.text = label;
    option.widget->style()->drawControl( QStyle::CE_RadioButton, &rbOption, painter, option.widget );

    labelRect.moveLeft( labelRect.width() );
    option.widget->style()->drawItemText(
        painter, labelRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, option.palette, false, description );

    labelRect.moveLeft( 2 * labelRect.width() );
    option.widget->style()->drawItemPixmap( painter, labelRect, Qt::AlignHCenter | Qt::AlignVCenter, image );
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
    } );

    auto* view = new QListView( this );
    view->setModel( m_config->themeModel() );
    view->setItemDelegate( new ThemeDelegate( view ) );
    view->setUniformItemSizes( true );
    view->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    ui->verticalLayout->addWidget( view );

    connect( view->selectionModel(),
             &QItemSelectionModel::selectionChanged,
             [ this ]( const QItemSelection& selected, const QItemSelection& )
             {
                 auto i = selected.indexes();
                 if ( !i.isEmpty() )
                 {
                     auto row = i.first().row();
                     auto* model = m_config->themeModel();
                     auto id = model->data( model->index( row, 0 ), ThemesModel::KeyRole ).toString();
                     if ( !id.isEmpty() )
                     {
                         m_config->setTheme( id );
                     }
                 }
             } );
}
