/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "CalamaresWindow.h"

#include "progresstree/ProgressTreeView.h"
#include "utils/CalamaresUtilsGui.h"
#include "ViewManager.h"

#include <QBoxLayout>
#include <QLabel>
#include <QTreeView>

CalamaresWindow::CalamaresWindow( QWidget* parent )
    : QWidget( parent )
{
    // Hide close button
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );
    setMinimumSize( 800, 600 );

    QBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    QWidget* sideBox = new QWidget( this );
    mainLayout->addWidget( sideBox );

    QBoxLayout* sideLayout = new QVBoxLayout;
    sideBox->setLayout( sideLayout );
    sideBox->setFixedWidth( 190 ); //FIXME
    sideBox->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    QHBoxLayout* logoLayout = new QHBoxLayout;
    sideLayout->addLayout( logoLayout );
    logoLayout->addStretch();
    QLabel* logoLabel = new QLabel( "branding\ngoes\nhere", sideBox );
    logoLabel->setFixedSize( 80, 80 );
    logoLayout->addWidget( logoLabel );
    logoLayout->addStretch();

    ProgressTreeView* tv = new ProgressTreeView( sideBox );
    sideLayout->addWidget( tv );
    CalamaresUtils::unmarginLayout( sideLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    //This should create a PageManager or ViewManager or whatever, which
    //should control the sidebar, next/back buttons and QSW.
    Calamares::ViewManager* vm = new Calamares::ViewManager( this );

    mainLayout->addWidget( vm->centralWidget() );
}
