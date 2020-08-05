/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
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
 *
 *
 */

#ifndef LOCALE_TIMEZONE_H
#define LOCALE_TIMEZONE_H

#include "DllMacro.h"

#include <QAbstractListModel>
#include <QObject>
#include <QSortFilterProxyModel>
#include <QVariant>

namespace CalamaresUtils
{
namespace Locale
{
struct Private;

/** @brief The list of timezone regions
 *
 * The regions are a short list of global areas (Africa, America, India ..)
 * which contain zones.
 */
class DLLEXPORT RegionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        NameRole = Qt::DisplayRole,
        KeyRole = Qt::UserRole + 1
    };

    RegionsModel( QObject* parent = nullptr );
    virtual ~RegionsModel() override;

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    QHash< int, QByteArray > roleNames() const override;

private:
    Private* m_private;
};

class DLLEXPORT ZonesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        NameRole = Qt::DisplayRole,
        KeyRole = Qt::UserRole + 1
    };

    ZonesModel( QObject* parent = nullptr );
    virtual ~ZonesModel() override;

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    QHash< int, QByteArray > roleNames() const override;

private:
    Private* m_private;
};

class DLLEXPORT RegionalZonesModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY( QString region READ region WRITE setRegion NOTIFY regionChanged )

public:
    RegionalZonesModel( ZonesModel* source, QObject* parent = nullptr );
    ~RegionalZonesModel() override;

    bool filterAcceptsRow( int sourceRow, const QModelIndex& sourceParent ) const override;

    QString region() const { return m_region; }

public Q_SLOTS:
    void setRegion( const QString& r );

signals:
    void regionChanged( const QString& );

private:
    Private* m_private;
    QString m_region;
};


}  // namespace Locale
}  // namespace CalamaresUtils

#endif  // LOCALE_TIMEZONE_H
