/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "groupstreeview.h"

#include "utils/Logger.h"

#include <QPainter>

void
GroupsTreeView::drawBranches( QPainter* painter, const QRect& rect, const QModelIndex& index ) const
{
    QTreeView::drawBranches( painter, rect, index );

    // Empty names are handled specially: don't draw them as items,
    // so the "branch" seems to just pass them by.
    const QString s = index.data().toString();
    if ( s.isEmpty() )
    {
        QStyleOptionViewItem opt = viewOptions();
        opt.state = QStyle::State_Sibling;
        opt.rect = QRect( !isRightToLeft() ? rect.left() : rect.right() + 1, rect.top(), indentation(), rect.height() );
        painter->eraseRect( opt.rect );
        style()->drawPrimitive( QStyle::PE_IndicatorBranch, &opt, painter, this );
    }
}
