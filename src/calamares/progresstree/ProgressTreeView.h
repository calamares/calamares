/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PROGRESSTREEVIEW_H
#define PROGRESSTREEVIEW_H

#include <QListView>

/**
 * @brief The ProgressTreeView class is a modified QTreeView which displays the
 * available view steps and the user's progress through them.
 */
class ProgressTreeView : public QListView
{
    Q_OBJECT
public:
    explicit ProgressTreeView( QWidget* parent = nullptr );
    ~ProgressTreeView() override;

    /**
     * @brief setModel assigns a model to this view.
     */
    void setModel( QAbstractItemModel* model ) override;
};

#endif  // PROGRESSTREEVIEW_H
