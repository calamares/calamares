/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PROGRESSTREEDELEGATE_H
#define PROGRESSTREEDELEGATE_H

#include <QStyledItemDelegate>

/**
 * @brief The ProgressTreeDelegate class customizes the look and feel of the
 * ProgressTreeView elements.
 * @see ProgressTreeView
 */
class ProgressTreeDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

protected:
    QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
};

#endif  // PROGRESSTREEDELEGATE_H
