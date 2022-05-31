/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ResultDelegate.h"

#include "modulesystem/RequirementsModel.h"
#include "utils/CalamaresUtilsGui.h"

#include <QApplication>
#include <QPainter>

static constexpr int const item_margin = 8;
static inline int
item_fontsize()
{
    return CalamaresUtils::defaultFontSize() + 4;
}

static void
paintRequirement( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, int role )
{
    const auto fontsize = item_fontsize();

    QRect textRect = option.rect.adjusted( item_margin, item_margin, -item_margin, -item_margin );
    QFont font = qApp->font();
    font.setPointSize( fontsize );
    font.setBold( false );
    painter->setFont( font );

    CalamaresUtils::ImageType statusImage = CalamaresUtils::StatusOk;

    painter->setPen( QColorConstants::Black );
    if ( index.data( Calamares::RequirementsModel::Satisfied ).toBool() )
    {
        painter->fillRect( textRect, option.palette.window().color() );
    }
    else
    {
        if ( index.data( Calamares::RequirementsModel::Mandatory ).toBool() )
        {
            QColor bgColor = option.palette.window().color();
            bgColor.setHsv( 0, 64, bgColor.value() );
            painter->fillRect( option.rect, bgColor );
            statusImage = CalamaresUtils::StatusError;
        }
        else
        {
            QColor bgColor = option.palette.window().color();
            bgColor.setHsv( 60, 64, bgColor.value() );
            painter->fillRect( option.rect, bgColor );
            statusImage = CalamaresUtils::StatusWarning;
        }
    }

    auto image
        = CalamaresUtils::defaultPixmap( statusImage, CalamaresUtils::Original, QSize( 2 * fontsize, 2 * fontsize ) )
              .toImage();
    painter->drawImage( textRect.topLeft(), image );

    // Leave space for that image (already drawn)
    textRect.moveLeft( 2 * fontsize + 2 * item_margin );
    painter->drawText( textRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, index.data( role ).toString() );
}

QSize
ResultDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    if ( !index.isValid() )
    {
        return option.rect.size();
    }

    QFont font = qApp->font();

    font.setPointSize( item_fontsize() );
    QFontMetrics fm( font );

    const int height = fm.height() + 2 * item_margin;
    int textwidth = fm.boundingRect( index.data( Calamares::RequirementsModel::NegatedText ).toString() ).width();

    return QSize( qMax( option.rect.width(), textwidth ), height );
}


void
ResultDelegate::paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const
{
    QStyleOptionViewItem opt = option;

    painter->save();

    initStyleOption( &opt, index );
    opt.text.clear();

    paintRequirement( painter, opt, index, m_textRole );

    painter->restore();
}
