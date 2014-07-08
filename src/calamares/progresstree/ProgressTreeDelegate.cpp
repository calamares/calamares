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

#include "ProgressTreeDelegate.h"

#include "../CalamaresApplication.h"
#include "../CalamaresWindow.h"
#include "ViewStepItem.h"
#include "ProgressTreeModel.h"
#include "ViewManager.h"
#include "utils/CalamaresStyle.h"
#include "utils/CalamaresUtilsGui.h"

#include <QAbstractItemView>
#include <QPainter>

#define ITEM_MARGIN 12
#define VS_FONTSIZE CalamaresUtils::defaultFontSize() + 2
#define CAT_FONTSIZE CalamaresUtils::defaultFontSize() + 5

ProgressTreeDelegate::ProgressTreeDelegate( QAbstractItemView* parent )
    : QStyledItemDelegate( parent )
    , m_parent( parent )
{
}


QSize
ProgressTreeDelegate::sizeHint( const QStyleOptionViewItem& option,
                                const QModelIndex& index ) const
{
    ProgressTreeModel::RowType type =
            static_cast< ProgressTreeModel::RowType >(
                index.data( ProgressTreeModel::ProgressTreeItemTypeRole ).toInt() );
    if ( type == ProgressTreeModel::Invalid )
        return option.rect.size();

    QFont font = qApp->font();

    if ( type == ProgressTreeModel::Category )
    {
        font.setPointSize( CAT_FONTSIZE );
    }
    else if ( type == ProgressTreeModel::ViewStep )
    {
        font.setPointSize( VS_FONTSIZE );
    }
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
    QStyleOptionViewItemV4 opt = option;

    painter->save();

    ProgressTreeModel::RowType type =
            static_cast< ProgressTreeModel::RowType >(
                index.data( ProgressTreeModel::ProgressTreeItemTypeRole ).toInt() );
    if ( type == ProgressTreeModel::Invalid )
        return;

    initStyleOption( &opt, index );
    opt.text.clear();

    painter->setBrush( CalamaresStyle::SIDEBAR_BACKGROUND );
    painter->setPen( CalamaresStyle::SIDEBAR_TEXT );

    if ( type == ProgressTreeModel::Category )
        paintCategory( painter, opt, index );
    else if ( type == ProgressTreeModel::ViewStep )
        paintViewStep( painter, opt, index );

    painter->restore();
}


void
ProgressTreeDelegate::paintCategory( QPainter* painter,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index ) const
{
    QRect textRect = option.rect.adjusted( ITEM_MARGIN,
                                           ITEM_MARGIN,
                                           ITEM_MARGIN,
                                           ITEM_MARGIN );

    QFont font = qApp->font();
    font.setPointSize( CAT_FONTSIZE );
    font.setBold( false );
    painter->setFont( font );

    painter->drawText( textRect, index.data().toString() );
}


void
ProgressTreeDelegate::paintViewStep( QPainter* painter,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index ) const
{
    QRect textRect = option.rect.adjusted( ITEM_MARGIN + 32 /*indentation*/,
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
        painter->setPen( CalamaresStyle::SIDEBAR_BACKGROUND );
        painter->setBrush( APP->mainWindow()->palette().background() );
    }

    painter->fillRect( option.rect, painter->brush().color() );
    painter->drawText( textRect, index.data().toString() );
}
