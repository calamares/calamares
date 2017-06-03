/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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
    Q_OBJECT
public:
    explicit ProgressTreeDelegate( QAbstractItemView* parent = nullptr );

protected:
    QSize sizeHint( const QStyleOptionViewItem& option,
                    const QModelIndex& index ) const override;
    void paint( QPainter* painter,
                const QStyleOptionViewItem& option,
                const QModelIndex& index ) const override;

private:
    void paintViewStep( QPainter* painter,
                        const QStyleOptionViewItem& option,
                        const QModelIndex& index ) const;

    QAbstractItemView* m_parent;
};

#endif // PROGRESSTREEDELEGATE_H
