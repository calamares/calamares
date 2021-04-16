/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PACKAGECHOOSERPAGE_H
#define PACKAGECHOOSERPAGE_H

#include "Config.h"
#include "PackageModel.h"

#include <QAbstractItemModel>
#include <QWidget>

namespace Ui
{
class PackageChooserPage;
}

class PackageChooserPage : public QWidget
{
    Q_OBJECT
public:
    explicit PackageChooserPage( PackageChooserMode mode, QWidget* parent = nullptr );

    /// @brief Sets the data model for the listview
    void setModel( QAbstractItemModel* model );

    /// @brief Sets the introductory (no-package-selected) texts
    void setIntroduction( const PackageItem& item );
    /// @brief Selects a listview item
    void setSelection( const QModelIndex& index );
    /// @brief Is anything selected?
    bool hasSelection() const;
    /** @brief Get the list of selected ids
     *
     * This list may be empty (if none is selected).
     */
    QStringList selectedPackageIds() const;

public slots:
    void currentChanged( const QModelIndex& index );
    void updateLabels();

signals:
    void selectionChanged();

private:
    Ui::PackageChooserPage* ui;
    PackageItem m_introduction;
};

#endif  // PACKAGECHOOSERPAGE_H
