/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WELCOME_CHECKER_RESULTDELEGATE_HH
#define WELCOME_CHECKER_RESULTDELEGATE_HH

#include <QStyledItemDelegate>

/**
 * @brief Class for drawing (un)satisfied requirements
 */
class ResultDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

protected:
    QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
};

#endif  // PROGRESSTREEDELEGATE_H
