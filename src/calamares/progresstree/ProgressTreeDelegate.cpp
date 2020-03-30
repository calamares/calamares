/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "Branding.h"
#include "CalamaresApplication.h"
#include "CalamaresWindow.h"
#include "ViewManager.h"
#include "utils/CalamaresUtilsGui.h"

#include <QPainter>

static constexpr int const item_margin = 8;
static inline int
item_fontsize()
{
    return CalamaresUtils::defaultFontSize() + 4;
}

QSize
ProgressTreeDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    if ( !index.isValid() )
    {
        return option.rect.size();
    }

    QFont font = qApp->font();

    font.setPointSize( item_fontsize() );
    QFontMetrics fm( font );
    int height = fm.height();

    height += 2 * item_margin;

    return QSize( option.rect.width(), height );
}


void
ProgressTreeDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionViewItem opt = option;

    painter->save();

    initStyleOption( &opt, index );
    opt.text.clear();

    painter->setBrush(
        QColor( Calamares::Branding::instance()->styleString( Calamares::Branding::SidebarBackground ) ) );
    painter->setPen( QColor( Calamares::Branding::instance()->styleString( Calamares::Branding::SidebarText ) ) );

    paintViewStep( painter, opt, index );

    painter->restore();
}


void
ProgressTreeDelegate::paintViewStep( QPainter* painter,
                                     const QStyleOptionViewItem& option,
                                     const QModelIndex& index ) const
{
    QRect textRect = option.rect.adjusted( item_margin, item_margin, -item_margin, -item_margin );
    QFont font = qApp->font();
    font.setPointSize( item_fontsize() );
    font.setBold( false );
    painter->setFont( font );

    if ( index.row() == index.data( Calamares::ViewManager::ProgressTreeItemCurrentIndex ).toInt() )
    {
        painter->setPen( Calamares::Branding::instance()->styleString( Calamares::Branding::SidebarTextSelect ) );
        QString textHighlight
            = Calamares::Branding::instance()->styleString( Calamares::Branding::SidebarTextHighlight );
        if ( textHighlight.isEmpty() )
        {
            painter->setBrush( CalamaresApplication::instance()->mainWindow()->palette().window() );
        }
        else
        {
            painter->setBrush( QColor( textHighlight ) );
        }
    }


    // Draw the text at least once. If it doesn't fit, then shrink the font
    // being used by 1 pt on each iteration, up to a maximum of maximumShrink
    // times. On each loop, we'll have to blank out the rectangle again, so this
    // is an expensive (in terms of drawing operations) thing to do.
    //
    // (The loop uses <= because the counter is incremented at the start).
    static constexpr int const maximumShrink = 4;
    int shrinkSteps = 0;
    do
    {
        painter->fillRect( option.rect, painter->brush().color() );
        shrinkSteps++;

        QRectF boundingBox;
        painter->drawText(
            textRect, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, index.data().toString(), &boundingBox );

        // The extra check here is to avoid the changing-font-size if we're not going to use
        // it in the next iteration of the loop anyway.
        if ( ( shrinkSteps <= maximumShrink ) && ( boundingBox.width() > textRect.width() ) )
        {
            font.setPointSize( item_fontsize() - shrinkSteps );
            painter->setFont( font );
        }
        else
        {
            break;  // It fits
        }
    } while ( shrinkSteps <= maximumShrink );
}
