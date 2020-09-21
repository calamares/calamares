/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @brief Support for "named" enumerations
 *
 * For tables which map string names to enum values, provide a NamedEnumTable
 * which hangs on to an initializer_list of pairs of names and values.
 * This table can be used with find() to map names to values, or
 * values to names. A convenience function smash() is provided to help
 * in printing integer (underlying) values of an enum.
 */

#ifndef UTILS_NAMEDENUM_H
#define UTILS_NAMEDENUM_H

#include <QString>

#include <initializer_list>
#include <type_traits>
#include <vector>

/** @brief Type for collecting parts of a named enum. */
template < typename T >
struct NamedEnumTable
{
    using string_t = QString;
    using enum_t = T;
    using pair_t = std::pair< string_t, enum_t >;
    using type = std::vector< pair_t >;

    type table;

    /** @brief Create a table of named enum values.
     *
     * Use braced-initialisation for NamedEnum, and remember that the
     * elements of the list are **pairs**, e.g.
     *
     * static const NamedEnumTable<Colors> c{ {"red", Colors::Red } };
     */
    NamedEnumTable( const std::initializer_list< pair_t >& v )
        : table( v )
    {
        /* static_assert( v.size() > 0 ); */
    }

    /** @brief Find a name @p s in the table.
     *
     * Searches case-insensitively.
     *
     * If the name @p s is not found, @p ok is set to false and
     * the first enum value in the table is returned. Otherwise,
     * @p ok is set to true and the corresponding value is returned.
     *
     */
    enum_t find( const string_t& s, bool& ok ) const
    {
        ok = false;

        for ( const auto& p : table )
            if ( 0 == QString::compare( s, p.first, Qt::CaseInsensitive ) )
            {
                ok = true;
                return p.second;
            }

        // ok is still false
        return table.begin()->second;
    }

    /** @brief Find a value @p s in the table.
     *
     * If the value @p s is not found, @p ok is set to false and
     * an empty string is returned. Otherwise, @p is set to true
     * and the corresponding name is returned.
     */
    string_t find( enum_t s, bool& ok ) const
    {
        ok = false;

        for ( const auto& p : table )
            if ( s == p.second )
            {
                ok = true;
                return p.first;
            }

        // ok is still false
        return string_t();
    }

    /** @brief Find a value @p s in the table and return its name.
     *
     * Returns emptry string if the value is not found.
     */
    string_t find( enum_t s ) const
    {
        bool ok = false;
        return find( s, ok );
    }
};

/** @brief Smashes an enum value to its underlying type. */
template < typename E >
constexpr typename std::underlying_type< E >::type
smash( const E e )
{
    return static_cast< typename std::underlying_type< E >::type >( e );
}

#endif
