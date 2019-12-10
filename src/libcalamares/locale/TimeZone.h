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

#ifndef LOCALE_TIMEZONE_H
#define LOCALE_TIMEZONE_H

#include "DllMacro.h"

#include "utils/Logger.h"

#include <QAbstractListModel>
#include <QObject>
#include <QString>

#include <memory>

namespace CalamaresUtils
{
namespace Locale
{

/** @brief A pair of strings, one human-readable, one a key
 *
 * Given an identifier-like string (e.g. "New_York"), makes
 * a human-readable version of that and keeps a copy of the
 * identifier itself.
 *
 * This explicitly uses const char* instead of just being
 * QPair<QString, QString> because there is API that needs
 * C-style strings.
 */
class CStringPair
{
public:
    /// @brief An empty pair
    CStringPair() {};
    /// @brief Given an identifier, create the pair
    explicit CStringPair( const char* s1 );
    CStringPair( CStringPair&& t );
    CStringPair( const CStringPair& );
    virtual ~CStringPair();

    /// @brief Give the localized human-readable form
    virtual QString tr() const = 0;

    QString key() const { return m_key; }

protected:
    char* m_human = nullptr;
    QString m_key;
};

class TZZone;
class TZRegion;
using TZZoneList = QList< TZZone* >;
using TZRegionList = QList< TZRegion* >;

/// @brief A pair of strings for timezone regions (e.g. "America")
class TZRegion : public CStringPair
{
public:
    using CStringPair::CStringPair;
    virtual ~TZRegion();
    QString tr() const override;

    bool operator<( const TZRegion& other ) const { return m_key < other.m_key; }

    /** @brief Create model from a zone.tab-like file
     *
     * Returns a list of all the regions; each region has a list
     * of zones within that region.
     *
     * The list owns the regions, and the regions own their own list of zones.
     * When getting rid of the list, remember to qDeleteAll() on it.
     */
    static TZRegionList fromFile( const char* fileName );
    /// @brief Calls fromFile with the standard zone.tab name
    static TZRegionList fromZoneTab();

private:
    TZZoneList m_zones;
};

/// @brief A pair of strings for specific timezone names (e.g. "New_York")
class TZZone : public CStringPair
{
public:
    using CStringPair::CStringPair;
    QString tr() const override;

    TZZone( const char* zoneName, const QString& country, QString position );

    void print( QDebug& ) const;

protected:
    QString m_country;
    double m_latitude = 0.0, m_longitude = 0.0;
};

inline QDebug&
operator<<( QDebug& log, const TZZone& z )
{
    z.print( log );
    return log;
}

class DLLEXPORT TZRegionModel : public QAbstractListModel
{
public:
    /// @brief Create empty model
    TZRegionModel();
    /// @brief Create model from list (non-owning)
    TZRegionModel( TZRegionList );
    virtual ~TZRegionModel() override;

    int rowCount( const QModelIndex& parent ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;

    const TZRegion* region( int index ) const;

private:
    TZRegionList m_regions;
};

}  // namespace Locale
}  // namespace CalamaresUtils

#endif  // LOCALE_TIMEZONE_H
