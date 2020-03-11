/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "ProgressTreeView.h"

#include "ProgressTreeDelegate.h"

#include "Branding.h"
#include "ViewManager.h"

ProgressTreeView::ProgressTreeView( QWidget* parent )
    : QListView( parent )
{
    this->setObjectName( "sidebarMenuApp" );
    setFrameShape( QFrame::NoFrame );
    setContentsMargins( 0, 0, 0, 0 );

    setSelectionMode( QAbstractItemView::NoSelection );
    setDragDropMode( QAbstractItemView::NoDragDrop );
    setAcceptDrops( false );

    setItemDelegate( new ProgressTreeDelegate( this ) );

    QPalette plt = palette();
    plt.setColor( QPalette::Base,
                  Calamares::Branding::instance()->styleString( Calamares::Branding::SidebarBackground ) );
    setPalette( plt );
}


ProgressTreeView::~ProgressTreeView() {}


void
ProgressTreeView::setModel( QAbstractItemModel* model )
{
    if ( ProgressTreeView::model() )
    {
        return;
    }

    QListView::setModel( model );

    connect(
        Calamares::ViewManager::instance(),
        &Calamares::ViewManager::currentStepChanged,
        this,
        [this]() { viewport()->update(); },
        Qt::UniqueConnection );
}
