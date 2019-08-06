/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "PackageChooserPage.h"

#include "ui_page_package.h"

#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QLabel>

PackageChooserPage::PackageChooserPage( PackageChooserMode mode, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::PackageChooserPage )
    , m_introduction( QString(),
                      QString(),
                      tr( "Package Selection" ),
                      tr( "Please pick a product from the list. The selected product will be installed." ) )
{
    m_introduction.screenshot = QPixmap( QStringLiteral( ":/images/no-selection.png" ) );

    ui->setupUi( this );
    CALAMARES_RETRANSLATE( updateLabels(); )

    switch ( mode )
    {
    case PackageChooserMode::Optional:
        FALLTHRU;
    case PackageChooserMode::Required:
        ui->products->setSelectionMode( QAbstractItemView::SingleSelection );
        break;
    case PackageChooserMode::OptionalMultiple:
        FALLTHRU;
    case PackageChooserMode::RequiredMultiple:
        ui->products->setSelectionMode( QAbstractItemView::ExtendedSelection );
    }
}

void
PackageChooserPage::currentChanged( const QModelIndex& index )
{
    if ( !index.isValid() || !ui->products->selectionModel()->hasSelection() )
    {
        ui->productName->setText( m_introduction.name.get() );
        ui->productScreenshot->setPixmap( m_introduction.screenshot );
        ui->productDescription->setText( m_introduction.description.get() );
    }
    else
    {
        const auto* model = ui->products->model();

        ui->productName->setText( model->data( index, PackageListModel::NameRole ).toString() );
        ui->productScreenshot->setPixmap( model->data( index, PackageListModel::ScreenshotRole ).value< QPixmap >() );
        ui->productDescription->setText( model->data( index, PackageListModel::DescriptionRole ).toString() );
    }
}

void
PackageChooserPage::updateLabels()
{
    if ( ui && ui->products && ui->products->selectionModel() )
    {
        currentChanged( ui->products->selectionModel()->currentIndex() );
    }
    else
    {
        currentChanged( QModelIndex() );
    }
    emit selectionChanged();
}

void
PackageChooserPage::setModel( QAbstractItemModel* model )
{
    ui->products->setModel( model );

    // Check if any of the items in the model is the "none" option.
    // If so, copy its values into the introduction / none item.
    for ( int r = 0; r < model->rowCount(); ++r )
    {
        auto index = model->index( r, 0 );
        if ( index.isValid() )
        {
            QVariant v = model->data( index, PackageListModel::IdRole );
            if ( v.isValid() && v.toString().isEmpty() )
            {
                m_introduction.name = model->data( index, PackageListModel::NameRole ).toString();
                m_introduction.description = model->data( index, PackageListModel::DescriptionRole ).toString();
                m_introduction.screenshot = model->data( index, PackageListModel::ScreenshotRole ).value< QPixmap >();
                currentChanged( QModelIndex() );
                break;
            }
        }
    }

    connect( ui->products->selectionModel(),
             &QItemSelectionModel::selectionChanged,
             this,
             &PackageChooserPage::updateLabels );
}

bool
PackageChooserPage::hasSelection() const
{
    return ui && ui->products && ui->products->selectionModel() && ui->products->selectionModel()->hasSelection();
}

QStringList
PackageChooserPage::selectedPackageIds() const
{
    if ( !( ui && ui->products && ui->products->selectionModel() ) )
    {
        return QStringList();
    }

    const auto* model = ui->products->model();
    QStringList ids;
    for ( const auto& index : ui->products->selectionModel()->selectedIndexes() )
    {
        QString pid = model->data( index, PackageListModel::IdRole ).toString();
        if ( !pid.isEmpty() )
        {
            ids.append( pid );
        }
    }
    return ids;
}
