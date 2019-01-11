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

/** @brief Support for "named" enumerations
 *
 * For tables which map string names to enum values, provide a NamedEnumTable
 * which hangs on to an initializer_list of pairs of names and values.
 * This table can be used with find() to map names to values, or
 * values to names. A convenience function smash() is provided to help
 * in printing integer (underlying) values of an enum.
 */

#ifndef LIBCALAMARES_NAMEDENUM_H
#define LIBCALAMARES_NAMEDENUM_H

#include <QString>

#include <type_traits>
#include <initializer_list>

/** @brief Type for collecting parts of a named enum. */
template<typename T>
struct NamedEnumTable
{
    using string_t = QString;
    using enum_t = T;
    using pair_t = std::pair< string_t, enum_t >;
    using type = std::initializer_list< pair_t >;
} ;

/** @brief Find a name @p s in the @p table. */
template<typename T>
typename NamedEnumTable<T>::enum_t find( const typename NamedEnumTable<T>::type& table, const QString& s, bool& ok )
{
    ok = false;

    for ( const auto p : table )
        if ( s == p.first )
        {
            ok = true;
            return p.second;
        }

    // ok is still false
    return table.begin()->second;
}

/** @brief Find a value @p s in the @p table. */
template<typename T>
typename NamedEnumTable<T>::enum_t find( const typename NamedEnumTable<T>::type& table, const T s, bool& ok )
{
    ok = false;

    for ( const auto p : table )
        if ( s == p.second)
        {
            ok = true;
            return p.first;
        }

    // ok is still false
    return QString();
}

/** @brief Smashes an enum value to its underlying type. */
template<typename E>
constexpr typename std::underlying_type<E>::type smash( const E e )
{
    return static_cast<typename std::underlying_type<E>::type>( e );
}


#endif
