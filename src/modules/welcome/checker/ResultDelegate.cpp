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
    QRect textRect = option.rect.adjusted( item_margin, item_margin, -item_margin, -item_margin );
    QFont font = qApp->font();
    font.setPointSize( item_fontsize() );
    font.setBold( false );
    painter->setFont( font );

    if ( index.data( Calamares::RequirementsModel::Satisfied ).toBool() )
    {
        painter->setBrush( QColorConstants::Green );
        painter->setPen( QColorConstants::Black );
    }
    else
    {
        if ( index.data( Calamares::RequirementsModel::Mandatory ).toBool() )
        {
            painter->setPen( QColorConstants::Red );
        }
        else
        {
            painter->setPen( QColorConstants::Blue );
        }
    }

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
    int height = fm.height();

    height += 2 * item_margin;

    return QSize( option.rect.width(), height );
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
