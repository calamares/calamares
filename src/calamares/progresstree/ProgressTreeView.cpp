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

#include "ProgressTreeView.h"

#include "ProgressTreeDelegate.h"
#include "ViewManager.h"
#include "Branding.h"

ProgressTreeView* ProgressTreeView::s_instance = nullptr;

ProgressTreeView*
ProgressTreeView::instance()
{
    return s_instance;
}

ProgressTreeView::ProgressTreeView( QWidget* parent )
    : QTreeView( parent )
{
    s_instance = this; //FIXME: should assert when s_instance gets written and it wasn't nullptr

    setFrameShape( QFrame::NoFrame );
    setContentsMargins( 0, 0, 0, 0 );

    setHeaderHidden( true );
    setRootIsDecorated( true );
    setExpandsOnDoubleClick( true );

    setSelectionMode( QAbstractItemView::NoSelection );
    setDragDropMode( QAbstractItemView::NoDragDrop );
    setAcceptDrops( false );
    setUniformRowHeights( false );

    setIndentation( 0 );
    setSortingEnabled( false );

    m_delegate = new ProgressTreeDelegate( this );
    setItemDelegate( m_delegate );

    QPalette plt = palette();
    plt.setColor( QPalette::Base, Calamares::Branding::instance()->
        styleString( Calamares::Branding::SidebarBackground ) );
    setPalette( plt );
}


ProgressTreeView::~ProgressTreeView()
{

}


void
ProgressTreeView::setModel( QAbstractItemModel* model )
{
    if ( ProgressTreeView::model() )
        return;

    QTreeView::setModel( model );
    expandAll();

    connect( Calamares::ViewManager::instance(),
             &Calamares::ViewManager::currentStepChanged,
             this, [this]()
    {
        viewport()->update();
    },
    Qt::UniqueConnection );
}
