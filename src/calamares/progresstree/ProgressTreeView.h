/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef PROGRESSTREEVIEW_H
#define PROGRESSTREEVIEW_H

#include <QTreeView>

class ProgressTreeDelegate;

/**
 * @brief The ProgressTreeView class is a modified QTreeView which displays the
 * available view steps and the user's progress through them.
 * @note singleton, only access through ProgressTreeView::instance().
 */
class ProgressTreeView : public QTreeView
{
    Q_OBJECT
public:
    static ProgressTreeView* instance();

    explicit ProgressTreeView( QWidget* parent = nullptr );
    virtual ~ProgressTreeView() override;

    /**
     * @brief setModel assigns a model to this view.
     */
    void setModel( QAbstractItemModel* model ) override;

private:
    static ProgressTreeView* s_instance;
    ProgressTreeDelegate* m_delegate;
};

#endif // PROGRESSTREEVIEW_H
