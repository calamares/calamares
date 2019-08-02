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

PackageChooserPage::PackageChooserPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::PackageChooserPage )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE( updateLabels(); )
}

void
PackageChooserPage::updateLabels()
{
    ui->productName->setText( QString() );
    ui->productScreenshot->hide();
    ui->productDescription->setText( tr( "Please pick a product from the list." ) );
}

void
PackageChooserPage::setModel( QAbstractItemModel* model )
{
    ui->products->setModel( model );
}

void
PackageChooserPage::currentChanged( const QModelIndex& current )
{
    updateLabels();
    cDebug() << "Current updated to" << current.row();
    cDebug() << ui->products->model()->data( current, Qt::DisplayRole );
}
