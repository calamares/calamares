/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include <QTreeView>

class GroupsTreeView : public QTreeView
{
public:
    using QTreeView::QTreeView;

protected:
    virtual void drawBranches( QPainter* painter, const QRect& rect, const QModelIndex& index ) const override;
};
