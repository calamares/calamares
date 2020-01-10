/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef PACKAGECHOOSERPAGE_H
#define PACKAGECHOOSERPAGE_H

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
