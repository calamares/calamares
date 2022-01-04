/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @file Timezone data and models to go with it
 *
 * The TimeZoneData class holds information from zone.tab, about
 * TZ names and locations (latitude and longitude) for geographic
 * lookups.
 *
 * The RegionModel lists the regions of the world (about 12) and
 * ZonesModel lists all the timezones; the RegionalZonesModel provides
 * a way to restrict the view of timezones to those of a specific region.
 *
 */
#ifndef LOCALE_TIMEZONE_H
#define LOCALE_TIMEZONE_H

#include "DllMacro.h"

#include "locale/TranslatableString.h"

#include <QAbstractListModel>
#include <QObject>
#include <QSortFilterProxyModel>
#include <QVariant>

namespace CalamaresUtils
{
namespace Locale
{
class Private;
class RegionalZonesModel;
class ZonesModel;

class TimeZoneData : public QObject, TranslatableString
{
    friend class RegionalZonesModel;
    friend class ZonesModel;

    Q_OBJECT

    Q_PROPERTY( QString region READ region CONSTANT )
    Q_PROPERTY( QString zone READ zone CONSTANT )
    Q_PROPERTY( QString name READ tr CONSTANT )
    Q_PROPERTY( QString countryCode READ country CONSTANT )

public:
    TimeZoneData( const QString& region,
                  const QString& zone,
                  const QString& country,
                  double latitude,
                  double longitude );
    TimeZoneData( const TimeZoneData& ) = delete;
    TimeZoneData( TimeZoneData&& ) = delete;

    QString tr() const override;

    QString region() const { return m_region; }
    QString zone() const { return key(); }

    QString country() const { return m_country; }
    double latitude() const { return m_latitude; }
    double longitude() const { return m_longitude; }

private:
    QString m_region;
    QString m_country;
    double m_latitude;
    double m_longitude;
};


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
        KeyRole = Qt::UserRole  // So that currentData() will get the key
    };

    RegionsModel( QObject* parent = nullptr );
    ~RegionsModel() override;

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    QHash< int, QByteArray > roleNames() const override;

public Q_SLOTS:
    /** @brief Provides a human-readable version of the region
     *
     * Returns @p region unchanged if there is no such region
     * or no translation for the region's name.
     */
    QString tr( const QString& region ) const;

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
        KeyRole = Qt::UserRole,  // So that currentData() will get the key
        RegionRole = Qt::UserRole + 1
    };

    ZonesModel( QObject* parent = nullptr );
    ~ZonesModel() override;

    int rowCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    QHash< int, QByteArray > roleNames() const override;

    /** @brief Iterator for the underlying list of zones
     *
     * Iterates over all the zones in the model. Operator * may return
     * a @c nullptr when the iterator is not valid. Typical usage:
     *
     * ```
     * for( auto it = model.begin(); it; ++it )
     * {
     *     const auto* zonedata = *it;
     *     ...
     * }
     */
    class Iterator
    {
        friend class ZonesModel;
        Iterator( const Private* m )
            : m_index( 0 )
            , m_p( m )
        {
        }

    public:
        operator bool() const;
        void operator++() { ++m_index; }
        const TimeZoneData* operator*() const;
        int index() const { return m_index; }

    private:
        int m_index;
        const Private* m_p;
    };

    Iterator begin() const { return Iterator( m_private ); }

    /** @brief Look up TZ data based on an arbitrary distance function
     *
     * This is a generic method that can define distance in whatever
     * coordinate system is wanted; returns the zone with the smallest
     * distance. The @p distanceFunc must return "the distance" for
     * each zone. It would be polite to return something non-negative.
     *
     * Note: not a slot, because the parameter isn't moc-able.
     */
    const TimeZoneData* find( const std::function< double( const TimeZoneData* ) >& distanceFunc ) const;

public Q_SLOTS:
    /** @brief Look up TZ data based on its name.
     *
     * Returns @c nullptr if not found.
     */
    const TimeZoneData* find( const QString& region, const QString& zone ) const;

    /** @brief Look up TZ data based on the location.
     *
     * Returns the nearest zone to the given lat and lon. This is a
     * convenience function for calling find(), below, with a standard
     * distance function based on the distance between the given
     * location (lat and lon) and each zone's given location.
     */
    const TimeZoneData* find( double latitude, double longitude ) const;

    /** @brief Look up TZ data based on the location.
     *
     * Returns the nearest zone, or New York. This is non-const for QML
     * purposes, but the object should be considered const anyway.
     */
    QObject* lookup( double latitude, double longitude ) const;

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
