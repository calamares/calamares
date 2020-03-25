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
class CStringPair : public QObject
{
    Q_OBJECT
public:
    /// @brief An empty pair
    CStringPair() {}
    /// @brief Given an identifier, create the pair
    explicit CStringPair( const char* s1 );
    CStringPair( CStringPair&& t );
    CStringPair( const CStringPair& );
    virtual ~CStringPair();

    /// @brief Give the localized human-readable form
    virtual QString tr() const = 0;
    QString key() const { return m_key; }

    bool operator<( const CStringPair& other ) const { return m_key < other.m_key; }

protected:
    char* m_human = nullptr;
    QString m_key;
};

class CStringPairList : public QList< CStringPair* >
{
public:
    template < typename T >
    T* find( const QString& key ) const
    {
        for ( auto* p : *this )
        {
            if ( p->key() == key )
            {
                return dynamic_cast< T* >( p );
            }
        }
        return nullptr;
    }
};

/// @brief A pair of strings for timezone regions (e.g. "America")
class TZRegion : public CStringPair
{
    Q_OBJECT
public:
    using CStringPair::CStringPair;
    virtual ~TZRegion() override;
    TZRegion( const TZRegion& ) = delete;
    QString tr() const override;

    QString region() const { return key(); }

    /** @brief Create list from a zone.tab-like file
     *
     * Returns a list of all the regions; each region has a list
     * of zones within that region. Dyamically, the items in the
     * returned list are TZRegions; their zones dynamically are
     * TZZones even though all those lists have type CStringPairList.
     *
     * The list owns the regions, and the regions own their own list of zones.
     * When getting rid of the list, remember to qDeleteAll() on it.
     */
    static CStringPairList fromFile( const char* fileName );
    /// @brief Calls fromFile with the standard zone.tab name
    static const CStringPairList& fromZoneTab();

    const CStringPairList& zones() const { return m_zones; }

private:
    CStringPairList m_zones;
};

/// @brief A pair of strings for specific timezone names (e.g. "New_York")
class TZZone : public CStringPair
{
    Q_OBJECT
public:
    using CStringPair::CStringPair;
    QString tr() const override;

    TZZone( const QString& region, const char* zoneName, const QString& country, QString position );

    QString region() const { return m_region; }
    QString zone() const { return key(); }
    QString country() const { return m_country; }
    double latitude() const { return m_latitude; }
    double longitude() const { return m_longitude; }

protected:
    QString m_region;
    QString m_country;
    double m_latitude = 0.0, m_longitude = 0.0;
};

class CStringListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged )

public:
    /// @brief Create empty model
    CStringListModel() {}
    /// @brief Create model from list (non-owning)
    CStringListModel( CStringPairList );

    int rowCount( const QModelIndex& parent ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;

    const CStringPair* item( int index ) const;
    QHash< int, QByteArray > roleNames() const override;

    void setCurrentIndex( int index );
    int currentIndex() const;

    void setList( CStringPairList );

    inline int indexOf( const QString& key )
    {
        const auto it = std::find_if(
            m_list.constBegin(), m_list.constEnd(), [&]( const CalamaresUtils::Locale::CStringPair* item ) -> bool {
                return item->key() == key;
            } );

        if ( it != m_list.constEnd() )
        {
            // distance() is usually a long long
            return int( std::distance( m_list.constBegin(), it ) );
        }
        else
        {
            return -1;
        }
    }


private:
    CStringPairList m_list;
    int m_currentIndex = -1;

signals:
    void currentIndexChanged();
};

}  // namespace Locale
}  // namespace CalamaresUtils

#endif  // LOCALE_TIMEZONE_H
