/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "ProgressTreeDelegate.h"

#include "../CalamaresApplication.h"
#include "../CalamaresWindow.h"
#include "ViewStepItem.h"
#include "ProgressTreeModel.h"
#include "ViewManager.h"
#include "Branding.h"
#include "utils/CalamaresUtilsGui.h"

#include <QAbstractItemView>
#include <QPainter>

#define ITEM_MARGIN 12
#define VS_FONTSIZE CalamaresUtils::defaultFontSize() + 4

ProgressTreeDelegate::ProgressTreeDelegate( QAbstractItemView* parent )
    : QStyledItemDelegate( parent )
    , m_parent( parent )
{
}


QSize
ProgressTreeDelegate::sizeHint( const QStyleOptionViewItem& option,
                                const QModelIndex& index ) const
{
    if ( !index.isValid() )
        return option.rect.size();

    QFont font = qApp->font();

    font.setPointSize( VS_FONTSIZE );
    QFontMetrics fm( font );
    int height = fm.height();

    height += 2*ITEM_MARGIN; //margin

    return QSize( option.rect.width(), height );
}


void
ProgressTreeDelegate::paint( QPainter* painter,
                             const QStyleOptionViewItem& option,
                             const QModelIndex& index) const
{
    QStyleOptionViewItem opt = option;

    painter->save();

    initStyleOption( &opt, index );
    opt.text.clear();

    painter->setBrush( QColor( Calamares::Branding::instance()->
        styleString( Calamares::Branding::SidebarBackground ) ) );
    painter->setPen( QColor( Calamares::Branding::instance()->
        styleString( Calamares::Branding::SidebarText ) ) );

    paintViewStep( painter, opt, index );

    painter->restore();
}


void
ProgressTreeDelegate::paintViewStep( QPainter* painter,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index ) const
{
    QRect textRect = option.rect.adjusted( ITEM_MARGIN,
                                           ITEM_MARGIN,
                                           ITEM_MARGIN,
                                           ITEM_MARGIN );
    QFont font = qApp->font();
    font.setPointSize( VS_FONTSIZE );
    font.setBold( false );
    painter->setFont( font );

    bool isCurrent = false;
    isCurrent = index.data( ProgressTreeModel::ProgressTreeItemCurrentRole ).toBool();

    if ( isCurrent )
    {
        painter->setPen( Calamares::Branding::instance()->
                         styleString( Calamares::Branding::SidebarTextSelect ) );
        QString textHighlight = Calamares::Branding::instance()->
                           styleString( Calamares::Branding::SidebarTextHighlight );
        if ( textHighlight.isEmpty() )
            painter->setBrush( APP->mainWindow()->palette().background() );
        else
            painter->setBrush( QColor( textHighlight ) );
    }

    painter->fillRect( option.rect, painter->brush().color() );
    painter->drawText( textRect, index.data().toString() );
}
